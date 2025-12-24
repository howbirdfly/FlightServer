/****************************************************************************
** Meta object code from reading C++ file 'single_center.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../single_center.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'single_center.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Single_Center_t {
    QByteArrayData data[15];
    char stringdata0[196];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Single_Center_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Single_Center_t qt_meta_stringdata_Single_Center = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Single_Center"
QT_MOC_LITERAL(1, 14, 13), // "backRequested"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 13), // "onCancelOrder"
QT_MOC_LITERAL(4, 43, 13), // "onDeleteOrder"
QT_MOC_LITERAL(5, 57, 11), // "onViewOrder"
QT_MOC_LITERAL(6, 69, 19), // "on_btn_back_clicked"
QT_MOC_LITERAL(7, 89, 19), // "onGetOrdersResponse"
QT_MOC_LITERAL(8, 109, 7), // "msgType"
QT_MOC_LITERAL(9, 117, 7), // "success"
QT_MOC_LITERAL(10, 125, 7), // "message"
QT_MOC_LITERAL(11, 133, 4), // "data"
QT_MOC_LITERAL(12, 138, 21), // "onCancelOrderResponse"
QT_MOC_LITERAL(13, 160, 13), // "onAddFavorite"
QT_MOC_LITERAL(14, 174, 21) // "onAddFavoriteResponse"

    },
    "Single_Center\0backRequested\0\0onCancelOrder\0"
    "onDeleteOrder\0onViewOrder\0on_btn_back_clicked\0"
    "onGetOrdersResponse\0msgType\0success\0"
    "message\0data\0onCancelOrderResponse\0"
    "onAddFavorite\0onAddFavoriteResponse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Single_Center[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    4,   64,    2, 0x08 /* Private */,
      12,    4,   73,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    4,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,    8,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,    8,    9,   10,   11,

       0        // eod
};

void Single_Center::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Single_Center *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->onCancelOrder(); break;
        case 2: _t->onDeleteOrder(); break;
        case 3: _t->onViewOrder(); break;
        case 4: _t->on_btn_back_clicked(); break;
        case 5: _t->onGetOrdersResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 6: _t->onCancelOrderResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 7: _t->onAddFavorite(); break;
        case 8: _t->onAddFavoriteResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Single_Center::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Single_Center::backRequested)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Single_Center::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Single_Center.data,
    qt_meta_data_Single_Center,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Single_Center::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Single_Center::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Single_Center.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Single_Center::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Single_Center::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
