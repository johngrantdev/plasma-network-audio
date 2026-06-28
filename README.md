# Plasma Network Audio

> Disclaimer: This project was vibe coded to fix an issue I was having with how random network audio devices were automatically added as audio outputs in KDE Plasma/Pipewire. It works well for my use case but has had limited testing. So read the source code and use at your own risk.

This is a KDE Plasma system settings module for managing AirPlay/RAOP network audio devices. Currently KDE Plasma uses `libpipewire-module-raop-discover` to automatically discover and add audio sinks for all network audio devices on the network. This functionality can cause audio to output from devices that the user never explicitly connected to. This solution instead provides a Bluetooth-style UX to discover devices on the network and connect to them manually, with options for auto-connect and per-device preferences.

## Screenshot

![Settings — device connected](screenshots/settings-connected.png)

## Features

- Discover AirPlay/RAOP devices on the local network
- Connect and disconnect devices on demand
- Auto-connect option per device
- Desktop notifications for newly discovered devices (Connect / Ignore)
- Remembers device preferences across sessions
- Detects device type (Apple TV, HomePod, Sonos, AirPort Express, etc.)

## Architecture

The project has two components that communicate over D-Bus.

### Daemon (`kded_network_audio`)

A `KDEDModule` that runs persistently in the KDE session, loaded automatically by `kded6` at login. It owns all the application logic:

- **AvahiBrowser** — watches for `_raop._tcp` mDNS services using Avahi. Detects device type from TXT record fields and hostname heuristics.
- **PipeWireController** — creates and removes PipeWire audio sinks by invoking `pactl load-module module-raop-sink` / `pactl unload-module`. This is what actually connects a device as an audio output.
- **PreferenceStore** — persists per-device settings (name, device type, auto-connect, ignored) in `~/.config/plasma-network-audiorc` via KConfig.
- **NetworkAudioAdaptor** — a `QDBusAbstractAdaptor` that exposes the daemon's API on the session bus at `org.kde.kded6` / `/NetworkAudio` / `org.kde.NetworkAudio`.

When a new device is discovered the daemon checks stored preferences. If the device is set to auto-connect it creates a sink immediately. If it has no preference, a desktop notification is shown with Connect and Ignore actions. If ignored, it is silently tracked but no sink is created. When a device goes offline, known devices transition to an Offline state rather than being forgotten.

### Settings UI (`kcm_network_audio`)

A thin `KQuickConfigModule` (System Settings page) with no discovery or audio logic of its own. On load it calls `devices()` over D-Bus to populate the list, then subscribes to daemon signals (`deviceDiscovered`, `deviceRemoved`, `deviceUpdated`, `deviceConnected`, `deviceDisconnected`) to keep the view in sync. User actions (connect, disconnect, auto-connect toggle, forget) are forwarded as D-Bus calls to the daemon.

The device list is backed by a `QAbstractListModel` and rendered in QML, with devices grouped into Available, Offline, and Ignored sections.

```
Avahi  →  AvahiBrowser  →  NetworkAudioDaemon  →  D-Bus  →  NetworkAudioKCM  →  QML
                                    ↕
                           PipeWireController
                           PreferenceStore
```

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

**Note:** The commonly suggested alternative of setting `context.properties = { module.raop = false }` in a pipewire drop-in config will not work here. That property disables all RAOP modules including `libpipewire-module-raop-sink`, which this application depends on to create audio sinks when connecting to devices.

## Building

```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=~/.local
cmake --build build
cmake --install build
```

After installing, log out and back in for the kded module to load.
