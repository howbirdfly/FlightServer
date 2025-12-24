/********************************************************************************
** Form generated from reading UI file 'single_center.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SINGLE_CENTER_H
#define UI_SINGLE_CENTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Single_Center
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_title;
    QPushButton *btn_back;
    QPushButton *btn_refresh;
    QTableWidget *tableWidget_orders;

    void setupUi(QWidget *Single_Center)
    {
        if (Single_Center->objectName().isEmpty())
            Single_Center->setObjectName("Single_Center");
        Single_Center->resize(1000, 700);
        verticalLayout = new QVBoxLayout(Single_Center);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(20, 20, 20, 20);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName("horizontalLayout");
        label_title = new QLabel(Single_Center);
        label_title->setObjectName("label_title");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_title->sizePolicy().hasHeightForWidth());
        label_title->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label_title->setFont(font);

        horizontalLayout->addWidget(label_title);

        btn_back = new QPushButton(Single_Center);
        btn_back->setObjectName("btn_back");
        btn_back->setMinimumSize(QSize(80, 32));

        horizontalLayout->addWidget(btn_back);

        btn_refresh = new QPushButton(Single_Center);
        btn_refresh->setObjectName("btn_refresh");
        btn_refresh->setMinimumSize(QSize(80, 32));

        horizontalLayout->addWidget(btn_refresh);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget_orders = new QTableWidget(Single_Center);
        tableWidget_orders->setObjectName("tableWidget_orders");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget_orders->sizePolicy().hasHeightForWidth());
        tableWidget_orders->setSizePolicy(sizePolicy1);
        tableWidget_orders->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget_orders->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget_orders->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget_orders);


        retranslateUi(Single_Center);

        QMetaObject::connectSlotsByName(Single_Center);
    } // setupUi

    void retranslateUi(QWidget *Single_Center)
    {
        Single_Center->setWindowTitle(QCoreApplication::translate("Single_Center", "\344\270\252\344\272\272\344\270\255\345\277\203 - \346\210\221\347\232\204\350\256\242\345\215\225", nullptr));
        label_title->setText(QCoreApplication::translate("Single_Center", "\346\210\221\347\232\204\350\256\242\345\215\225", nullptr));
        btn_back->setText(QCoreApplication::translate("Single_Center", "\350\277\224\345\233\236", nullptr));
        btn_refresh->setText(QCoreApplication::translate("Single_Center", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Single_Center: public Ui_Single_Center {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SINGLE_CENTER_H
