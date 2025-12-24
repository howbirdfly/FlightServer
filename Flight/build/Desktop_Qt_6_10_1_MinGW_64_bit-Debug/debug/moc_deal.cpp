/****************************************************************************
** Meta object code from reading C++ file 'deal.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../deal.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deal.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.1. It"
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
struct qt_meta_tag_ZN4DealE_t {};
} // unnamed namespace

template <> constexpr inline auto Deal::qt_create_metaobjectdata<qt_meta_tag_ZN4DealE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Deal",
        "on_Single_Center_clicked",
        "",
        "on_btn_search_clicked",
        "on_favorite_button_clicked",
        "on_Deal_2_clicked",
        "onBookTicket",
        "onAddFavorite",
        "refreshTicketList",
        "showTicketSearchPage",
        "on_Avatar_clicked",
        "onSearchResponse",
        "msgType",
        "success",
        "message",
        "QJsonObject",
        "data",
        "onAddFavoriteResponse",
        "onGetUserInfoForAvatar",
        "on_lineEdit_pageNum_returnPressed",
        "updatePageContainerText",
        "on_home_clicked"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'on_Single_Center_clicked'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_btn_search_clicked'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_favorite_button_clicked'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Deal_2_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onBookTicket'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onAddFavorite'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'refreshTicketList'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showTicketSearchPage'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_Avatar_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSearchResponse'
        QtMocHelpers::SlotData<void(int, bool, const QString &, const QJsonObject &)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::Bool, 13 }, { QMetaType::QString, 14 }, { 0x80000000 | 15, 16 },
        }}),
        // Slot 'onAddFavoriteResponse'
        QtMocHelpers::SlotData<void(int, bool, const QString &, const QJsonObject &)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::Bool, 13 }, { QMetaType::QString, 14 }, { 0x80000000 | 15, 16 },
        }}),
        // Slot 'onGetUserInfoForAvatar'
        QtMocHelpers::SlotData<void(int, bool, const QString &, const QJsonObject &)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 }, { QMetaType::Bool, 13 }, { QMetaType::QString, 14 }, { 0x80000000 | 15, 16 },
        }}),
        // Slot 'on_lineEdit_pageNum_returnPressed'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'updatePageContainerText'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_home_clicked'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Deal, qt_meta_tag_ZN4DealE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Deal::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4DealE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4DealE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN4DealE_t>.metaTypes,
    nullptr
} };

void Deal::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Deal *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
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
        case 9: _t->onSearchResponse((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[4]))); break;
        case 10: _t->onAddFavoriteResponse((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[4]))); break;
        case 11: _t->onGetUserInfoForAvatar((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QString>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<QJsonObject>>(_a[4]))); break;
        case 12: _t->on_lineEdit_pageNum_returnPressed(); break;
        case 13: _t->updatePageContainerText(); break;
        case 14: _t->on_home_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *Deal::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Deal::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN4DealE_t>.strings))
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
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 15;
    }
    return _id;
}
QT_WARNING_POP
