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
    case IdRole:            return dev.id;
    case NameRole:          return dev.name;
    case HostRole:          return dev.host;
    case PortRole:          return dev.port;
    case ConnectedRole:     return dev.connected;
    case StatusRole:        return static_cast<int>(dev.status);
    case AutoConnectRole:   return dev.autoConnect;
    case HasPreferenceRole: return dev.hasPreference;
    default:                return {};
    }
}

QHash<int, QByteArray> NetworkAudioModel::roleNames() const
{
    return {
        {IdRole,            "deviceId"},
        {NameRole,          "name"},
        {HostRole,          "host"},
        {PortRole,          "port"},
        {ConnectedRole,     "connected"},
        {StatusRole,        "status"},
        {AutoConnectRole,   "autoConnect"},
        {HasPreferenceRole, "hasPreference"},
    };
}

NetworkAudioDevice NetworkAudioModel::deviceForId(const QString &id) const
{
    const int i = indexForId(id);
    return i >= 0 ? m_devices.at(i) : NetworkAudioDevice{};
}

// Find the first position whose section is "greater than" status,
// so new items land at the end of their section.
int NetworkAudioModel::insertionIndexFor(NetworkAudioDevice::Status status) const
{
    using S = NetworkAudioDevice::Status;
    for (int i = 0; i < m_devices.size(); ++i) {
        const S s = m_devices.at(i).status;
        if (status == S::Available && s != S::Available) return i;
        if (status == S::Offline   && s == S::Ignored)   return i;
    }
    return m_devices.size();
}

void NetworkAudioModel::addDevice(const NetworkAudioDevice &device)
{
    const int existing = indexForId(device.id);
    if (existing >= 0) {
        updateDevice(device);
        return;
    }

    const int pos = insertionIndexFor(device.status);
    beginInsertRows({}, pos, pos);
    m_devices.insert(pos, device);
    endInsertRows();
}

void NetworkAudioModel::removeDevice(const QString &id)
{
    const int i = indexForId(id);
    if (i < 0) return;
    beginRemoveRows({}, i, i);
    m_devices.removeAt(i);
    endRemoveRows();
}

void NetworkAudioModel::updateDevice(const NetworkAudioDevice &device)
{
    const int i = indexForId(device.id);
    if (i < 0) {
        addDevice(device);
        return;
    }

    if (m_devices.at(i).status != device.status) {
        // Status changed — remove and re-insert in the correct section
        beginRemoveRows({}, i, i);
        m_devices.removeAt(i);
        endRemoveRows();

        const int pos = insertionIndexFor(device.status);
        beginInsertRows({}, pos, pos);
        m_devices.insert(pos, device);
        endInsertRows();
    } else {
        m_devices[i] = device;
        const QModelIndex idx = index(i);
        Q_EMIT dataChanged(idx, idx);
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
