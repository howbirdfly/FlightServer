/********************************************************************************
** Form generated from reading UI file 'edit_infor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_INFOR_H
#define UI_EDIT_INFOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_edit_infor
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_top;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_3;
    QLineEdit *old_name;
    QLabel *label_2;
    QLineEdit *new_name;
    QLabel *label_4;
    QLineEdit *new_jianjie;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_bottom;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *edit_infor)
    {
        if (edit_infor->objectName().isEmpty())
            edit_infor->setObjectName(QString::fromUtf8("edit_infor"));
        edit_infor->resize(650, 380);
        verticalLayout = new QVBoxLayout(edit_infor);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(40, 40, 40, 20);
        verticalSpacer_top = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_top);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(30);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setVerticalSpacing(20);
        label = new QLabel(edit_infor);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton = new QPushButton(edit_infor);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 1, 1, 1);

        label_3 = new QLabel(edit_infor);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        old_name = new QLineEdit(edit_infor);
        old_name->setObjectName(QString::fromUtf8("old_name"));
        old_name->setFocusPolicy(Qt::NoFocus);
        old_name->setReadOnly(true);

        gridLayout->addWidget(old_name, 1, 1, 1, 1);

        label_2 = new QLabel(edit_infor);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        new_name = new QLineEdit(edit_infor);
        new_name->setObjectName(QString::fromUtf8("new_name"));

        gridLayout->addWidget(new_name, 2, 1, 1, 1);

        label_4 = new QLabel(edit_infor);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        new_jianjie = new QLineEdit(edit_infor);
        new_jianjie->setObjectName(QString::fromUtf8("new_jianjie"));

        gridLayout->addWidget(new_jianjie, 3, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        label_5 = new QLabel(edit_infor);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(130, 160));
        label_5->setScaledContents(false);
        label_5->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_5);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_bottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_bottom);

        buttonBox = new QDialogButtonBox(edit_infor);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(edit_infor);
        QObject::connect(buttonBox, SIGNAL(accepted()), edit_infor, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), edit_infor, SLOT(reject()));

        QMetaObject::connectSlotsByName(edit_infor);
    } // setupUi

    void retranslateUi(QDialog *edit_infor)
    {
        edit_infor->setWindowTitle(QCoreApplication::translate("edit_infor", "\347\274\226\350\276\221\344\270\252\344\272\272\344\277\241\346\201\257", nullptr));
        label->setText(QCoreApplication::translate("edit_infor", "\350\256\276\347\275\256\344\275\240\347\232\204\347\205\247\347\211\207\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("edit_infor", "\351\200\211\346\213\251\346\234\254\345\234\260\345\233\276\347\211\207", nullptr));
        label_3->setText(QCoreApplication::translate("edit_infor", "\345\216\237\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        old_name->setPlaceholderText(QCoreApplication::translate("edit_infor", "\345\275\223\345\211\215\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("edit_infor", "\346\226\260\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        new_name->setPlaceholderText(QCoreApplication::translate("edit_infor", "\350\257\267\350\276\223\345\205\245\346\226\260\347\232\204\347\224\250\346\210\267\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("edit_infor", "\347\256\200\344\273\213\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("edit_infor", "\345\244\264\345\203\217\351\242\204\350\247\210", nullptr));
        label_5->setStyleSheet(QCoreApplication::translate("edit_infor", "border: 1px dashed #aaa;", nullptr));
    } // retranslateUi

};

namespace Ui {
    class edit_infor: public Ui_edit_infor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_INFOR_H
