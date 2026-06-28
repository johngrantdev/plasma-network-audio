#include "preference_store.h"

#include <KConfigGroup>

PreferenceStore::PreferenceStore(QObject *parent)
    : QObject(parent)
    , m_config(KSharedConfig::openConfig(QStringLiteral("plasma-network-audiorc")))
{
}

KConfigGroup PreferenceStore::devicesGroup() const
{
    return KConfigGroup(m_config, QStringLiteral("Devices"));
}

bool PreferenceStore::hasEntry(const QString &id) const
{
    return devicesGroup().hasGroup(id);
}

DevicePreference PreferenceStore::entry(const QString &id) const
{
    const KConfigGroup grp = devicesGroup().group(id);
    DevicePreference p;
    p.id          = id;
    p.name        = grp.readEntry("name", QString());
    p.autoConnect = grp.readEntry("autoConnect", false);
    p.ignored     = grp.readEntry("ignored", false);
    return p;
}

QList<DevicePreference> PreferenceStore::allEntries() const
{
    QList<DevicePreference> result;
    for (const QString &id : devicesGroup().groupList())
        result.append(entry(id));
    return result;
}

void PreferenceStore::save(const QString &id, const QString &name, bool autoConnect, bool ignored)
{
    KConfigGroup top = devicesGroup();
    KConfigGroup grp = top.group(id);
    grp.writeEntry("name",        name);
    grp.writeEntry("autoConnect", autoConnect);
    grp.writeEntry("ignored",     ignored);
    m_config->sync();
}

void PreferenceStore::forget(const QString &id)
{
    KConfigGroup top = devicesGroup();
    top.deleteGroup(id);
    m_config->sync();
}
