#pragma once

#include <QDBusAbstractAdaptor>
#include <QList>
#include <QVariantMap>

class NetworkAudioDaemon;

class NetworkAudioAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.kde.NetworkAudio")

public:
    explicit NetworkAudioAdaptor(NetworkAudioDaemon *parent);

public Q_SLOTS:
    QList<QVariantMap> devices() const;
    void connectDevice(const QString &id);
    void disconnectDevice(const QString &id);
    void setAutoConnect(const QString &id, bool enabled);
    void ignoreDevice(const QString &id);
    void forgetDevice(const QString &id);

Q_SIGNALS:
    void deviceDiscovered(const QVariantMap &device);
    void deviceRemoved(const QString &id);
    void deviceConnected(const QString &id);
    void deviceDisconnected(const QString &id);
    void deviceError(const QString &id, const QString &message);
    void deviceUpdated(const QVariantMap &device);

private:
    NetworkAudioDaemon *m_daemon;
};
