#pragma once

#include <KQuickConfigModule>
#include "network_audio_model.h"

class QDBusInterface;

class NetworkAudioKCM : public KQuickConfigModule
{
    Q_OBJECT
    Q_PROPERTY(NetworkAudioModel *deviceModel READ deviceModel CONSTANT)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit NetworkAudioKCM(QObject *parent, const KPluginMetaData &data);

    NetworkAudioModel *deviceModel() const;
    QString lastError() const;

    Q_INVOKABLE void connectDevice(const QString &id);
    Q_INVOKABLE void disconnectDevice(const QString &id);
    Q_INVOKABLE void setAutoConnect(const QString &id, bool enabled);
    Q_INVOKABLE void forgetDevice(const QString &id);
    Q_INVOKABLE void clearLastError();

Q_SIGNALS:
    void lastErrorChanged();

private Q_SLOTS:
    void onDeviceDiscovered(const QVariantMap &device);
    void onDeviceRemoved(const QString &id);
    void onDeviceConnected(const QString &id);
    void onDeviceDisconnected(const QString &id);
    void onDeviceError(const QString &id, const QString &message);
    void onDeviceUpdated(const QVariantMap &device);

private:
    void setLastError(const QString &id, const QString &msg);
    void loadDevicesFromDaemon();
    static NetworkAudioDevice deviceFromMap(const QVariantMap &map);

    NetworkAudioModel *m_model;
    QDBusInterface    *m_daemon;
    QString            m_lastError;
};
