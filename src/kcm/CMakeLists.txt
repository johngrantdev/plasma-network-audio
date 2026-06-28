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

target_include_directories(kcm_network_audio PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
