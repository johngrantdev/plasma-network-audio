/****************************************************************************
** Meta object code from reading C++ file 'avahi_browser.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/avahi_browser.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'avahi_browser.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12AvahiBrowserE_t {};
} // unnamed namespace

template <> constexpr inline auto AvahiBrowser::qt_create_metaobjectdata<qt_meta_tag_ZN12AvahiBrowserE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AvahiBrowser",
        "deviceDiscovered",
        "",
        "NetworkAudioDevice",
        "device",
        "deviceRemoved",
        "id",
        "onItemNew",
        "interface",
        "protocol",
        "name",
        "type",
        "domain",
        "flags",
        "onItemRemove",
        "onResolverFound",
        "host",
        "aprotocol",
        "address",
        "port",
        "QList<QByteArray>",
        "txt"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'deviceDiscovered'
        QtMocHelpers::SignalData<void(const NetworkAudioDevice &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'deviceRemoved'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 6 },
        }}),
        // Slot 'onItemNew'
        QtMocHelpers::SlotData<void(int, int, const QString &, const QString &, const QString &, uint)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::Int, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 },
            { QMetaType::QString, 12 }, { QMetaType::UInt, 13 },
        }}),
        // Slot 'onItemRemove'
        QtMocHelpers::SlotData<void(int, int, const QString &, const QString &, const QString &, uint)>(14, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::Int, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 },
            { QMetaType::QString, 12 }, { QMetaType::UInt, 13 },
        }}),
        // Slot 'onResolverFound'
        QtMocHelpers::SlotData<void(int, int, const QString &, const QString &, const QString &, const QString &, int, const QString &, quint16, const QList<QByteArray> &, uint)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 8 }, { QMetaType::Int, 9 }, { QMetaType::QString, 10 }, { QMetaType::QString, 11 },
            { QMetaType::QString, 12 }, { QMetaType::QString, 16 }, { QMetaType::Int, 17 }, { QMetaType::QString, 18 },
            { QMetaType::UShort, 19 }, { 0x80000000 | 20, 21 }, { QMetaType::UInt, 13 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AvahiBrowser, qt_meta_tag_ZN12AvahiBrowserE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AvahiBrowser::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12AvahiBrowserE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12AvahiBrowserE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12AvahiBrowserE_t>.metaTypes,
    nullptr
} };

void AvahiBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AvahiBrowser *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->deviceDiscovered((*reinterpret_cast<std::add_pointer_t<NetworkAudioDevice>>(_a[1]))); break;
        case 1: _t->deviceRemoved((*reinterpret_cast<std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onItemNew((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<uint>>(_a[6]))); break;
        case 3: _t->onItemRemove((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<uint>>(_a[6]))); break;
        case 4: _t->onResolverFound((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[5])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[6])),(*reinterpret_cast<std::add_pointer_t<int>>(_a[7])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[8])),(*reinterpret_cast<std::add_pointer_t<quint16>>(_a[9])),(*reinterpret_cast<std::add_pointer_t<QList<QByteArray>>>(_a[10])),(*reinterpret_cast<std::add_pointer_t<uint>>(_a[11]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 9:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QByteArray> >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AvahiBrowser::*)(const NetworkAudioDevice & )>(_a, &AvahiBrowser::deviceDiscovered, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (AvahiBrowser::*)(const QString & )>(_a, &AvahiBrowser::deviceRemoved, 1))
            return;
    }
}

const QMetaObject *AvahiBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AvahiBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12AvahiBrowserE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int AvahiBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AvahiBrowser::deviceDiscovered(const NetworkAudioDevice & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void AvahiBrowser::deviceRemoved(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}
QT_WARNING_POP
