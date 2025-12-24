/********************************************************************************
** Form generated from reading UI file 'sign_in.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_IN_H
#define UI_SIGN_IN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sign_in
{
public:
    QVBoxLayout *verticalLayout_main;
    QSpacerItem *verticalSpacer_top;
    QHBoxLayout *horizontalLayout_center;
    QSpacerItem *horizontalSpacer_left;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *Sign_in_Username;
    QLineEdit *Sign_in_UsernameT;
    QLabel *label;
    QLineEdit *ID;
    QLabel *Sign_in_PassWord;
    QLineEdit *Sign_in_PassWordT;
    QLabel *Sign_in_PassWordA;
    QLineEdit *Sign_in_PassWordAT;
    QHBoxLayout *horizontalLayout_btns;
    QPushButton *Sign_in_Button;
    QPushButton *Sign_in_Cencel;
    QSpacerItem *horizontalSpacer_right;
    QSpacerItem *verticalSpacer_bottom;

    void setupUi(QWidget *Sign_in)
    {
        if (Sign_in->objectName().isEmpty())
            Sign_in->setObjectName("Sign_in");
        Sign_in->resize(1000, 700);
        verticalLayout_main = new QVBoxLayout(Sign_in);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalSpacer_top = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_main->addItem(verticalSpacer_top);

        horizontalLayout_center = new QHBoxLayout();
        horizontalLayout_center->setObjectName("horizontalLayout_center");
        horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_center->addItem(horizontalSpacer_left);

        frame = new QFrame(Sign_in);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(450, 380));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(20);
        gridLayout->setHorizontalSpacing(15);
        gridLayout->setContentsMargins(40, 40, 40, 40);
        Sign_in_Username = new QLabel(frame);
        Sign_in_Username->setObjectName("Sign_in_Username");
        Sign_in_Username->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Sign_in_Username, 0, 0, 1, 1);

        Sign_in_UsernameT = new QLineEdit(frame);
        Sign_in_UsernameT->setObjectName("Sign_in_UsernameT");
        Sign_in_UsernameT->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(Sign_in_UsernameT, 0, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        ID = new QLineEdit(frame);
        ID->setObjectName("ID");
        ID->setMinimumSize(QSize(0, 35));

        gridLayout->addWidget(ID, 1, 1, 1, 1);

        Sign_in_PassWord = new QLabel(frame);
        Sign_in_PassWord->setObjectName("Sign_in_PassWord");
        Sign_in_PassWord->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Sign_in_PassWord, 2, 0, 1, 1);

        Sign_in_PassWordT = new QLineEdit(frame);
        Sign_in_PassWordT->setObjectName("Sign_in_PassWordT");
        Sign_in_PassWordT->setMinimumSize(QSize(0, 35));
        Sign_in_PassWordT->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(Sign_in_PassWordT, 2, 1, 1, 1);

        Sign_in_PassWordA = new QLabel(frame);
        Sign_in_PassWordA->setObjectName("Sign_in_PassWordA");
        Sign_in_PassWordA->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(Sign_in_PassWordA, 3, 0, 1, 1);

        Sign_in_PassWordAT = new QLineEdit(frame);
        Sign_in_PassWordAT->setObjectName("Sign_in_PassWordAT");
        Sign_in_PassWordAT->setMinimumSize(QSize(0, 35));
        Sign_in_PassWordAT->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(Sign_in_PassWordAT, 3, 1, 1, 1);

        horizontalLayout_btns = new QHBoxLayout();
        horizontalLayout_btns->setObjectName("horizontalLayout_btns");
        horizontalLayout_btns->setContentsMargins(-1, 10, -1, -1);
        Sign_in_Button = new QPushButton(frame);
        Sign_in_Button->setObjectName("Sign_in_Button");
        Sign_in_Button->setMinimumSize(QSize(120, 40));
        Sign_in_Button->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_btns->addWidget(Sign_in_Button);

        Sign_in_Cencel = new QPushButton(frame);
        Sign_in_Cencel->setObjectName("Sign_in_Cencel");
        Sign_in_Cencel->setMinimumSize(QSize(120, 40));
        Sign_in_Cencel->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_btns->addWidget(Sign_in_Cencel);


        gridLayout->addLayout(horizontalLayout_btns, 4, 0, 1, 2);


        horizontalLayout_center->addWidget(frame);

        horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_center->addItem(horizontalSpacer_right);


        verticalLayout_main->addLayout(horizontalLayout_center);

        verticalSpacer_bottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_main->addItem(verticalSpacer_bottom);


        retranslateUi(Sign_in);

        QMetaObject::connectSlotsByName(Sign_in);
    } // setupUi

    void retranslateUi(QWidget *Sign_in)
    {
        Sign_in->setWindowTitle(QCoreApplication::translate("Sign_in", "\346\263\250\345\206\214\350\264\246\346\210\267", nullptr));
        Sign_in_Username->setText(QCoreApplication::translate("Sign_in", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        Sign_in_UsernameT->setPlaceholderText(QCoreApplication::translate("Sign_in", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\347\224\250\346\210\267\345\220\215...", nullptr));
        label->setText(QCoreApplication::translate("Sign_in", "\350\264\246\346\210\267ID\357\274\232", nullptr));
        ID->setPlaceholderText(QCoreApplication::translate("Sign_in", "ID\344\270\272\350\264\246\345\217\267\347\232\204\345\224\257\344\270\200\345\207\255\350\257\201", nullptr));
        Sign_in_PassWord->setText(QCoreApplication::translate("Sign_in", "\345\257\206\347\240\201\357\274\232", nullptr));
        Sign_in_PassWordT->setPlaceholderText(QCoreApplication::translate("Sign_in", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\345\257\206\347\240\201...", nullptr));
        Sign_in_PassWordA->setText(QCoreApplication::translate("Sign_in", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", nullptr));
        Sign_in_PassWordAT->setPlaceholderText(QCoreApplication::translate("Sign_in", "\350\257\267\347\241\256\350\256\244\344\275\240\347\232\204\345\257\206\347\240\201...", nullptr));
        Sign_in_Button->setText(QCoreApplication::translate("Sign_in", "\346\263\250\345\206\214", nullptr));
        Sign_in_Cencel->setText(QCoreApplication::translate("Sign_in", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sign_in: public Ui_Sign_in {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_IN_H
