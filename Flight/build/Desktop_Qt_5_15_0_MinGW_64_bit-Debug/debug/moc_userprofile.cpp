/****************************************************************************
** Meta object code from reading C++ file 'userprofile.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../userprofile.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'userprofile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UserProfile_t {
    QByteArrayData data[23];
    char stringdata0[376];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UserProfile_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UserProfile_t qt_meta_stringdata_UserProfile = {
    {
QT_MOC_LITERAL(0, 0, 11), // "UserProfile"
QT_MOC_LITERAL(1, 12, 13), // "backRequested"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 17), // "myOrdersRequested"
QT_MOC_LITERAL(4, 45, 15), // "logoutRequested"
QT_MOC_LITERAL(5, 61, 20), // "myFavoritesRequested"
QT_MOC_LITERAL(6, 82, 13), // "avatarUpdated"
QT_MOC_LITERAL(7, 96, 7), // "getData"
QT_MOC_LITERAL(8, 104, 6), // "userID"
QT_MOC_LITERAL(9, 111, 19), // "on_btn_back_clicked"
QT_MOC_LITERAL(10, 131, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(11, 155, 23), // "on_pushButton_8_clicked"
QT_MOC_LITERAL(12, 179, 23), // "on_pushButton_7_clicked"
QT_MOC_LITERAL(13, 203, 23), // "on_pushButton_9_clicked"
QT_MOC_LITERAL(14, 227, 24), // "on_pushButton_10_clicked"
QT_MOC_LITERAL(15, 252, 23), // "on_pushButton_5_clicked"
QT_MOC_LITERAL(16, 276, 24), // "on_btn_favorites_clicked"
QT_MOC_LITERAL(17, 301, 23), // "on_btn_recharge_clicked"
QT_MOC_LITERAL(18, 325, 21), // "onGetUserInfoResponse"
QT_MOC_LITERAL(19, 347, 7), // "msgType"
QT_MOC_LITERAL(20, 355, 7), // "success"
QT_MOC_LITERAL(21, 363, 7), // "message"
QT_MOC_LITERAL(22, 371, 4) // "data"

    },
    "UserProfile\0backRequested\0\0myOrdersRequested\0"
    "logoutRequested\0myFavoritesRequested\0"
    "avatarUpdated\0getData\0userID\0"
    "on_btn_back_clicked\0on_pushButton_4_clicked\0"
    "on_pushButton_8_clicked\0on_pushButton_7_clicked\0"
    "on_pushButton_9_clicked\0"
    "on_pushButton_10_clicked\0"
    "on_pushButton_5_clicked\0"
    "on_btn_favorites_clicked\0"
    "on_btn_recharge_clicked\0onGetUserInfoResponse\0"
    "msgType\0success\0message\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UserProfile[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,
       4,    0,   96,    2, 0x06 /* Public */,
       5,    0,   97,    2, 0x06 /* Public */,
       6,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   99,    2, 0x0a /* Public */,
       9,    0,  102,    2, 0x08 /* Private */,
      10,    0,  103,    2, 0x08 /* Private */,
      11,    0,  104,    2, 0x08 /* Private */,
      12,    0,  105,    2, 0x08 /* Private */,
      13,    0,  106,    2, 0x08 /* Private */,
      14,    0,  107,    2, 0x08 /* Private */,
      15,    0,  108,    2, 0x08 /* Private */,
      16,    0,  109,    2, 0x08 /* Private */,
      17,    0,  110,    2, 0x08 /* Private */,
      18,    4,  111,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   19,   20,   21,   22,

       0        // eod
};

void UserProfile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserProfile *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->myOrdersRequested(); break;
        case 2: _t->logoutRequested(); break;
        case 3: _t->myFavoritesRequested(); break;
        case 4: _t->avatarUpdated(); break;
        case 5: _t->getData((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->on_btn_back_clicked(); break;
        case 7: _t->on_pushButton_4_clicked(); break;
        case 8: _t->on_pushButton_8_clicked(); break;
        case 9: _t->on_pushButton_7_clicked(); break;
        case 10: _t->on_pushButton_9_clicked(); break;
        case 11: _t->on_pushButton_10_clicked(); break;
        case 12: _t->on_pushButton_5_clicked(); break;
        case 13: _t->on_btn_favorites_clicked(); break;
        case 14: _t->on_btn_recharge_clicked(); break;
        case 15: _t->onGetUserInfoResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UserProfile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserProfile::backRequested)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UserProfile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserProfile::myOrdersRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UserProfile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserProfile::logoutRequested)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UserProfile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserProfile::myFavoritesRequested)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UserProfile::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserProfile::avatarUpdated)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UserProfile::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_UserProfile.data,
    qt_meta_data_UserProfile,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UserProfile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UserProfile::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UserProfile.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UserProfile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void UserProfile::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void UserProfile::myOrdersRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void UserProfile::logoutRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void UserProfile::myFavoritesRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void UserProfile::avatarUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
