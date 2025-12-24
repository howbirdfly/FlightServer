/********************************************************************************
** Form generated from reading UI file 'userprofile.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPROFILE_H
#define UI_USERPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
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

class Ui_UserProfile
{
public:
    QVBoxLayout *verticalLayout_main;
    QWidget *headerWidget;
    QHBoxLayout *horizontalLayout_header;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_back;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QFormLayout *formLayout;
    QLabel *label_3;
    QLineEdit *txt_Username;
    QLabel *label_5;
    QLineEdit *txt_UserAccount;
    QLabel *label_4;
    QLineEdit *txt_jianjie;
    QLabel *label_6;
    QLineEdit *txt_yu;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_2;
    QGridLayout *gridLayout_buttons;
    QPushButton *pushButton_9;
    QPushButton *btn_recharge;
    QPushButton *pushButton_8;
    QPushButton *pushButton_10;
    QPushButton *btn_favorites;
    QPushButton *pushButton_5;
    QPushButton *pushButton_7;
    QPushButton *pushButton_4;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *UserProfile)
    {
        if (UserProfile->objectName().isEmpty())
            UserProfile->setObjectName("UserProfile");
        UserProfile->resize(1000, 800);
        verticalLayout_main = new QVBoxLayout(UserProfile);
        verticalLayout_main->setSpacing(20);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalLayout_main->setContentsMargins(20, 20, 20, 20);
        headerWidget = new QWidget(UserProfile);
        headerWidget->setObjectName("headerWidget");
        horizontalLayout_header = new QHBoxLayout(headerWidget);
        horizontalLayout_header->setObjectName("horizontalLayout_header");
        horizontalLayout_header->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(headerWidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout_header->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer);

        btn_back = new QPushButton(headerWidget);
        btn_back->setObjectName("btn_back");
        btn_back->setMinimumSize(QSize(80, 32));

        horizontalLayout_header->addWidget(btn_back);


        verticalLayout_main->addWidget(headerWidget);

        frame = new QFrame(UserProfile);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(120, 120));
        label_2->setMaximumSize(QSize(120, 120));
        label_2->setScaledContents(true);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setHorizontalSpacing(15);
        formLayout->setVerticalSpacing(10);
        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_3);

        txt_Username = new QLineEdit(frame);
        txt_Username->setObjectName("txt_Username");
        txt_Username->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, txt_Username);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_5);

        txt_UserAccount = new QLineEdit(frame);
        txt_UserAccount->setObjectName("txt_UserAccount");
        txt_UserAccount->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, txt_UserAccount);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_4);

        txt_jianjie = new QLineEdit(frame);
        txt_jianjie->setObjectName("txt_jianjie");
        txt_jianjie->setReadOnly(true);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, txt_jianjie);

        label_6 = new QLabel(frame);
        label_6->setObjectName("label_6");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_6);

        txt_yu = new QLineEdit(frame);
        txt_yu->setObjectName("txt_yu");
        txt_yu->setReadOnly(true);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, txt_yu);


        horizontalLayout->addLayout(formLayout);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_main->addWidget(frame);

        frame_2 = new QFrame(UserProfile);
        frame_2->setObjectName("frame_2");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_buttons = new QGridLayout(frame_2);
        gridLayout_buttons->setObjectName("gridLayout_buttons");
        gridLayout_buttons->setHorizontalSpacing(40);
        gridLayout_buttons->setVerticalSpacing(20);
        gridLayout_buttons->setContentsMargins(40, 30, 40, 30);
        pushButton_9 = new QPushButton(frame_2);
        pushButton_9->setObjectName("pushButton_9");
        pushButton_9->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(pushButton_9, 2, 1, 1, 1);

        btn_recharge = new QPushButton(frame_2);
        btn_recharge->setObjectName("btn_recharge");
        btn_recharge->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(btn_recharge, 2, 0, 1, 1);

        pushButton_8 = new QPushButton(frame_2);
        pushButton_8->setObjectName("pushButton_8");
        pushButton_8->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(pushButton_8, 0, 1, 1, 1);

        pushButton_10 = new QPushButton(frame_2);
        pushButton_10->setObjectName("pushButton_10");
        pushButton_10->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(pushButton_10, 3, 1, 1, 1);

        btn_favorites = new QPushButton(frame_2);
        btn_favorites->setObjectName("btn_favorites");
        btn_favorites->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(btn_favorites, 3, 0, 1, 1);

        pushButton_5 = new QPushButton(frame_2);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(pushButton_5, 0, 0, 1, 1);

        pushButton_7 = new QPushButton(frame_2);
        pushButton_7->setObjectName("pushButton_7");
        pushButton_7->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(pushButton_7, 1, 1, 1, 1);

        pushButton_4 = new QPushButton(frame_2);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 45));

        gridLayout_buttons->addWidget(pushButton_4, 1, 0, 1, 1);


        verticalLayout_main->addWidget(frame_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        verticalLayout_main->addItem(verticalSpacer);


        retranslateUi(UserProfile);

        QMetaObject::connectSlotsByName(UserProfile);
    } // setupUi

    void retranslateUi(QWidget *UserProfile)
    {
        UserProfile->setWindowTitle(QCoreApplication::translate("UserProfile", "\344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
        label->setText(QCoreApplication::translate("UserProfile", "\344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
        btn_back->setText(QCoreApplication::translate("UserProfile", "\350\277\224\345\233\236", nullptr));
        label_2->setText(QCoreApplication::translate("UserProfile", "\347\205\247\347\211\207", nullptr));
        label_3->setText(QCoreApplication::translate("UserProfile", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("UserProfile", "\350\264\246\345\217\267\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("UserProfile", "\347\256\200\344\273\213\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("UserProfile", "\351\222\261\345\214\205\344\275\231\351\242\235\357\274\232", nullptr));
        pushButton_9->setText(QCoreApplication::translate("UserProfile", "\346\263\250\351\224\200", nullptr));
        btn_recharge->setText(QCoreApplication::translate("UserProfile", "\345\205\205\345\200\274", nullptr));
        pushButton_8->setText(QCoreApplication::translate("UserProfile", "\346\263\250\345\206\214", nullptr));
        pushButton_10->setText(QCoreApplication::translate("UserProfile", "\344\271\230\345\256\242\344\277\241\346\201\257", nullptr));
        btn_favorites->setText(QCoreApplication::translate("UserProfile", "\346\224\266\350\227\217", nullptr));
        pushButton_5->setText(QCoreApplication::translate("UserProfile", "\347\274\226\350\276\221\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        pushButton_7->setText(QCoreApplication::translate("UserProfile", "\347\231\273\345\275\225", nullptr));
        pushButton_4->setText(QCoreApplication::translate("UserProfile", "\346\210\221\347\232\204\350\256\242\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserProfile: public Ui_UserProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPROFILE_H
