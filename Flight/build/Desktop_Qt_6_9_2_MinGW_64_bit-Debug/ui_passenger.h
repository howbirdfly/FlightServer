/********************************************************************************
** Form generated from reading UI file 'passenger.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSENGER_H
#define UI_PASSENGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_passenger
{
public:
    QWidget *dockWidgetContents;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *edit_name;
    QLabel *label_2;
    QLineEdit *edit_idcard;
    QLabel *label_3;
    QLineEdit *edit_phone;
    QPushButton *btn_add;
    QGroupBox *groupBox_2;
    QTableWidget *table_passengers;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_refresh;
    QPushButton *btn_close;

    void setupUi(QDockWidget *passenger)
    {
        if (passenger->objectName().isEmpty())
            passenger->setObjectName("passenger");
        passenger->resize(601, 744);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName("dockWidgetContents");
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(20, 10, 551, 161));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 20, 381, 126));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        edit_name = new QLineEdit(formLayoutWidget);
        edit_name->setObjectName("edit_name");
        edit_name->setMaxLength(50);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, edit_name);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        edit_idcard = new QLineEdit(formLayoutWidget);
        edit_idcard->setObjectName("edit_idcard");
        edit_idcard->setMaxLength(18);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, edit_idcard);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        edit_phone = new QLineEdit(formLayoutWidget);
        edit_phone->setObjectName("edit_phone");
        edit_phone->setMaxLength(11);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, edit_phone);

        btn_add = new QPushButton(groupBox);
        btn_add->setObjectName("btn_add");
        btn_add->setGeometry(QRect(432, 47, 91, 41));
        groupBox_2 = new QGroupBox(dockWidgetContents);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(20, 180, 521, 441));
        table_passengers = new QTableWidget(groupBox_2);
        if (table_passengers->columnCount() < 4)
            table_passengers->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_passengers->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_passengers->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_passengers->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        table_passengers->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        table_passengers->setObjectName("table_passengers");
        table_passengers->setGeometry(QRect(15, 41, 501, 381));
        table_passengers->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_passengers->setAlternatingRowColors(true);
        table_passengers->setSelectionMode(QAbstractItemView::SingleSelection);
        table_passengers->setSelectionBehavior(QAbstractItemView::SelectRows);
        horizontalLayoutWidget = new QWidget(dockWidgetContents);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(20, 630, 521, 81));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_refresh = new QPushButton(horizontalLayoutWidget);
        btn_refresh->setObjectName("btn_refresh");

        horizontalLayout->addWidget(btn_refresh);

        btn_close = new QPushButton(horizontalLayoutWidget);
        btn_close->setObjectName("btn_close");

        horizontalLayout->addWidget(btn_close);

        passenger->setWidget(dockWidgetContents);

        retranslateUi(passenger);

        QMetaObject::connectSlotsByName(passenger);
    } // setupUi

    void retranslateUi(QDockWidget *passenger)
    {
        passenger->setWindowTitle(QCoreApplication::translate("passenger", "DockWidget", nullptr));
        groupBox->setTitle(QCoreApplication::translate("passenger", "\346\267\273\345\212\240\346\226\260\344\271\230\345\256\242", nullptr));
        label->setText(QCoreApplication::translate("passenger", "\345\247\223\345\220\215\357\274\232", nullptr));
        edit_name->setPlaceholderText(QCoreApplication::translate("passenger", "\350\257\267\350\276\223\345\205\245\344\271\230\345\256\242\345\247\223\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("passenger", "\350\272\253\344\273\275\350\257\201\357\274\232", nullptr));
        edit_idcard->setInputMask(QCoreApplication::translate("passenger", ">NNNNNNNNNNNNNNNNNN", nullptr));
        edit_idcard->setPlaceholderText(QCoreApplication::translate("passenger", "\350\257\267\350\276\223\345\205\24518\344\275\215\350\272\253\344\273\275\350\257\201\345\217\267\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("passenger", "\346\211\213\346\234\272\345\217\267\357\274\232", nullptr));
        edit_phone->setInputMask(QCoreApplication::translate("passenger", ">99999999999", nullptr));
        edit_phone->setPlaceholderText(QCoreApplication::translate("passenger", "\350\257\267\350\276\223\345\205\24511\344\275\215\346\211\213\346\234\272\345\217\267", nullptr));
        btn_add->setText(QCoreApplication::translate("passenger", "\346\267\273\345\212\240\344\271\230\345\256\242", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("passenger", "\346\210\221\347\232\204\344\271\230\345\256\242\345\210\227\350\241\250", nullptr));
        QTableWidgetItem *___qtablewidgetitem = table_passengers->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("passenger", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_passengers->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("passenger", "\350\272\253\344\273\275\350\257\201", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table_passengers->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("passenger", "\346\211\213\346\234\272\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = table_passengers->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("passenger", "\346\223\215\344\275\234", nullptr));
        btn_refresh->setText(QCoreApplication::translate("passenger", "\345\210\267\346\226\260", nullptr));
        btn_close->setText(QCoreApplication::translate("passenger", "\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class passenger: public Ui_passenger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSENGER_H
