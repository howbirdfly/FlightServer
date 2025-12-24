/********************************************************************************
** Form generated from reading UI file 'passenger.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSENGER_H
#define UI_PASSENGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_passenger
{
public:
    QVBoxLayout *verticalLayout_main;
    QFrame *frame;
    QVBoxLayout *verticalLayout_frame;
    QLabel *label_title;
    QGridLayout *gridLayout_input;
    QLabel *name;
    QLineEdit *edit_name;
    QLabel *id;
    QLineEdit *edit_idcard;
    QLabel *phone;
    QLineEdit *edit_phone;
    QPushButton *btn_add;
    QTableWidget *table_passengers;
    QHBoxLayout *horizontalLayout_btns;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_refresh;
    QPushButton *btn_close;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *passenger)
    {
        if (passenger->objectName().isEmpty())
            passenger->setObjectName(QString::fromUtf8("passenger"));
        passenger->resize(650, 621);
        verticalLayout_main = new QVBoxLayout(passenger);
        verticalLayout_main->setSpacing(0);
        verticalLayout_main->setObjectName(QString::fromUtf8("verticalLayout_main"));
        verticalLayout_main->setContentsMargins(20, 20, 20, 20);
        frame = new QFrame(passenger);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_frame = new QVBoxLayout(frame);
        verticalLayout_frame->setSpacing(15);
        verticalLayout_frame->setObjectName(QString::fromUtf8("verticalLayout_frame"));
        verticalLayout_frame->setContentsMargins(30, 30, 30, 30);
        label_title = new QLabel(frame);
        label_title->setObjectName(QString::fromUtf8("label_title"));
        label_title->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_frame->addWidget(label_title);

        gridLayout_input = new QGridLayout();
        gridLayout_input->setSpacing(15);
        gridLayout_input->setObjectName(QString::fromUtf8("gridLayout_input"));
        name = new QLabel(frame);
        name->setObjectName(QString::fromUtf8("name"));
        name->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_input->addWidget(name, 0, 0, 1, 1);

        edit_name = new QLineEdit(frame);
        edit_name->setObjectName(QString::fromUtf8("edit_name"));

        gridLayout_input->addWidget(edit_name, 0, 1, 1, 1);

        id = new QLabel(frame);
        id->setObjectName(QString::fromUtf8("id"));
        id->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_input->addWidget(id, 0, 2, 1, 1);

        edit_idcard = new QLineEdit(frame);
        edit_idcard->setObjectName(QString::fromUtf8("edit_idcard"));

        gridLayout_input->addWidget(edit_idcard, 0, 3, 1, 1);

        phone = new QLabel(frame);
        phone->setObjectName(QString::fromUtf8("phone"));
        phone->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_input->addWidget(phone, 1, 0, 1, 1);

        edit_phone = new QLineEdit(frame);
        edit_phone->setObjectName(QString::fromUtf8("edit_phone"));

        gridLayout_input->addWidget(edit_phone, 1, 1, 1, 1);

        btn_add = new QPushButton(frame);
        btn_add->setObjectName(QString::fromUtf8("btn_add"));
        btn_add->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout_input->addWidget(btn_add, 1, 3, 1, 1);


        verticalLayout_frame->addLayout(gridLayout_input);

        table_passengers = new QTableWidget(frame);
        if (table_passengers->columnCount() < 3)
            table_passengers->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_passengers->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_passengers->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        table_passengers->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        table_passengers->setObjectName(QString::fromUtf8("table_passengers"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(table_passengers->sizePolicy().hasHeightForWidth());
        table_passengers->setSizePolicy(sizePolicy);
        table_passengers->setColumnCount(3);
        table_passengers->horizontalHeader()->setStretchLastSection(true);
        table_passengers->verticalHeader()->setVisible(false);

        verticalLayout_frame->addWidget(table_passengers);

        horizontalLayout_btns = new QHBoxLayout();
        horizontalLayout_btns->setSpacing(20);
        horizontalLayout_btns->setObjectName(QString::fromUtf8("horizontalLayout_btns"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_btns->addItem(horizontalSpacer);

        btn_refresh = new QPushButton(frame);
        btn_refresh->setObjectName(QString::fromUtf8("btn_refresh"));
        btn_refresh->setMinimumSize(QSize(120, 40));
        btn_refresh->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_btns->addWidget(btn_refresh);

        btn_close = new QPushButton(frame);
        btn_close->setObjectName(QString::fromUtf8("btn_close"));
        btn_close->setMinimumSize(QSize(120, 40));
        btn_close->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_btns->addWidget(btn_close);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_btns->addItem(horizontalSpacer_2);


        verticalLayout_frame->addLayout(horizontalLayout_btns);


        verticalLayout_main->addWidget(frame);


        retranslateUi(passenger);

        QMetaObject::connectSlotsByName(passenger);
    } // setupUi

    void retranslateUi(QWidget *passenger)
    {
        passenger->setWindowTitle(QCoreApplication::translate("passenger", "\344\271\230\345\256\242\344\277\241\346\201\257", nullptr));
        label_title->setText(QCoreApplication::translate("passenger", "\344\271\230\345\256\242\344\277\241\346\201\257\347\256\241\347\220\206", nullptr));
        name->setText(QCoreApplication::translate("passenger", "\345\247\223\345\220\215\357\274\232", nullptr));
        edit_name->setPlaceholderText(QCoreApplication::translate("passenger", "\350\257\267\350\276\223\345\205\245\344\271\230\345\256\242\345\247\223\345\220\215", nullptr));
        id->setText(QCoreApplication::translate("passenger", "\350\272\253\344\273\275\350\257\201\345\217\267\357\274\232", nullptr));
        edit_idcard->setPlaceholderText(QCoreApplication::translate("passenger", "\350\257\267\350\276\223\345\205\24518\344\275\215\350\272\253\344\273\275\350\257\201\345\217\267\347\240\201", nullptr));
        phone->setText(QCoreApplication::translate("passenger", "\347\224\265\350\257\235\345\217\267\347\240\201\357\274\232", nullptr));
        edit_phone->setPlaceholderText(QCoreApplication::translate("passenger", "\350\257\267\350\276\223\345\205\245\350\201\224\347\263\273\347\224\265\350\257\235", nullptr));
        btn_add->setText(QCoreApplication::translate("passenger", "\346\267\273\345\212\240\344\271\230\345\256\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem = table_passengers->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("passenger", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_passengers->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("passenger", "\350\272\253\344\273\275\350\257\201\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = table_passengers->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("passenger", "\347\224\265\350\257\235\345\217\267\347\240\201", nullptr));
        btn_refresh->setText(QCoreApplication::translate("passenger", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        btn_close->setText(QCoreApplication::translate("passenger", "\345\205\263\351\227\255\351\241\265\351\235\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class passenger: public Ui_passenger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSENGER_H
