#pragma once

#include <QString>

struct NetworkAudioDevice {
    QString id;              // unique key: "rawAvahiName@host"
    QString name;            // display name (MAC prefix stripped)
    QString avahiName;       // raw Avahi name, e.g. "542A1B855FEC@Family Room"
    QString host;            // IP address
    QString hostname;        // mDNS hostname, e.g. "Sonos-542A1B855FEC.local"
    QString domain;          // mDNS domain, e.g. "local"
    quint16 port = 0;
    int ifindex = 0;         // network interface index from Avahi resolver
    QString codec;           // raop.audio.codec, e.g. "PCM"
    QString encryptionType;  // raop.encryption.type, e.g. "auth_setup"
    QString transport;       // raop.transport, e.g. "udp"
    bool connected = false;
};
