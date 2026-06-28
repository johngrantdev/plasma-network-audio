/****************************************************************************
** Meta object code from reading C++ file 'network_audio_kcm.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/network_audio_kcm.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network_audio_kcm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN15NetworkAudioKCME_t {};
} // unnamed namespace

template <> constexpr inline auto NetworkAudioKCM::qt_create_metaobjectdata<qt_meta_tag_ZN15NetworkAudioKCME_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NetworkAudioKCM",
        "lastErrorChanged",
        "",
        "onDeviceDiscovered",
        "QVariantMap",
        "device",
        "onDeviceRemoved",
        "id",
        "onDeviceConnected",
        "onDeviceDisconnected",
        "onDeviceError",
        "message",
        "onDeviceUpdated",
        "connectDevice",
        "disconnectDevice",
        "setAutoConnect",
        "enabled",
        "forgetDevice",
        "clearLastError",
        "deviceModel",
        "NetworkAudioModel*",
        "lastError"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'lastErrorChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'onDeviceDiscovered'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(3, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Slot 'onDeviceRemoved'
        QtMocHelpers::SlotData<void(const QString &)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'onDeviceConnected'
        QtMocHelpers::SlotData<void(const QString &)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'onDeviceDisconnected'
        QtMocHelpers::SlotData<void(const QString &)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'onDeviceError'
        QtMocHelpers::SlotData<void(const QString &, const QString &)>(10, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::QString, 11 },
        }}),
        // Slot 'onDeviceUpdated'
        QtMocHelpers::SlotData<void(const QVariantMap &)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 4, 5 },
        }}),
        // Method 'connectDevice'
        QtMocHelpers::MethodData<void(const QString &)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'disconnectDevice'
        QtMocHelpers::MethodData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'setAutoConnect'
        QtMocHelpers::MethodData<void(const QString &, bool)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 }, { QMetaType::Bool, 16 },
        }}),
        // Method 'forgetDevice'
        QtMocHelpers::MethodData<void(const QString &)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Method 'clearLastError'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'deviceModel'
        QtMocHelpers::PropertyData<NetworkAudioModel*>(19, 0x80000000 | 20, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
        // property 'lastError'
        QtMocHelpers::PropertyData<QString>(21, QMetaType::QString, QMC::DefaultPropertyFlags, 0),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<NetworkAudioKCM, qt_meta_tag_ZN15NetworkAudioKCME_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject NetworkAudioKCM::staticMetaObject = { {
    QMetaObject::SuperData::link<KQuickConfigModule::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15NetworkAudioKCME_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15NetworkAudioKCME_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN15NetworkAudioKCME_t>.metaTypes,
    nullptr
} };

void NetworkAudioKCM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NetworkAudioKCM *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->lastErrorChanged(); break;
        case 1: _t->onDeviceDiscovered((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 2: _t->onDeviceRemoved((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->onDeviceConnected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->onDeviceDisconnected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onDeviceError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 6: _t->onDeviceUpdated((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 7: _t->connectDevice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->disconnectDevice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->setAutoConnect((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 10: _t->forgetDevice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->clearLastError(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NetworkAudioKCM::*)()>(_a, &NetworkAudioKCM::lastErrorChanged, 0))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< NetworkAudioModel* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<NetworkAudioModel**>(_v) = _t->deviceModel(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->lastError(); break;
        default: break;
        }
    }
}

const QMetaObject *NetworkAudioKCM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkAudioKCM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN15NetworkAudioKCME_t>.strings))
        return static_cast<void*>(this);
    return KQuickConfigModule::qt_metacast(_clname);
}

int NetworkAudioKCM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KQuickConfigModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void NetworkAudioKCM::lastErrorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
