# Plasma Network Audio

A KDE Plasma system settings module for managing AirPlay/RAOP network audio devices. Provides a Bluetooth-style UX — discover devices on the network and connect to them manually, with options for auto-connect and per-device preferences.

## Screenshot

![Settings — device connected](screenshots/settings-connected.png)

## Features

- Discover AirPlay/RAOP devices on the local network
- Connect and disconnect devices on demand
- Auto-connect option per device
- Desktop notifications for newly discovered devices (Connect / Ignore)
- Remembers device preferences across sessions
- Detects device type (Apple TV, HomePod, Sonos, AirPort Express, etc.)

## Dependencies

- KDE Plasma 6
- KDE Frameworks 6: KCMUtils, KDBusAddons, KNotifications, KConfig, KCoreAddons, KI18n
- Qt 6: Core, DBus, Quick
- PipeWire with `libpipewire-module-raop-sink`
- Avahi

## Conflict with raop-discover

This application manually manages audio sinks for network devices. It conflicts with `libpipewire-module-raop-discover`, which automatically creates sinks for all discovered devices.

Before using this application, disable raop-discover by removing:

```
/usr/share/pipewire/pipewire.conf.d/50-raop.conf
```

On Fedora/Aurora this file is provided by the `pipewire` package. Removing it requires either a custom OS image or a local override.

## Building

```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=~/.local
cmake --build build
cmake --install build
```

After installing, log out and back in for the kded module to load.
