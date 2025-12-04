/********************************************************************************
** Form generated from reading UI file 'edit_infor.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDIT_INFOR_H
#define UI_EDIT_INFOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_edit_infor
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QPushButton *pushButton;
    QLabel *label_3;
    QLineEdit *old_name;
    QLabel *label_2;
    QLineEdit *new_name;
    QLabel *label_4;
    QLineEdit *new_jianjie;
    QLabel *label_5;

    void setupUi(QDialog *edit_infor)
    {
        if (edit_infor->objectName().isEmpty())
            edit_infor->setObjectName("edit_infor");
        edit_infor->resize(650, 380);
        edit_infor->setStyleSheet(QString::fromUtf8("/* ================= \345\205\250\345\261\200\347\252\227\345\217\243\350\256\276\347\275\256 ================= */\n"
"QDialog {\n"
"    background-color: #ffffff;\n"
"    color: #333333;\n"
"    font-family: \"Microsoft YaHei\", \"Segoe UI\", sans-serif;\n"
"}\n"
"\n"
"/* ================= \346\240\207\347\255\276 (Label) \346\240\267\345\274\217 ================= */\n"
"QLabel {\n"
"    color: #333333;\n"
"    font-size: 14px;\n"
"    font-weight: bold;\n"
"    background: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"/* ================= \350\276\223\345\205\245\346\241\206 (LineEdit) \346\240\267\345\274\217 ================= */\n"
"QLineEdit {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #cccccc;\n"
"    border-radius: 4px;\n"
"    color: #000000;\n"
"    padding: 5px 8px;\n"
"    font-size: 14px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #0078d7;\n"
"}\n"
"\n"
"/* \345\217\252\350\257\273\350\276\223\345\205\245\346\241\206\346\240\267\345\274\217 */\n"
"QLineEdit[rea"
                        "dOnly=\"true\"] {\n"
"    background-color: #f7f7f7;\n"
"    color: #555555;\n"
"    border: 1px solid #dddddd;\n"
"}\n"
"\n"
"/* ================= \346\214\211\351\222\256 (PushButton) \346\240\267\345\274\217 ================= */\n"
"QPushButton {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdcdc;\n"
"    border-bottom: 2px solid #b0b0b0;\n"
"    border-radius: 6px;\n"
"    color: #333333;\n"
"    font-size: 14px;\n"
"    padding: 6px 16px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #f0f8ff;\n"
"    border-color: #0078d7;\n"
"    color: #0078d7;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #e0e0e0;\n"
"    border-top: 2px solid #b0b0b0;\n"
"    border-bottom: none;\n"
"    padding-top: 8px;\n"
"    padding-bottom: 4px;\n"
"}\n"
"\n"
"/* ================= \345\244\264\345\203\217\351\242\204\350\247\210\346\241\206\346\240\267\345\274\217 ================= */\n"
"QLabel#label_5 {\n"
"    background-color: #f0f0f0;\n"
"    border: 2px solid #dcdcdc;\n"
"  "
                        "  border-radius: 8px;\n"
"}"));
        buttonBox = new QDialogButtonBox(edit_infor);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(190, 310, 211, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        label = new QLabel(edit_infor);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 50, 111, 19));
        pushButton = new QPushButton(edit_infor);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(160, 45, 161, 32));
        label_3 = new QLabel(edit_infor);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 100, 69, 19));
        old_name = new QLineEdit(edit_infor);
        old_name->setObjectName("old_name");
        old_name->setGeometry(QRect(160, 95, 221, 31));
        old_name->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        old_name->setReadOnly(true);
        label_2 = new QLabel(edit_infor);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 160, 69, 19));
        label_2->setStyleSheet(QString::fromUtf8(""));
        new_name = new QLineEdit(edit_infor);
        new_name->setObjectName("new_name");
        new_name->setGeometry(QRect(160, 155, 221, 31));
        label_4 = new QLabel(edit_infor);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(60, 220, 69, 19));
        new_jianjie = new QLineEdit(edit_infor);
        new_jianjie->setObjectName("new_jianjie");
        new_jianjie->setGeometry(QRect(160, 215, 221, 31));
        label_5 = new QLabel(edit_infor);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(450, 45, 131, 160));
        label_5->setScaledContents(false);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(edit_infor);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, edit_infor, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, edit_infor, qOverload<>(&QDialog::reject));

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
    } // retranslateUi

};

namespace Ui {
    class edit_infor: public Ui_edit_infor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDIT_INFOR_H
