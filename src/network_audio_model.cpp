#include "network_audio_model.h"

NetworkAudioModel::NetworkAudioModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int NetworkAudioModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_devices.size();
}

QVariant NetworkAudioModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_devices.size())
        return {};

    const auto &dev = m_devices.at(index.row());
    switch (role) {
    case IdRole:        return dev.id;
    case NameRole:      return dev.name;
    case HostRole:      return dev.host;
    case PortRole:      return dev.port;
    case ConnectedRole: return dev.connected;
    default:            return {};
    }
}

QHash<int, QByteArray> NetworkAudioModel::roleNames() const
{
    return {
        {IdRole,        "deviceId"},
        {NameRole,      "name"},
        {HostRole,      "host"},
        {PortRole,      "port"},
        {ConnectedRole, "connected"},
    };
}

NetworkAudioDevice NetworkAudioModel::deviceForId(const QString &id) const
{
    const int i = indexForId(id);
    return i >= 0 ? m_devices.at(i) : NetworkAudioDevice{};
}

void NetworkAudioModel::addDevice(const NetworkAudioDevice &device)
{
    // Update in-place if already present (re-resolved after network change)
    const int existing = indexForId(device.id);
    if (existing >= 0) {
        m_devices[existing].name = device.name;
        m_devices[existing].host = device.host;
        m_devices[existing].port = device.port;
        const QModelIndex idx = index(existing);
        Q_EMIT dataChanged(idx, idx, {NameRole, HostRole, PortRole});
        return;
    }

    beginInsertRows({}, m_devices.size(), m_devices.size());
    m_devices.append(device);
    endInsertRows();
}

void NetworkAudioModel::removeDevice(const QString &rawName)
{
    // ItemRemove gives us the raw mDNS name (with MAC prefix) but not the host,
    // so match on any device whose id starts with rawName@
    for (int i = 0; i < m_devices.size(); ++i) {
        if (m_devices.at(i).id.startsWith(rawName + QLatin1Char('@'))
            || m_devices.at(i).id == rawName) {
            beginRemoveRows({}, i, i);
            m_devices.removeAt(i);
            endRemoveRows();
            return;
        }
    }
}

void NetworkAudioModel::setConnected(const QString &id)
{
    const int i = indexForId(id);
    if (i < 0) return;
    m_devices[i].connected = true;
    const QModelIndex idx = index(i);
    Q_EMIT dataChanged(idx, idx, {ConnectedRole});
}

void NetworkAudioModel::setDisconnected(const QString &id)
{
    const int i = indexForId(id);
    if (i < 0) return;
    m_devices[i].connected = false;
    const QModelIndex idx = index(i);
    Q_EMIT dataChanged(idx, idx, {ConnectedRole});
}

int NetworkAudioModel::indexForId(const QString &id) const
{
    for (int i = 0; i < m_devices.size(); ++i) {
        if (m_devices.at(i).id == id) return i;
    }
    return -1;
}
