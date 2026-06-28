#include "network_audio_kcm.h"

#include <KPluginFactory>
#include <QDebug>

K_PLUGIN_CLASS_WITH_JSON(NetworkAudioKCM, "kcm_network_audio.json")

NetworkAudioKCM::NetworkAudioKCM(QObject *parent, const KPluginMetaData &data)
    : KQuickConfigModule(parent, data)
    , m_model(new NetworkAudioModel(this))
    , m_browser(new AvahiBrowser(this))
    , m_controller(new PipeWireController(this))
{
    connect(m_browser, &AvahiBrowser::deviceDiscovered, this, [this](const NetworkAudioDevice &dev) {
        m_model->addDevice(dev);
        m_controller->checkConnectionState(dev.id);
    });
    connect(m_browser, &AvahiBrowser::deviceRemoved,
            m_model,   &NetworkAudioModel::removeDevice);

    connect(m_controller, &PipeWireController::deviceConnected,
            m_model,      &NetworkAudioModel::setConnected);
    connect(m_controller, &PipeWireController::deviceDisconnected,
            m_model,      &NetworkAudioModel::setDisconnected);
    connect(m_controller, &PipeWireController::error,
            this,         &NetworkAudioKCM::setLastError);

    setButtons(KQuickConfigModule::NoAdditionalButton);
    m_browser->start();
}

NetworkAudioKCM::~NetworkAudioKCM()
{
    m_browser->stop();
}

NetworkAudioModel *NetworkAudioKCM::deviceModel() const { return m_model; }
QString NetworkAudioKCM::lastError() const { return m_lastError; }

void NetworkAudioKCM::clearLastError()
{
    m_lastError.clear();
    Q_EMIT lastErrorChanged();
}

void NetworkAudioKCM::setLastError(const QString &id, const QString &msg)
{
    qWarning() << "[NetworkAudio] error for" << id << ":" << msg;
    m_lastError = msg;
    Q_EMIT lastErrorChanged();
}

void NetworkAudioKCM::connectDevice(const QString &id)
{
    const NetworkAudioDevice dev = m_model->deviceForId(id);
    if (dev.id.isEmpty()) {
        qWarning() << "[NetworkAudio] connectDevice: id not found:" << id;
        return;
    }
    qDebug() << "[NetworkAudio] connecting" << dev.name << dev.host << dev.port;
    m_controller->connectDevice(dev);
}

void NetworkAudioKCM::disconnectDevice(const QString &id)
{
    qDebug() << "[NetworkAudio] disconnecting" << id;
    m_controller->disconnectDevice(id);
}

#include "network_audio_kcm.moc"
