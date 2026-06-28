#pragma once

#include <KQuickConfigModule>
#include "network_audio_model.h"
#include "avahi_browser.h"
#include "pipewire_controller.h"

class NetworkAudioKCM : public KQuickConfigModule
{
    Q_OBJECT
    Q_PROPERTY(NetworkAudioModel *deviceModel READ deviceModel CONSTANT)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    explicit NetworkAudioKCM(QObject *parent, const KPluginMetaData &data);
    ~NetworkAudioKCM() override;

    NetworkAudioModel *deviceModel() const;
    QString lastError() const;

    Q_INVOKABLE void connectDevice(const QString &id);
    Q_INVOKABLE void disconnectDevice(const QString &id);
    Q_INVOKABLE void clearLastError();

Q_SIGNALS:
    void lastErrorChanged();

private:
    void setLastError(const QString &id, const QString &msg);

    NetworkAudioModel   *m_model;
    AvahiBrowser        *m_browser;
    PipeWireController  *m_controller;
    QString              m_lastError;
};
