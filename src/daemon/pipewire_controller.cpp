#include "pipewire_controller.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QProcess>

PipeWireController::PipeWireController(QObject *parent)
    : QObject(parent)
{
}

// Derive a stable sm-objects metadata key from the device ID.
static QString smKey(const QString &deviceId)
{
    QString key = QStringLiteral("raop.") + deviceId;
    key.replace(QLatin1Char(' '), QLatin1Char('-'));
    return key;
}

void PipeWireController::connectDevice(const NetworkAudioDevice &device)
{
    const QString nodeName = QString(device.name)
        .replace(QLatin1Char(' '), QLatin1Char('_'))
        .replace(QLatin1Char('\''), QString());

    QJsonObject args;
    args[QStringLiteral("raop.ip")]          = device.host;
    args[QStringLiteral("raop.port")]        = device.port;
    args[QStringLiteral("node.name")]        = QStringLiteral("raop.") + nodeName;
    args[QStringLiteral("node.description")] = device.name;
    if (!device.avahiName.isEmpty())
        args[QStringLiteral("raop.name")]        = device.avahiName;
    if (!device.hostname.isEmpty())
        args[QStringLiteral("raop.hostname")]    = device.hostname;
    if (!device.domain.isEmpty())
        args[QStringLiteral("raop.domain")]      = device.domain;
    if (device.ifindex > 0)
        args[QStringLiteral("raop.ifindex")]     = device.ifindex;
    if (!device.codec.isEmpty())
        args[QStringLiteral("raop.audio.codec")] = device.codec;
    if (!device.encryptionType.isEmpty())
        args[QStringLiteral("raop.encryption.type")] = device.encryptionType;
    if (!device.transport.isEmpty())
        args[QStringLiteral("raop.transport")]   = device.transport;

    QJsonObject root;
    root[QStringLiteral("type")] = QStringLiteral("pw-module");
    root[QStringLiteral("name")] = QStringLiteral("libpipewire-module-raop-sink");
    root[QStringLiteral("args")] = args;

    const QString jsonValue = QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Compact));
    const QString key = smKey(device.id);

    qDebug() << "[PipeWireController] sm-objects set key:" << key;

    auto *proc = new QProcess(this);
    const QString id = device.id;

    connect(proc, &QProcess::errorOccurred, this, [this, proc, id](QProcess::ProcessError) {
        Q_EMIT error(id, QStringLiteral("Failed to start pw-metadata: %1").arg(proc->errorString()));
        proc->deleteLater();
    });
    connect(proc, &QProcess::finished, this, [this, proc, id](int exitCode) {
        const QString err = QString::fromUtf8(proc->readAllStandardError()).trimmed();
        proc->deleteLater();
        if (exitCode == 0)
            Q_EMIT deviceConnected(id);
        else
            Q_EMIT error(id, err.isEmpty() ? QStringLiteral("pw-metadata failed") : err);
    });

    proc->start(QStringLiteral("pw-metadata"),
                { QStringLiteral("-n"), QStringLiteral("sm-objects"),
                  QStringLiteral("0"), key, jsonValue, QStringLiteral("Spa:String:JSON") });
}

void PipeWireController::checkConnectionState(const QString &deviceId)
{
    const QString key = smKey(deviceId);
    auto *proc = new QProcess(this);

    connect(proc, &QProcess::finished, this, [this, proc, deviceId](int exitCode) {
        if (exitCode == 0) {
            const QString out = QString::fromUtf8(proc->readAllStandardOutput());
            if (out.contains(QStringLiteral("value:")))
                Q_EMIT deviceConnected(deviceId);
        }
        proc->deleteLater();
    });

    proc->start(QStringLiteral("pw-metadata"),
                { QStringLiteral("-n"), QStringLiteral("sm-objects"),
                  QStringLiteral("0"), key });
}

void PipeWireController::disconnectDevice(const QString &id)
{
    const QString key = smKey(id);
    qDebug() << "[PipeWireController] sm-objects delete key:" << key;

    auto *proc = new QProcess(this);

    connect(proc, &QProcess::errorOccurred, this, [this, proc, id](QProcess::ProcessError) {
        Q_EMIT error(id, QStringLiteral("Failed to start pw-metadata: %1").arg(proc->errorString()));
        proc->deleteLater();
    });
    connect(proc, &QProcess::finished, this, [this, proc, id](int exitCode) {
        const QString err = QString::fromUtf8(proc->readAllStandardError()).trimmed();
        proc->deleteLater();
        if (exitCode == 0)
            Q_EMIT deviceDisconnected(id);
        else
            Q_EMIT error(id, err.isEmpty() ? QStringLiteral("pw-metadata failed") : err);
    });

    proc->start(QStringLiteral("pw-metadata"),
                { QStringLiteral("-n"), QStringLiteral("sm-objects"),
                  QStringLiteral("-d"), QStringLiteral("0"), key });
}
