#pragma once

#include <QAbstractListModel>
#include <QList>
#include "network_audio_device.h"

class NetworkAudioModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        HostRole,
        PortRole,
        ConnectedRole,
        StatusRole,
        AutoConnectRole,
        HasPreferenceRole,
    };

    explicit NetworkAudioModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = {}) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    NetworkAudioDevice deviceForId(const QString &id) const;

public Q_SLOTS:
    void addDevice(const NetworkAudioDevice &device);
    void removeDevice(const QString &id);
    void updateDevice(const NetworkAudioDevice &device);
    void setConnected(const QString &id);
    void setDisconnected(const QString &id);

private:
    int indexForId(const QString &id) const;
    int insertionIndexFor(NetworkAudioDevice::Status status) const;

    QList<NetworkAudioDevice> m_devices;
};
