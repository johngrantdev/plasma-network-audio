Name:           plasma-network-audio
Version:        %{version}
Release:        %{release}%{?dist}
Summary:        Network audio device management for KDE Plasma
License:        GPL-2.0-or-later

BuildRequires:  cmake
BuildRequires:  extra-cmake-modules
BuildRequires:  gcc-c++
BuildRequires:  ninja-build
BuildRequires:  qt6-qtbase-devel
BuildRequires:  qt6-qtdeclarative-devel
BuildRequires:  kf6-kcoreaddons-devel
BuildRequires:  kf6-ki18n-devel
BuildRequires:  kf6-kcmutils-devel
BuildRequires:  kf6-kdbusaddons-devel
BuildRequires:  kf6-knotifications-devel
BuildRequires:  kf6-kconfig-devel

Requires:       kf6-kdbusaddons
Requires:       kf6-knotifications
Requires:       kf6-kconfig
Requires:       pipewire-utils

%description
Provides a Bluetooth-style UX for AirPlay/RAOP network audio devices in KDE
Plasma. Instead of auto-creating PipeWire sinks for every discovered device,
users explicitly connect to the devices they want. Includes a System Settings
page and desktop notifications with Connect/Ignore actions.

%install
cp -a %{staging}/* %{buildroot}/

%files
%{_libdir}/plugins/kf6/kded/kded_network_audio.so
%{_libdir}/plugins/plasma/kcms/systemsettings/kcm_network_audio.so
%{_datadir}/applications/kcm_network_audio.desktop
%{_datadir}/knotifications6/kded_network_audio.notifyrc

%changelog
* %(date "+%%a %%b %%d %%Y") John Grant <jlgrant85@gmail.com> - %{version}-%{release}
- Alpha release
