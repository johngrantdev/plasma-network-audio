#pragma once

#include <QObject>
#include "network_audio_device.h"

class QProcess;

class PipeWireController : public QObject
{
    Q_OBJECT
public:
    explicit PipeWireController(QObject *parent = nullptr);

    void connectDevice(const NetworkAudioDevice &device);
    void disconnectDevice(const QString &id);
    void checkConnectionState(const QString &deviceId);

Q_SIGNALS:
    void deviceConnected(const QString &id);
    void deviceDisconnected(const QString &id);
    void error(const QString &id, const QString &message);
};
