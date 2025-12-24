/****************************************************************************
** Meta object code from reading C++ file 'edit_infor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../edit_infor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'edit_infor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_edit_infor_t {
    QByteArrayData data[18];
    char stringdata0[202];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_edit_infor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_edit_infor_t qt_meta_stringdata_edit_infor = {
    {
QT_MOC_LITERAL(0, 0, 10), // "edit_infor"
QT_MOC_LITERAL(1, 11, 11), // "change_name"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "QString&"
QT_MOC_LITERAL(4, 33, 7), // "oldname"
QT_MOC_LITERAL(5, 41, 7), // "newname"
QT_MOC_LITERAL(6, 49, 14), // "change_jianjie"
QT_MOC_LITERAL(7, 64, 10), // "oldjianjie"
QT_MOC_LITERAL(8, 75, 7), // "jianjie"
QT_MOC_LITERAL(9, 83, 13), // "change_avatar"
QT_MOC_LITERAL(10, 97, 6), // "pixmap"
QT_MOC_LITERAL(11, 104, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(12, 126, 21), // "onGetUserInfoResponse"
QT_MOC_LITERAL(13, 148, 7), // "msgType"
QT_MOC_LITERAL(14, 156, 7), // "success"
QT_MOC_LITERAL(15, 164, 7), // "message"
QT_MOC_LITERAL(16, 172, 4), // "data"
QT_MOC_LITERAL(17, 177, 24) // "onUpdateUserInfoResponse"

    },
    "edit_infor\0change_name\0\0QString&\0"
    "oldname\0newname\0change_jianjie\0"
    "oldjianjie\0jianjie\0change_avatar\0"
    "pixmap\0on_pushButton_clicked\0"
    "onGetUserInfoResponse\0msgType\0success\0"
    "message\0data\0onUpdateUserInfoResponse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_edit_infor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    2,   49,    2, 0x06 /* Public */,
       9,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   57,    2, 0x08 /* Private */,
      12,    4,   58,    2, 0x08 /* Private */,
      17,    4,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    7,    8,
    QMetaType::Void, QMetaType::QPixmap,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   13,   14,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   13,   14,   15,   16,

       0        // eod
};

void edit_infor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<edit_infor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change_name((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->change_jianjie((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->change_avatar((*reinterpret_cast< const QPixmap(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_clicked(); break;
        case 4: _t->onGetUserInfoResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 5: _t->onUpdateUserInfoResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (edit_infor::*)(QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&edit_infor::change_name)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (edit_infor::*)(QString & , QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&edit_infor::change_jianjie)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (edit_infor::*)(const QPixmap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&edit_infor::change_avatar)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject edit_infor::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_edit_infor.data,
    qt_meta_data_edit_infor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *edit_infor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *edit_infor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_edit_infor.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int edit_infor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void edit_infor::change_name(QString & _t1, QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void edit_infor::change_jianjie(QString & _t1, QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void edit_infor::change_avatar(const QPixmap & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
