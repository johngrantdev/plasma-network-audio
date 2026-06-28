#include "network_audio_adaptor.h"
#include "network_audio_daemon.h"

NetworkAudioAdaptor::NetworkAudioAdaptor(NetworkAudioDaemon *parent)
    : QDBusAbstractAdaptor(parent)
    , m_daemon(parent)
{
    setAutoRelaySignals(true);
}

QList<QVariantMap> NetworkAudioAdaptor::devices() const
{
    return m_daemon->devices();
}

void NetworkAudioAdaptor::connectDevice(const QString &id)
{
    m_daemon->connectDevice(id);
}

void NetworkAudioAdaptor::disconnectDevice(const QString &id)
{
    m_daemon->disconnectDevice(id);
}

void NetworkAudioAdaptor::setAutoConnect(const QString &id, bool enabled)
{
    m_daemon->setAutoConnect(id, enabled);
}

void NetworkAudioAdaptor::ignoreDevice(const QString &id)
{
    m_daemon->ignoreDevice(id);
}

void NetworkAudioAdaptor::forgetDevice(const QString &id)
{
    m_daemon->forgetDevice(id);
}
