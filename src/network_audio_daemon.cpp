#include "network_audio_daemon.h"
#include "network_audio_adaptor.h"

#include <KPluginFactory>
#include <KNotification>
#include <KLocalizedString>
#include <QDBusConnection>
#include <QDBusMetaType>
#include <QDebug>

K_PLUGIN_CLASS_WITH_JSON(NetworkAudioDaemon, "network_audio_daemon.json")

NetworkAudioDaemon::NetworkAudioDaemon(QObject *parent, const KPluginMetaData &data)
    : KDEDModule(parent)
    , m_browser(new AvahiBrowser(this))
    , m_controller(new PipeWireController(this))
    , m_prefs(new PreferenceStore(this))
{
    Q_UNUSED(data)

    KLocalizedString::setApplicationDomain("kded_network_audio");
    qDBusRegisterMetaType<QList<QVariantMap>>();
    new NetworkAudioAdaptor(this);

    auto bus = QDBusConnection::sessionBus();
    if (!bus.registerObject(QStringLiteral("/NetworkAudio"), this,
                            QDBusConnection::ExportAdaptors))
        qWarning() << "[NetworkAudio daemon] Failed to register D-Bus object at /NetworkAudio";

    connect(m_browser, &AvahiBrowser::deviceDiscovered,
            this, &NetworkAudioDaemon::onDeviceDiscovered);
    connect(m_browser, &AvahiBrowser::deviceRemoved,
            this, &NetworkAudioDaemon::onDeviceRemoved);

    connect(m_controller, &PipeWireController::deviceConnected, this, [this](const QString &id) {
        const int i = indexForId(id);
        if (i >= 0) m_devices[i].connected = true;
        Q_EMIT deviceConnected(id);
    });
    connect(m_controller, &PipeWireController::deviceDisconnected, this, [this](const QString &id) {
        const int i = indexForId(id);
        if (i >= 0) m_devices[i].connected = false;
        Q_EMIT deviceDisconnected(id);
    });
    connect(m_controller, &PipeWireController::error,
            this, &NetworkAudioDaemon::deviceError);

    m_browser->start();
}

NetworkAudioDaemon::~NetworkAudioDaemon()
{
    m_browser->stop();
}

QList<QVariantMap> NetworkAudioDaemon::devices() const
{
    QList<QVariantMap> result;

    for (const NetworkAudioDevice &dev : m_devices)
        result.append(deviceToMap(dev));

    // Append offline/ignored devices that are not currently live
    for (const DevicePreference &pref : m_prefs->allEntries()) {
        if (indexForId(pref.id) >= 0)
            continue;
        result.append(deviceToMap(deviceFromPreference(pref)));
    }

    return result;
}

void NetworkAudioDaemon::connectDevice(const QString &id)
{
    const int i = indexForId(id);
    if (i < 0) {
        qWarning() << "[NetworkAudio daemon] connectDevice: id not found:" << id;
        return;
    }
    m_controller->connectDevice(m_devices.at(i));
}

void NetworkAudioDaemon::disconnectDevice(const QString &id)
{
    m_controller->disconnectDevice(id);
}

void NetworkAudioDaemon::setAutoConnect(const QString &id, bool enabled)
{
    const int i = indexForId(id);

    if (i >= 0) {
        m_devices[i].autoConnect   = enabled;
        m_devices[i].hasPreference = true;
        m_prefs->save(id, m_devices[i].name, enabled,
                      m_devices[i].status == NetworkAudioDevice::Status::Ignored);
        Q_EMIT deviceUpdated(deviceToMap(m_devices[i]));

        if (enabled && !m_devices[i].connected
                && m_devices[i].status == NetworkAudioDevice::Status::Available)
            m_controller->connectDevice(m_devices[i]);
    } else if (m_prefs->hasEntry(id)) {
        const DevicePreference pref = m_prefs->entry(id);
        m_prefs->save(id, pref.name, enabled, pref.ignored);
        Q_EMIT deviceUpdated(deviceToMap(deviceFromPreference(m_prefs->entry(id))));
    }
}

void NetworkAudioDaemon::ignoreDevice(const QString &id)
{
    const int i = indexForId(id);
    const QString name = (i >= 0) ? m_devices.at(i).name
                                  : m_prefs->entry(id).name;
    m_prefs->save(id, name, false, true);

    if (i >= 0) {
        m_devices[i].status        = NetworkAudioDevice::Status::Ignored;
        m_devices[i].autoConnect   = false;
        m_devices[i].hasPreference = true;
        Q_EMIT deviceUpdated(deviceToMap(m_devices[i]));
    } else {
        Q_EMIT deviceUpdated(deviceToMap(deviceFromPreference(m_prefs->entry(id))));
    }
}

void NetworkAudioDaemon::forgetDevice(const QString &id)
{
    m_prefs->forget(id);

    const int i = indexForId(id);
    if (i >= 0) {
        m_devices[i].status        = NetworkAudioDevice::Status::Available;
        m_devices[i].autoConnect   = false;
        m_devices[i].hasPreference = false;
        Q_EMIT deviceUpdated(deviceToMap(m_devices[i]));
    } else {
        // Was offline/ignored — remove from the KCM model entirely
        Q_EMIT deviceRemoved(id);
    }
}

void NetworkAudioDaemon::onDeviceDiscovered(const NetworkAudioDevice &rawDev)
{
    NetworkAudioDevice dev = rawDev;
    dev.hasPreference = m_prefs->hasEntry(dev.id);

    if (dev.hasPreference) {
        const DevicePreference pref = m_prefs->entry(dev.id);
        dev.autoConnect = pref.autoConnect;
        dev.status      = pref.ignored ? NetworkAudioDevice::Status::Ignored
                                       : NetworkAudioDevice::Status::Available;
        // Refresh stored name to the latest display name
        if (!pref.ignored)
            m_prefs->save(dev.id, dev.name, pref.autoConnect, false);
    }

    const int existing = indexForId(dev.id);
    if (existing >= 0) {
        const bool wasConnected = m_devices.at(existing).connected;
        m_devices[existing] = dev;
        m_devices[existing].connected = wasConnected;
        Q_EMIT deviceUpdated(deviceToMap(m_devices[existing]));
        return;
    }

    m_devices.append(dev);
    m_controller->checkConnectionState(dev.id);
    Q_EMIT deviceDiscovered(deviceToMap(dev));

    if (dev.status == NetworkAudioDevice::Status::Ignored)
        return;

    if (dev.autoConnect) {
        m_controller->connectDevice(dev);
        return;
    }

    if (!dev.hasPreference)
        showDiscoveryNotification(dev);
}

void NetworkAudioDaemon::onDeviceRemoved(const QString &rawName)
{
    for (int i = 0; i < m_devices.size(); ++i) {
        const NetworkAudioDevice &dev = m_devices.at(i);
        if (dev.id.startsWith(rawName + QLatin1Char('@')) || dev.id == rawName) {
            const QString id = dev.id;
            m_devices.removeAt(i);

            if (m_prefs->hasEntry(id)) {
                // Transition to Offline/Ignored rather than removing from the model
                Q_EMIT deviceUpdated(deviceToMap(deviceFromPreference(m_prefs->entry(id))));
            } else {
                Q_EMIT deviceRemoved(id);
            }
            return;
        }
    }
}

void NetworkAudioDaemon::showDiscoveryNotification(const NetworkAudioDevice &dev)
{
    auto *notification = new KNotification(QStringLiteral("newDeviceFound"),
                                           KNotification::Persistent, this);
    notification->setTitle(i18n("Network Audio Device Found"));
    notification->setText(i18n("%1 is available on the network", dev.name));
    notification->setIconName(QStringLiteral("audio-speakers"));
    notification->setComponentName(QStringLiteral("kded_network_audio"));

    const QString id = dev.id;

    auto *connectAction = notification->addAction(i18n("Connect"));
    connect(connectAction, &KNotificationAction::activated, this, [this, id]() {
        const int i = indexForId(id);
        if (i < 0) return;
        m_prefs->save(id, m_devices[i].name, true, false);
        m_devices[i].autoConnect   = true;
        m_devices[i].hasPreference = true;
        Q_EMIT deviceUpdated(deviceToMap(m_devices[i]));
        m_controller->connectDevice(m_devices[i]);
    });

    auto *ignoreAction = notification->addAction(i18n("Ignore"));
    connect(ignoreAction, &KNotificationAction::activated, this, [this, id]() {
        ignoreDevice(id);
    });

    connect(notification, &KNotification::closed, notification, &QObject::deleteLater);
    notification->sendEvent();
}

QVariantMap NetworkAudioDaemon::deviceToMap(const NetworkAudioDevice &dev) const
{
    return {
        {QStringLiteral("id"),            dev.id},
        {QStringLiteral("name"),          dev.name},
        {QStringLiteral("host"),          dev.host},
        {QStringLiteral("port"),          static_cast<uint>(dev.port)},
        {QStringLiteral("connected"),     dev.connected},
        {QStringLiteral("status"),        static_cast<int>(dev.status)},
        {QStringLiteral("autoConnect"),   dev.autoConnect},
        {QStringLiteral("hasPreference"), dev.hasPreference},
    };
}

NetworkAudioDevice NetworkAudioDaemon::deviceFromPreference(const DevicePreference &pref)
{
    NetworkAudioDevice dev;
    dev.id            = pref.id;
    dev.name          = pref.name;
    dev.autoConnect   = pref.autoConnect;
    dev.hasPreference = true;
    dev.status        = pref.ignored ? NetworkAudioDevice::Status::Ignored
                                     : NetworkAudioDevice::Status::Offline;
    return dev;
}

int NetworkAudioDaemon::indexForId(const QString &id) const
{
    for (int i = 0; i < m_devices.size(); ++i) {
        if (m_devices.at(i).id == id) return i;
    }
    return -1;
}

#include "network_audio_daemon.moc"
