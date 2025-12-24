/****************************************************************************
** Meta object code from reading C++ file 'deal.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../deal.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Deal_t {
    QByteArrayData data[21];
    char stringdata0[347];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Deal_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Deal_t qt_meta_stringdata_Deal = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Deal"
QT_MOC_LITERAL(1, 5, 24), // "on_Single_Center_clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 21), // "on_btn_search_clicked"
QT_MOC_LITERAL(4, 53, 26), // "on_favorite_button_clicked"
QT_MOC_LITERAL(5, 80, 17), // "on_Deal_2_clicked"
QT_MOC_LITERAL(6, 98, 12), // "onBookTicket"
QT_MOC_LITERAL(7, 111, 13), // "onAddFavorite"
QT_MOC_LITERAL(8, 125, 17), // "refreshTicketList"
QT_MOC_LITERAL(9, 143, 20), // "showTicketSearchPage"
QT_MOC_LITERAL(10, 164, 17), // "on_Avatar_clicked"
QT_MOC_LITERAL(11, 182, 16), // "onSearchResponse"
QT_MOC_LITERAL(12, 199, 7), // "msgType"
QT_MOC_LITERAL(13, 207, 7), // "success"
QT_MOC_LITERAL(14, 215, 7), // "message"
QT_MOC_LITERAL(15, 223, 4), // "data"
QT_MOC_LITERAL(16, 228, 21), // "onAddFavoriteResponse"
QT_MOC_LITERAL(17, 250, 22), // "onGetUserInfoForAvatar"
QT_MOC_LITERAL(18, 273, 33), // "on_lineEdit_pageNum_returnPre..."
QT_MOC_LITERAL(19, 307, 23), // "updatePageContainerText"
QT_MOC_LITERAL(20, 331, 15) // "on_home_clicked"

    },
    "Deal\0on_Single_Center_clicked\0\0"
    "on_btn_search_clicked\0on_favorite_button_clicked\0"
    "on_Deal_2_clicked\0onBookTicket\0"
    "onAddFavorite\0refreshTicketList\0"
    "showTicketSearchPage\0on_Avatar_clicked\0"
    "onSearchResponse\0msgType\0success\0"
    "message\0data\0onAddFavoriteResponse\0"
    "onGetUserInfoForAvatar\0"
    "on_lineEdit_pageNum_returnPressed\0"
    "updatePageContainerText\0on_home_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Deal[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    0,   97,    2, 0x08 /* Private */,
      11,    4,   98,    2, 0x08 /* Private */,
      16,    4,  107,    2, 0x08 /* Private */,
      17,    4,  116,    2, 0x08 /* Private */,
      18,    0,  125,    2, 0x08 /* Private */,
      19,    0,  126,    2, 0x08 /* Private */,
      20,    0,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   12,   13,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   12,   13,   14,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString, QMetaType::QJsonObject,   12,   13,   14,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Deal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Deal *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Single_Center_clicked(); break;
        case 1: _t->on_btn_search_clicked(); break;
        case 2: _t->on_favorite_button_clicked(); break;
        case 3: _t->on_Deal_2_clicked(); break;
        case 4: _t->onBookTicket(); break;
        case 5: _t->onAddFavorite(); break;
        case 6: _t->refreshTicketList(); break;
        case 7: _t->showTicketSearchPage(); break;
        case 8: _t->on_Avatar_clicked(); break;
        case 9: _t->onSearchResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 10: _t->onAddFavoriteResponse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 11: _t->onGetUserInfoForAvatar((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QJsonObject(*)>(_a[4]))); break;
        case 12: _t->on_lineEdit_pageNum_returnPressed(); break;
        case 13: _t->updatePageContainerText(); break;
        case 14: _t->on_home_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Deal::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Deal.data,
    qt_meta_data_Deal,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Deal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Deal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Deal.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Deal::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
