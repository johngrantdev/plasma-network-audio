# KCM — UI only, talks to the daemon via D-Bus
kcmutils_add_qml_kcm(kcm_network_audio
    SOURCES
        network_audio_kcm.cpp
        network_audio_model.cpp
)

target_link_libraries(kcm_network_audio PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::DBus
    KF6::CoreAddons
    KF6::I18n
    KF6::KCMUtilsQuick
)

target_include_directories(kcm_network_audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# kded module — always-running daemon: discovery, auto-connect, notifications
kcoreaddons_add_plugin(kded_network_audio
    INSTALL_NAMESPACE "kf6/kded"
    SOURCES
        network_audio_daemon.cpp
        network_audio_adaptor.cpp
        avahi_browser.cpp
        pipewire_controller.cpp
        preference_store.cpp
)

target_link_libraries(kded_network_audio PRIVATE
    Qt6::Core
    Qt6::DBus
    KF6::CoreAddons
    KF6::DBusAddons
    KF6::Notifications
    KF6::ConfigCore
    KF6::I18n
)

target_include_directories(kded_network_audio PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

install(FILES kded_network_audio.notifyrc
    DESTINATION ${KDE_INSTALL_DATADIR}/knotifications6
)
