#include "network_audio_kcm.h"

#include <KPluginFactory>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusMetaType>
#include <QDebug>

K_PLUGIN_CLASS_WITH_JSON(NetworkAudioKCM, "kcm_network_audio.json")

static const QString DAEMON_SERVICE = QStringLiteral("org.kde.kded6");
static const QString DAEMON_PATH    = QStringLiteral("/NetworkAudio");
static const QString DAEMON_IFACE   = QStringLiteral("org.kde.NetworkAudio");

NetworkAudioKCM::NetworkAudioKCM(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_model(new NetworkAudioModel(this))
    , m_daemon(new QDBusInterface(DAEMON_SERVICE, DAEMON_PATH, DAEMON_IFACE,
                                   QDBusConnection::sessionBus(), this))
{
    setButtons(KQuickConfigModule::NoAdditionalButton);

    qDBusRegisterMetaType<QList<QVariantMap>>();

    auto bus = QDBusConnection::sessionBus();
    bus.connect(DAEMON_SERVICE, DAEMON_PATH, DAEMON_IFACE,
                QStringLiteral("deviceDiscovered"), this,
                SLOT(onDeviceDiscovered(QVariantMap)));
    bus.connect(DAEMON_SERVICE, DAEMON_PATH, DAEMON_IFACE,
                QStringLiteral("deviceRemoved"), this,
                SLOT(onDeviceRemoved(QString)));
    bus.connect(DAEMON_SERVICE, DAEMON_PATH, DAEMON_IFACE,
                QStringLiteral("deviceConnected"), this,
                SLOT(onDeviceConnected(QString)));
    bus.connect(DAEMON_SERVICE, DAEMON_PATH, DAEMON_IFACE,
                QStringLiteral("deviceDisconnected"), this,
                SLOT(onDeviceDisconnected(QString)));
    bus.connect(DAEMON_SERVICE, DAEMON_PATH, DAEMON_IFACE,
                QStringLiteral("deviceError"), this,
                SLOT(onDeviceError(QString,QString)));
    bus.connect(DAEMON_SERVICE, DAEMON_PATH, DAEMON_IFACE,
                QStringLiteral("deviceUpdated"), this,
                SLOT(onDeviceUpdated(QVariantMap)));

    // Ensure daemon is loaded (autoload handles session start; this covers first-run)
    QDBusInterface kded(QStringLiteral("org.kde.kded6"), QStringLiteral("/kded"),
                        QStringLiteral("org.kde.kded6"), QDBusConnection::sessionBus());
    kded.call(QStringLiteral("loadModule"), QStringLiteral("kded_network_audio"));

    loadDevicesFromDaemon();
}

NetworkAudioModel *NetworkAudioKCM::deviceModel() const { return m_model; }
QString NetworkAudioKCM::lastError() const { return m_lastError; }

void NetworkAudioKCM::clearLastError()
{
    m_lastError.clear();
    Q_EMIT lastErrorChanged();
}

void NetworkAudioKCM::connectDevice(const QString &id)
{
    m_daemon->asyncCall(QStringLiteral("connectDevice"), id);
}

void NetworkAudioKCM::disconnectDevice(const QString &id)
{
    m_daemon->asyncCall(QStringLiteral("disconnectDevice"), id);
}

void NetworkAudioKCM::setAutoConnect(const QString &id, bool enabled)
{
    m_daemon->asyncCall(QStringLiteral("setAutoConnect"), id, enabled);
}

void NetworkAudioKCM::forgetDevice(const QString &id)
{
    m_daemon->asyncCall(QStringLiteral("forgetDevice"), id);
}

void NetworkAudioKCM::loadDevicesFromDaemon()
{
    if (!m_daemon->isValid()) {
        qWarning() << "[NetworkAudio KCM] Daemon interface not available:"
                   << m_daemon->lastError().message();
        return;
    }

    QDBusReply<QList<QVariantMap>> reply = m_daemon->call(QStringLiteral("devices"));
    if (!reply.isValid()) {
        qWarning() << "[NetworkAudio KCM] Failed to get devices from daemon:"
                   << reply.error().message();
        return;
    }

    for (const QVariantMap &info : reply.value())
        m_model->addDevice(deviceFromMap(info));
}

void NetworkAudioKCM::onDeviceDiscovered(const QVariantMap &device)
{
    m_model->addDevice(deviceFromMap(device));
}

void NetworkAudioKCM::onDeviceRemoved(const QString &id)
{
    m_model->removeDevice(id);
}

void NetworkAudioKCM::onDeviceUpdated(const QVariantMap &device)
{
    m_model->updateDevice(deviceFromMap(device));
}

void NetworkAudioKCM::onDeviceConnected(const QString &id)
{
    m_model->setConnected(id);
}

void NetworkAudioKCM::onDeviceDisconnected(const QString &id)
{
    m_model->setDisconnected(id);
}

void NetworkAudioKCM::onDeviceError(const QString &id, const QString &message)
{
    setLastError(id, message);
}

void NetworkAudioKCM::setLastError(const QString &id, const QString &msg)
{
    qWarning() << "[NetworkAudio KCM] error for" << id << ":" << msg;
    m_lastError = msg;
    Q_EMIT lastErrorChanged();
}

NetworkAudioDevice NetworkAudioKCM::deviceFromMap(const QVariantMap &map)
{
    NetworkAudioDevice dev;
    dev.id            = map.value(QStringLiteral("id")).toString();
    dev.name          = map.value(QStringLiteral("name")).toString();
    dev.host          = map.value(QStringLiteral("host")).toString();
    dev.port          = static_cast<quint16>(map.value(QStringLiteral("port")).toUInt());
    dev.connected     = map.value(QStringLiteral("connected")).toBool();
    dev.status        = static_cast<NetworkAudioDevice::Status>(
                            map.value(QStringLiteral("status")).toInt());
    dev.autoConnect   = map.value(QStringLiteral("autoConnect")).toBool();
    dev.hasPreference = map.value(QStringLiteral("hasPreference")).toBool();
    return dev;
}

#include "network_audio_kcm.moc"
