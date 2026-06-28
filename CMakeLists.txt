cmake_minimum_required(VERSION 3.16)
project(plasma-network-audio VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

set(KDE_INSTALL_USE_QT_SYS_PATHS ON)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)

if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endif()

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick DBus)
find_package(KF6 REQUIRED COMPONENTS
    CoreAddons
    I18n
    KCMUtils
    DBusAddons
    Notifications
    Config
)

add_subdirectory(src)
