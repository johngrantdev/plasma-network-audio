#pragma once

#include <QList>
#include <QObject>
#include <QString>
#include <KSharedConfig>

struct DevicePreference {
    QString id;
    QString name;
    bool autoConnect = false;
    bool ignored = false;
};

class PreferenceStore : public QObject
{
    Q_OBJECT
public:
    explicit PreferenceStore(QObject *parent = nullptr);

    bool hasEntry(const QString &id) const;
    DevicePreference entry(const QString &id) const;
    QList<DevicePreference> allEntries() const;

    void save(const QString &id, const QString &name, bool autoConnect, bool ignored);
    void forget(const QString &id);

private:
    KConfigGroup devicesGroup() const;

    KSharedConfigPtr m_config;
};
