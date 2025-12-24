/****************************************************************************
** Meta object code from reading C++ file 'favorite_dialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../favorite_dialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'favorite_dialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_favorite_dialog_t {
    QByteArrayData data[13];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_favorite_dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_favorite_dialog_t qt_meta_stringdata_favorite_dialog = {
    {
QT_MOC_LITERAL(0, 0, 15), // "favorite_dialog"
QT_MOC_LITERAL(1, 16, 13), // "backRequested"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 19), // "on_btn_back_clicked"
QT_MOC_LITERAL(4, 51, 22), // "on_btn_refresh_clicked"
QT_MOC_LITERAL(5, 74, 20), // "on_searchBtn_clicked"
QT_MOC_LITERAL(6, 95, 16), // "onRemoveFavorite"
QT_MOC_LITERAL(7, 112, 22), // "onGetFavoritesResponse"
QT_MOC_LITERAL(8, 135, 7), // "msgType"
QT_MOC_LITERAL(9, 143, 7), // "success"
QT_MOC_LITERAL(10, 151, 7), // "message"
QT_MOC_LITERAL(11, 159, 4), // "data"
QT_MOC_LITERAL(12, 164, 24) // "onDeleteFavoriteResponse"

    },
    "favorite_dialog\0backRequested\0\0"
    "on_btn_back_clicked\0on_btn_refresh_clicked\0"
    "on_searchBtn_clicked\0onRemoveFavorite\0"
    "onGetFavoritesResponse\0msgType\0success\0"
    "message\0data\0onDeleteFavoriteResponse"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_favorite_dialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    4,   54,    2, 0x08 /* Private */,
      12,    4,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,    8,    9,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,    8,    9,   10,   11,

       0        // eod
};

void favorite_dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<favorite_dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->on_btn_back_clicked(); break;
        case 2: _t->on_btn_refresh_clicked(); break;
        case 3: _t->on_searchBtn_clicked(); break;
        case 4: _t->onRemoveFavorite(); break;
        case 5: _t->onGetFavoritesResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 6: _t->onDeleteFavoriteResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (favorite_dialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&favorite_dialog::backRequested)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject favorite_dialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_favorite_dialog.data,
    qt_meta_data_favorite_dialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *favorite_dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *favorite_dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_favorite_dialog.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int favorite_dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void favorite_dialog::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
