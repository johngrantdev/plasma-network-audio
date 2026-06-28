/****************************************************************************
** Meta object code from reading C++ file 'network_audio_adaptor.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/network_audio_adaptor.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'network_audio_adaptor.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN19NetworkAudioAdaptorE_t {};
} // unnamed namespace

template <> constexpr inline auto NetworkAudioAdaptor::qt_create_metaobjectdata<qt_meta_tag_ZN19NetworkAudioAdaptorE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "NetworkAudioAdaptor",
        "D-Bus Interface",
        "org.kde.NetworkAudio",
        "deviceDiscovered",
        "",
        "QVariantMap",
        "device",
        "deviceRemoved",
        "id",
        "deviceConnected",
        "deviceDisconnected",
        "deviceError",
        "message",
        "deviceUpdated",
        "devices",
        "QList<QVariantMap>",
        "connectDevice",
        "disconnectDevice",
        "setAutoConnect",
        "enabled",
        "ignoreDevice",
        "forgetDevice"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'deviceDiscovered'
        QtMocHelpers::SignalData<void(const QVariantMap &)>(3, 4, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Signal 'deviceRemoved'
        QtMocHelpers::SignalData<void(const QString &)>(7, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'deviceConnected'
        QtMocHelpers::SignalData<void(const QString &)>(9, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'deviceDisconnected'
        QtMocHelpers::SignalData<void(const QString &)>(10, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Signal 'deviceError'
        QtMocHelpers::SignalData<void(const QString &, const QString &)>(11, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 }, { QMetaType::QString, 12 },
        }}),
        // Signal 'deviceUpdated'
        QtMocHelpers::SignalData<void(const QVariantMap &)>(13, 4, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'devices'
        QtMocHelpers::SlotData<QList<QVariantMap>() const>(14, 4, QMC::AccessPublic, 0x80000000 | 15),
        // Slot 'connectDevice'
        QtMocHelpers::SlotData<void(const QString &)>(16, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Slot 'disconnectDevice'
        QtMocHelpers::SlotData<void(const QString &)>(17, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Slot 'setAutoConnect'
        QtMocHelpers::SlotData<void(const QString &, bool)>(18, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 }, { QMetaType::Bool, 19 },
        }}),
        // Slot 'ignoreDevice'
        QtMocHelpers::SlotData<void(const QString &)>(20, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
        // Slot 'forgetDevice'
        QtMocHelpers::SlotData<void(const QString &)>(21, 4, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 8 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    QtMocHelpers::UintData qt_constructors {};
    QtMocHelpers::ClassInfos qt_classinfo({
            {    1,    2 },
    });
    return QtMocHelpers::metaObjectData<NetworkAudioAdaptor, qt_meta_tag_ZN19NetworkAudioAdaptorE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_constructors, qt_classinfo);
}
Q_CONSTINIT const QMetaObject NetworkAudioAdaptor::staticMetaObject = { {
    QMetaObject::SuperData::link<QDBusAbstractAdaptor::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NetworkAudioAdaptorE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NetworkAudioAdaptorE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN19NetworkAudioAdaptorE_t>.metaTypes,
    nullptr
} };

void NetworkAudioAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<NetworkAudioAdaptor *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->deviceDiscovered((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 1: _t->deviceRemoved((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->deviceConnected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->deviceDisconnected((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->deviceError((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[2]))); break;
        case 5: _t->deviceUpdated((*reinterpret_cast<std::add_pointer_t<QVariantMap>>(_a[1]))); break;
        case 6: { QList<QVariantMap> _r = _t->devices();
            if (_a[0]) *reinterpret_cast<QList<QVariantMap>*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->connectDevice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->disconnectDevice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->setAutoConnect((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2]))); break;
        case 10: _t->ignoreDevice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->forgetDevice((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (NetworkAudioAdaptor::*)(const QVariantMap & )>(_a, &NetworkAudioAdaptor::deviceDiscovered, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkAudioAdaptor::*)(const QString & )>(_a, &NetworkAudioAdaptor::deviceRemoved, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkAudioAdaptor::*)(const QString & )>(_a, &NetworkAudioAdaptor::deviceConnected, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkAudioAdaptor::*)(const QString & )>(_a, &NetworkAudioAdaptor::deviceDisconnected, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkAudioAdaptor::*)(const QString & , const QString & )>(_a, &NetworkAudioAdaptor::deviceError, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (NetworkAudioAdaptor::*)(const QVariantMap & )>(_a, &NetworkAudioAdaptor::deviceUpdated, 5))
            return;
    }
}

const QMetaObject *NetworkAudioAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkAudioAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN19NetworkAudioAdaptorE_t>.strings))
        return static_cast<void*>(this);
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int NetworkAudioAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void NetworkAudioAdaptor::deviceDiscovered(const QVariantMap & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void NetworkAudioAdaptor::deviceRemoved(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void NetworkAudioAdaptor::deviceConnected(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void NetworkAudioAdaptor::deviceDisconnected(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void NetworkAudioAdaptor::deviceError(const QString & _t1, const QString & _t2)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1, _t2);
}

// SIGNAL 5
void NetworkAudioAdaptor::deviceUpdated(const QVariantMap & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}
QT_WARNING_POP
