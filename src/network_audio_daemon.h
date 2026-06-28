#pragma once

#include <KDEDModule>
#include <KPluginMetaData>
#include <QList>
#include <QVariantMap>

#include "network_audio_device.h"
#include "avahi_browser.h"
#include "pipewire_controller.h"
#include "preference_store.h"

class NetworkAudioDaemon : public KDEDModule
{
    Q_OBJECT

public:
    NetworkAudioDaemon(QObject *parent, const KPluginMetaData &data);
    ~NetworkAudioDaemon() override;

    // Called by NetworkAudioAdaptor
    QList<QVariantMap> devices() const;
    void connectDevice(const QString &id);
    void disconnectDevice(const QString &id);
    void setAutoConnect(const QString &id, bool enabled);
    void ignoreDevice(const QString &id);
    void forgetDevice(const QString &id);

Q_SIGNALS:
    // Relayed to D-Bus by NetworkAudioAdaptor via setAutoRelaySignals
    void deviceDiscovered(const QVariantMap &device);
    void deviceRemoved(const QString &id);
    void deviceConnected(const QString &id);
    void deviceDisconnected(const QString &id);
    void deviceError(const QString &id, const QString &message);
    void deviceUpdated(const QVariantMap &device);

private Q_SLOTS:
    void onDeviceDiscovered(const NetworkAudioDevice &dev);
    void onDeviceRemoved(const QString &rawName);

private:
    void showDiscoveryNotification(const NetworkAudioDevice &dev);
    QVariantMap deviceToMap(const NetworkAudioDevice &dev) const;
    int indexForId(const QString &id) const;
    static NetworkAudioDevice deviceFromPreference(const DevicePreference &pref);

    QList<NetworkAudioDevice> m_devices;  // live devices only (Avahi)
    AvahiBrowser              *m_browser;
    PipeWireController        *m_controller;
    PreferenceStore           *m_prefs;
};
