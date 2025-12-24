/****************************************************************************
** Meta object code from reading C++ file 'passenger.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../passenger.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'passenger.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_passenger_t {
    QByteArrayData data[21];
    char stringdata0[280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_passenger_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_passenger_t qt_meta_stringdata_passenger = {
    {
QT_MOC_LITERAL(0, 0, 9), // "passenger"
QT_MOC_LITERAL(1, 10, 13), // "backRequested"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "passengerSelected"
QT_MOC_LITERAL(4, 43, 4), // "name"
QT_MOC_LITERAL(5, 48, 6), // "idCard"
QT_MOC_LITERAL(6, 55, 5), // "phone"
QT_MOC_LITERAL(7, 61, 18), // "on_btn_add_clicked"
QT_MOC_LITERAL(8, 80, 22), // "on_btn_refresh_clicked"
QT_MOC_LITERAL(9, 103, 20), // "on_btn_close_clicked"
QT_MOC_LITERAL(10, 124, 17), // "onDeletePassenger"
QT_MOC_LITERAL(11, 142, 24), // "onPassengerDoubleClicked"
QT_MOC_LITERAL(12, 167, 3), // "row"
QT_MOC_LITERAL(13, 171, 6), // "column"
QT_MOC_LITERAL(14, 178, 23), // "onGetPassengersResponse"
QT_MOC_LITERAL(15, 202, 7), // "msgType"
QT_MOC_LITERAL(16, 210, 7), // "success"
QT_MOC_LITERAL(17, 218, 7), // "message"
QT_MOC_LITERAL(18, 226, 4), // "data"
QT_MOC_LITERAL(19, 231, 22), // "onAddPassengerResponse"
QT_MOC_LITERAL(20, 254, 25) // "onDeletePassengerResponse"

    },
    "passenger\0backRequested\0\0passengerSelected\0"
    "name\0idCard\0phone\0on_btn_add_clicked\0"
    "on_btn_refresh_clicked\0on_btn_close_clicked\0"
    "onDeletePassenger\0onPassengerDoubleClicked\0"
    "row\0column\0onGetPassengersResponse\0"
    "msgType\0success\0message\0data\0"
    "onAddPassengerResponse\0onDeletePassengerResponse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_passenger[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    3,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   72,    2, 0x08 /* Private */,
       8,    0,   73,    2, 0x08 /* Private */,
       9,    0,   74,    2, 0x08 /* Private */,
      10,    0,   75,    2, 0x08 /* Private */,
      11,    2,   76,    2, 0x08 /* Private */,
      14,    4,   81,    2, 0x08 /* Private */,
      19,    4,   90,    2, 0x08 /* Private */,
      20,    4,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   15,   16,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   15,   16,   17,   18,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   15,   16,   17,   18,

       0        // eod
};

void passenger::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<passenger *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->passengerSelected((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: _t->on_btn_add_clicked(); break;
        case 3: _t->on_btn_refresh_clicked(); break;
        case 4: _t->on_btn_close_clicked(); break;
        case 5: _t->onDeletePassenger(); break;
        case 6: _t->onPassengerDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->onGetPassengersResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 8: _t->onAddPassengerResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 9: _t->onDeletePassengerResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (passenger::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&passenger::backRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (passenger::*)(const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&passenger::passengerSelected)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject passenger::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_passenger.data,
    qt_meta_data_passenger,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *passenger::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *passenger::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_passenger.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int passenger::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void passenger::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void passenger::passengerSelected(const QString & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
