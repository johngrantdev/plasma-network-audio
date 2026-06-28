#pragma once

#include <QObject>
#include <QStringList>
#include "network_audio_device.h"

class QDBusInterface;

class AvahiBrowser : public QObject
{
    Q_OBJECT
public:
    explicit AvahiBrowser(QObject *parent = nullptr);
    ~AvahiBrowser() override;

    void start();
    void stop();

Q_SIGNALS:
    void deviceDiscovered(const NetworkAudioDevice &device);
    void deviceRemoved(const QString &id);

private Q_SLOTS:
    void onItemNew(int interface, int protocol, const QString &name,
                   const QString &type, const QString &domain, uint flags);
    void onItemRemove(int interface, int protocol, const QString &name,
                      const QString &type, const QString &domain, uint flags);
    void onResolverFound(int interface, int protocol, const QString &name,
                         const QString &type, const QString &domain,
                         const QString &host, int aprotocol, const QString &address,
                         quint16 port, const QList<QByteArray> &txt, uint flags);

private:
    void createResolver(int interface, int protocol, const QString &name,
                        const QString &type, const QString &domain);
    static QString detectDeviceType(const QString &am, const QString &hostname);
    static QString stripMacPrefix(const QString &rawName);
    static QString makeId(const QString &name, const QString &host);

    QDBusInterface *m_server = nullptr;
    QDBusInterface *m_browser = nullptr;
};
