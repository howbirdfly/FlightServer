/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_top;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_left;
    QFrame *frame;
    QGridLayout *gridLayout;
    QLabel *Username;
    QLineEdit *Usernamet;
    QLabel *Password;
    QLineEdit *Passwordt;
    QPushButton *log_in;
    QPushButton *sign_in;
    QSpacerItem *horizontalSpacer_right;
    QSpacerItem *verticalSpacer_bottom;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer_top = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_top);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_left = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_left);

        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(400, 280));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(20);
        gridLayout->setContentsMargins(30, 30, 30, 30);
        Username = new QLabel(frame);
        Username->setObjectName("Username");
        Username->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei UI\";"));

        gridLayout->addWidget(Username, 0, 0, 1, 1);

        Usernamet = new QLineEdit(frame);
        Usernamet->setObjectName("Usernamet");
        Usernamet->setMinimumSize(QSize(0, 35));
        Usernamet->setFrame(true);
        Usernamet->setClearButtonEnabled(true);

        gridLayout->addWidget(Usernamet, 0, 1, 1, 2);

        Password = new QLabel(frame);
        Password->setObjectName("Password");
        Password->setStyleSheet(QString::fromUtf8("font: 12pt \"Microsoft YaHei\";"));

        gridLayout->addWidget(Password, 1, 0, 1, 1);

        Passwordt = new QLineEdit(frame);
        Passwordt->setObjectName("Passwordt");
        Passwordt->setMinimumSize(QSize(0, 35));
        Passwordt->setEchoMode(QLineEdit::EchoMode::Password);
        Passwordt->setClearButtonEnabled(true);

        gridLayout->addWidget(Passwordt, 1, 1, 1, 2);

        log_in = new QPushButton(frame);
        log_in->setObjectName("log_in");
        log_in->setMinimumSize(QSize(0, 45));

        gridLayout->addWidget(log_in, 2, 0, 1, 2);

        sign_in = new QPushButton(frame);
        sign_in->setObjectName("sign_in");
        sign_in->setMinimumSize(QSize(0, 45));

        gridLayout->addWidget(sign_in, 2, 2, 1, 1);


        horizontalLayout->addWidget(frame);

        horizontalSpacer_right = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_right);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_bottom = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_bottom);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\210\252\347\217\255\347\256\241\347\220\206\347\263\273\347\273\237 - \347\231\273\345\275\225", nullptr));
        Username->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        Usernamet->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215...", nullptr));
        Password->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201\357\274\232", nullptr));
        Passwordt->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201...", nullptr));
        log_in->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        sign_in->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
