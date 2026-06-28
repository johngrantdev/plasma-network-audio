#include "avahi_browser.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDBusObjectPath>
#include <QRegularExpression>

static const QString AVAHI_SERVICE  = QStringLiteral("org.freedesktop.Avahi");
static const QString AVAHI_PATH     = QStringLiteral("/");
static const QString SERVER_IFACE   = QStringLiteral("org.freedesktop.Avahi.Server");
static const QString BROWSER_IFACE  = QStringLiteral("org.freedesktop.Avahi.ServiceBrowser");
static const QString RESOLVER_IFACE = QStringLiteral("org.freedesktop.Avahi.ServiceResolver");
static const QString RAOP_TYPE      = QStringLiteral("_raop._tcp");

static const int AVAHI_IF_UNSPEC    = -1;
static const int AVAHI_PROTO_UNSPEC = -1;

AvahiBrowser::AvahiBrowser(QObject *parent)
    : QObject(parent)
{
}

AvahiBrowser::~AvahiBrowser()
{
    stop();
}

void AvahiBrowser::start()
{
    auto bus = QDBusConnection::systemBus();

    m_server = new QDBusInterface(AVAHI_SERVICE, AVAHI_PATH, SERVER_IFACE, bus, this);
    if (!m_server->isValid()) {
        return;
    }

    QDBusReply<QDBusObjectPath> reply = m_server->call(
        QStringLiteral("ServiceBrowserNew"),
        AVAHI_IF_UNSPEC,
        AVAHI_PROTO_UNSPEC,
        RAOP_TYPE,
        QString(),
        uint(0)
    );

    if (!reply.isValid()) {
        return;
    }

    m_browser = new QDBusInterface(AVAHI_SERVICE, reply.value().path(), BROWSER_IFACE, bus, this);

    bus.connect(AVAHI_SERVICE, reply.value().path(), BROWSER_IFACE,
                QStringLiteral("ItemNew"), this,
                SLOT(onItemNew(int,int,QString,QString,QString,uint)));
    bus.connect(AVAHI_SERVICE, reply.value().path(), BROWSER_IFACE,
                QStringLiteral("ItemRemove"), this,
                SLOT(onItemRemove(int,int,QString,QString,QString,uint)));
}

void AvahiBrowser::stop()
{
    if (m_browser) {
        m_browser->call(QStringLiteral("Free"));
        delete m_browser;
        m_browser = nullptr;
    }
    delete m_server;
    m_server = nullptr;
}

void AvahiBrowser::onItemNew(int interface, int protocol, const QString &name,
                              const QString &type, const QString &domain, uint /*flags*/)
{
    createResolver(interface, protocol, name, type, domain);
}

void AvahiBrowser::onItemRemove(int /*interface*/, int /*protocol*/, const QString &name,
                                 const QString &/*type*/, const QString &/*domain*/, uint /*flags*/)
{
    // We don't have the host at remove time, so emit with the raw name as a partial id.
    // NetworkAudioModel matches on name prefix when host is unknown.
    Q_EMIT deviceRemoved(name);
}

void AvahiBrowser::createResolver(int interface, int protocol, const QString &name,
                                   const QString &type, const QString &domain)
{
    auto bus = QDBusConnection::systemBus();

    QDBusReply<QDBusObjectPath> reply = m_server->call(
        QStringLiteral("ServiceResolverNew"),
        interface,
        protocol,
        name,
        type,
        domain,
        AVAHI_PROTO_UNSPEC,
        uint(0)
    );

    if (!reply.isValid()) {
        return;
    }

    const QString resolverPath = reply.value().path();

    // Capture name for the lambda via a helper object
    bus.connect(AVAHI_SERVICE, resolverPath, RESOLVER_IFACE,
                QStringLiteral("Found"), this,
                SLOT(onResolverFound(int,int,QString,QString,QString,QString,int,QString,quint16,QList<QByteArray>,uint)));
}

void AvahiBrowser::onResolverFound(int interface, int /*protocol*/,
                                    const QString &name, const QString &/*type*/,
                                    const QString &domain, const QString &host,
                                    int /*aprotocol*/, const QString &address,
                                    quint16 port, const QList<QByteArray> &txt, uint /*flags*/)
{
    QMap<QString, QString> txtMap;
    for (const QByteArray &record : txt) {
        const int eq = record.indexOf('=');
        if (eq > 0)
            txtMap.insert(QString::fromUtf8(record.left(eq)).toLower(),
                          QString::fromUtf8(record.mid(eq + 1)));
    }

    NetworkAudioDevice device;
    device.name     = stripMacPrefix(name);
    device.avahiName = name;
    device.host     = address;
    device.hostname = host;
    device.domain   = domain;
    device.port     = port;
    device.ifindex  = interface;
    device.id       = makeId(name, address);

    static const QStringList codecNames = { "PCM", "ALAC", "AAC", "AAC-ELD" };
    device.codec = QStringLiteral("PCM");
    if (txtMap.contains(QStringLiteral("cn"))) {
        for (const QString &s : txtMap[QStringLiteral("cn")].split(QLatin1Char(','))) {
            bool ok;
            const int n = s.trimmed().toInt(&ok);
            if (ok && n >= 0 && n < codecNames.size()) { device.codec = codecNames[n]; break; }
        }
    }

    device.encryptionType = QStringLiteral("none");
    if (txtMap.contains(QStringLiteral("et"))) {
        bool hasAuthSetup = false, hasRSA = false;
        for (const QString &s : txtMap[QStringLiteral("et")].split(QLatin1Char(','))) {
            bool ok; const int n = s.trimmed().toInt(&ok);
            if (ok) { if (n == 4) hasAuthSetup = true; else if (n == 1) hasRSA = true; }
        }
        if (hasAuthSetup) device.encryptionType = QStringLiteral("auth_setup");
        else if (hasRSA)  device.encryptionType = QStringLiteral("RSA");
    }

    device.transport = QStringLiteral("udp");
    if (txtMap.contains(QStringLiteral("tp"))) {
        const QString tp = txtMap[QStringLiteral("tp")].toUpper();
        if (!tp.contains(QStringLiteral("UDP")) && tp.contains(QStringLiteral("TCP")))
            device.transport = QStringLiteral("tcp");
    }

    device.deviceType = detectDeviceType(txtMap.value(QStringLiteral("am")), host);

    Q_EMIT deviceDiscovered(device);
}

// static
QString AvahiBrowser::detectDeviceType(const QString &am, const QString &hostname)
{
    const QString a = am.toLower();
    if (a.startsWith(QLatin1String("appletv")))
        return QStringLiteral("Apple TV");
    if (a.startsWith(QLatin1String("homepod")) || a.startsWith(QLatin1String("audioaccessory")))
        return QStringLiteral("HomePod");
    if (a.startsWith(QLatin1String("airport")))
        return QStringLiteral("AirPort Express");
    if (a.contains(QLatin1String("shairport")))
        return QStringLiteral("Shairport-sync");
    if (hostname.contains(QLatin1String("sonos"), Qt::CaseInsensitive))
        return QStringLiteral("Sonos");
    // Samsung, LG, Sony etc. don't set 'am'; try name-based heuristics
    const QString h = hostname.toLower();
    if (h.contains(QLatin1String("samsung"))) return QStringLiteral("Samsung TV");
    if (h.contains(QLatin1String("lg")))      return QStringLiteral("LG TV");
    if (h.contains(QLatin1String("sony")))    return QStringLiteral("Sony TV");
    if (h.contains(QLatin1String("denon")))   return QStringLiteral("Denon");
    if (h.contains(QLatin1String("marantz"))) return QStringLiteral("Marantz");
    if (h.contains(QLatin1String("bose")))    return QStringLiteral("Bose");
    return QStringLiteral("AirPlay");
}

QString AvahiBrowser::stripMacPrefix(const QString &rawName)
{
    // Avahi RAOP names are formatted as "AABBCCDDEEFF@Display Name"
    static const QRegularExpression macPrefix(QStringLiteral("^[0-9A-Fa-f]{12}@"));
    return rawName.contains(QLatin1Char('@'))
        ? rawName.section(QLatin1Char('@'), 1)
        : rawName;
}

QString AvahiBrowser::makeId(const QString &name, const QString &host)
{
    return name + QLatin1Char('@') + host;
}
