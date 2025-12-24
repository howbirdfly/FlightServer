/********************************************************************************
** Form generated from reading UI file 'pay.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAY_H
#define UI_PAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Pay
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_title;
    QGroupBox *groupBox_payment;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_amount;
    QLabel *label_amount_text;
    QLabel *label_amount;
    QHBoxLayout *horizontalLayout_qr;
    QLabel *label_wechat_img;
    QLabel *label_alipay_img;
    QHBoxLayout *horizontalLayout_label;
    QLabel *label_wechat;
    QLabel *label_alipay;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_pay;
    QDoubleSpinBox *spinBox_amount;
    QHBoxLayout *horizontalLayout_buttons;
    QPushButton *btn_cancel;
    QPushButton *btn_confirm;

    void setupUi(QWidget *Pay)
    {
        if (Pay->objectName().isEmpty())
            Pay->setObjectName("Pay");
        Pay->resize(690, 621);
        Pay->setAutoFillBackground(true);
        Pay->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(Pay);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(30, 30, 30, 30);
        label_title = new QLabel(Pay);
        label_title->setObjectName("label_title");

        verticalLayout->addWidget(label_title);

        groupBox_payment = new QGroupBox(Pay);
        groupBox_payment->setObjectName("groupBox_payment");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_payment->sizePolicy().hasHeightForWidth());
        groupBox_payment->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(groupBox_payment);
        verticalLayout_2->setSpacing(20);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, -1, -1, 30);
        horizontalLayout_amount = new QHBoxLayout();
        horizontalLayout_amount->setObjectName("horizontalLayout_amount");
        label_amount_text = new QLabel(groupBox_payment);
        label_amount_text->setObjectName("label_amount_text");
        QFont font;
        font.setFamilies({QString::fromUtf8("Microsoft YaHei")});
        font.setBold(true);
        label_amount_text->setFont(font);
        label_amount_text->setStyleSheet(QString::fromUtf8("font-size: 16px;"));
        label_amount_text->setTextFormat(Qt::AutoText);
        label_amount_text->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_amount->addWidget(label_amount_text);

        label_amount = new QLabel(groupBox_payment);
        label_amount->setObjectName("label_amount");
        label_amount->setFont(font);
        label_amount->setStyleSheet(QString::fromUtf8("color: #f56c6c; font-size: 24px;"));

        horizontalLayout_amount->addWidget(label_amount);


        verticalLayout_2->addLayout(horizontalLayout_amount);

        horizontalLayout_qr = new QHBoxLayout();
        horizontalLayout_qr->setSpacing(40);
        horizontalLayout_qr->setObjectName("horizontalLayout_qr");
        label_wechat_img = new QLabel(groupBox_payment);
        label_wechat_img->setObjectName("label_wechat_img");
        label_wechat_img->setMinimumSize(QSize(180, 180));
        label_wechat_img->setMaximumSize(QSize(180, 180));
        label_wechat_img->setScaledContents(true);
        label_wechat_img->setAlignment(Qt::AlignCenter);

        horizontalLayout_qr->addWidget(label_wechat_img);

        label_alipay_img = new QLabel(groupBox_payment);
        label_alipay_img->setObjectName("label_alipay_img");
        label_alipay_img->setMinimumSize(QSize(180, 180));
        label_alipay_img->setMaximumSize(QSize(180, 180));
        label_alipay_img->setScaledContents(true);
        label_alipay_img->setAlignment(Qt::AlignCenter);

        horizontalLayout_qr->addWidget(label_alipay_img);


        verticalLayout_2->addLayout(horizontalLayout_qr);

        horizontalLayout_label = new QHBoxLayout();
        horizontalLayout_label->setObjectName("horizontalLayout_label");
        horizontalLayout_label->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_wechat = new QLabel(groupBox_payment);
        label_wechat->setObjectName("label_wechat");
        label_wechat->setLayoutDirection(Qt::LeftToRight);
        label_wechat->setAlignment(Qt::AlignCenter);

        horizontalLayout_label->addWidget(label_wechat);

        label_alipay = new QLabel(groupBox_payment);
        label_alipay->setObjectName("label_alipay");
        label_alipay->setAlignment(Qt::AlignCenter);

        horizontalLayout_label->addWidget(label_alipay);


        verticalLayout_2->addLayout(horizontalLayout_label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_pay = new QLabel(groupBox_payment);
        label_pay->setObjectName("label_pay");
        label_pay->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_pay);

        spinBox_amount = new QDoubleSpinBox(groupBox_payment);
        spinBox_amount->setObjectName("spinBox_amount");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox_amount->sizePolicy().hasHeightForWidth());
        spinBox_amount->setSizePolicy(sizePolicy1);
        spinBox_amount->setMaximum(100000.000000000000000);

        horizontalLayout_3->addWidget(spinBox_amount);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout->addWidget(groupBox_payment);

        horizontalLayout_buttons = new QHBoxLayout();
        horizontalLayout_buttons->setSpacing(15);
        horizontalLayout_buttons->setObjectName("horizontalLayout_buttons");
        btn_cancel = new QPushButton(Pay);
        btn_cancel->setObjectName("btn_cancel");
        btn_cancel->setMinimumSize(QSize(100, 36));

        horizontalLayout_buttons->addWidget(btn_cancel);

        btn_confirm = new QPushButton(Pay);
        btn_confirm->setObjectName("btn_confirm");
        btn_confirm->setMinimumSize(QSize(100, 36));
        btn_confirm->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        horizontalLayout_buttons->addWidget(btn_confirm);


        verticalLayout->addLayout(horizontalLayout_buttons);


        retranslateUi(Pay);

        QMetaObject::connectSlotsByName(Pay);
    } // setupUi

    void retranslateUi(QWidget *Pay)
    {
        Pay->setWindowTitle(QCoreApplication::translate("Pay", "\346\224\266\351\223\266\345\217\260", nullptr));
        label_title->setText(QCoreApplication::translate("Pay", "\350\256\242\345\215\225\346\224\257\344\273\230", nullptr));
        groupBox_payment->setTitle(QCoreApplication::translate("Pay", "\346\211\253\347\240\201\346\224\257\344\273\230", nullptr));
        label_amount_text->setText(QCoreApplication::translate("Pay", "\346\224\257\344\273\230\351\207\221\351\242\235\357\274\232", nullptr));
        label_amount->setText(QCoreApplication::translate("Pay", "\302\245 0.00", nullptr));
        label_wechat_img->setText(QCoreApplication::translate("Pay", "\345\276\256\344\277\241\344\272\214\347\273\264\347\240\201", nullptr));
        label_alipay_img->setText(QCoreApplication::translate("Pay", "\346\224\257\344\273\230\345\256\235\344\272\214\347\273\264\347\240\201", nullptr));
        label_wechat->setText(QCoreApplication::translate("Pay", "\345\276\256\344\277\241\346\224\257\344\273\230", nullptr));
        label_alipay->setText(QCoreApplication::translate("Pay", "\346\224\257\344\273\230\345\256\235\346\224\257\344\273\230", nullptr));
        label_pay->setText(QCoreApplication::translate("Pay", "\345\205\205\345\200\274\351\207\221\351\242\235\357\274\232", nullptr));
        spinBox_amount->setPrefix(QCoreApplication::translate("Pay", "\302\245", nullptr));
        btn_cancel->setText(QCoreApplication::translate("Pay", "\345\217\226\346\266\210", nullptr));
        btn_confirm->setText(QCoreApplication::translate("Pay", "\346\210\221\345\267\262\346\224\257\344\273\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Pay: public Ui_Pay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAY_H
