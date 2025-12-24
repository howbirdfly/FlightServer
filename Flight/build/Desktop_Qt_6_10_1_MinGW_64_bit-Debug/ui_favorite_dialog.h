/********************************************************************************
** Form generated from reading UI file 'favorite_dialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FAVORITE_DIALOG_H
#define UI_FAVORITE_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
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

class Ui_favorite_dialog
{
public:
    QVBoxLayout *verticalLayout_main;
    QHBoxLayout *horizontalLayout_header;
    QLabel *label_title;
    QPushButton *btn_refresh;
    QPushButton *btn_back;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_datebegin;
    QDateEdit *dateEdit_begin;
    QLabel *label_dateend;
    QDateEdit *dateEdit_end;
    QSpacerItem *horizontalSpacer;
    QLabel *label_dep;
    QLineEdit *lineEdit_dep;
    QLabel *label_arr;
    QLineEdit *lineEdit_arr;
    QPushButton *searchBtn;
    QTableWidget *tableWidget_favorites;

    void setupUi(QWidget *favorite_dialog)
    {
        if (favorite_dialog->objectName().isEmpty())
            favorite_dialog->setObjectName("favorite_dialog");
        favorite_dialog->resize(1000, 700);
        favorite_dialog->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_main = new QVBoxLayout(favorite_dialog);
        verticalLayout_main->setSpacing(15);
        verticalLayout_main->setObjectName("verticalLayout_main");
        verticalLayout_main->setContentsMargins(20, 20, 20, 20);
        horizontalLayout_header = new QHBoxLayout();
        horizontalLayout_header->setSpacing(6);
        horizontalLayout_header->setObjectName("horizontalLayout_header");
        horizontalLayout_header->setSizeConstraint(QLayout::SizeConstraint::SetNoConstraint);
        label_title = new QLabel(favorite_dialog);
        label_title->setObjectName("label_title");
        label_title->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_header->addWidget(label_title);

        btn_refresh = new QPushButton(favorite_dialog);
        btn_refresh->setObjectName("btn_refresh");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btn_refresh->sizePolicy().hasHeightForWidth());
        btn_refresh->setSizePolicy(sizePolicy);
        btn_refresh->setMinimumSize(QSize(100, 32));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("view-refresh")));
        btn_refresh->setIcon(icon);

        horizontalLayout_header->addWidget(btn_refresh);

        btn_back = new QPushButton(favorite_dialog);
        btn_back->setObjectName("btn_back");
        sizePolicy.setHeightForWidth(btn_back->sizePolicy().hasHeightForWidth());
        btn_back->setSizePolicy(sizePolicy);
        btn_back->setMinimumSize(QSize(100, 32));
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("go-previous")));
        btn_back->setIcon(icon1);

        horizontalLayout_header->addWidget(btn_back);


        verticalLayout_main->addLayout(horizontalLayout_header);

        groupBox = new QGroupBox(favorite_dialog);
        groupBox->setObjectName("groupBox");
        groupBox->setMinimumSize(QSize(0, 100));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        label_datebegin = new QLabel(groupBox);
        label_datebegin->setObjectName("label_datebegin");
        label_datebegin->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_datebegin, 0, 0, 1, 1);

        dateEdit_begin = new QDateEdit(groupBox);
        dateEdit_begin->setObjectName("dateEdit_begin");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dateEdit_begin->sizePolicy().hasHeightForWidth());
        dateEdit_begin->setSizePolicy(sizePolicy1);
        dateEdit_begin->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit_begin, 0, 1, 2, 1);

        label_dateend = new QLabel(groupBox);
        label_dateend->setObjectName("label_dateend");
        label_dateend->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_dateend, 0, 2, 1, 1);

        dateEdit_end = new QDateEdit(groupBox);
        dateEdit_end->setObjectName("dateEdit_end");
        sizePolicy1.setHeightForWidth(dateEdit_end->sizePolicy().hasHeightForWidth());
        dateEdit_end->setSizePolicy(sizePolicy1);
        dateEdit_end->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit_end, 0, 3, 2, 1);

        horizontalSpacer = new QSpacerItem(148, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 2, 1);

        label_dep = new QLabel(groupBox);
        label_dep->setObjectName("label_dep");
        label_dep->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_dep, 2, 0, 1, 1);

        lineEdit_dep = new QLineEdit(groupBox);
        lineEdit_dep->setObjectName("lineEdit_dep");
        sizePolicy1.setHeightForWidth(lineEdit_dep->sizePolicy().hasHeightForWidth());
        lineEdit_dep->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_dep, 2, 1, 1, 1);

        label_arr = new QLabel(groupBox);
        label_arr->setObjectName("label_arr");
        label_arr->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        gridLayout->addWidget(label_arr, 2, 2, 1, 1);

        lineEdit_arr = new QLineEdit(groupBox);
        lineEdit_arr->setObjectName("lineEdit_arr");
        sizePolicy1.setHeightForWidth(lineEdit_arr->sizePolicy().hasHeightForWidth());
        lineEdit_arr->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_arr, 2, 3, 1, 1);

        searchBtn = new QPushButton(groupBox);
        searchBtn->setObjectName("searchBtn");
        sizePolicy1.setHeightForWidth(searchBtn->sizePolicy().hasHeightForWidth());
        searchBtn->setSizePolicy(sizePolicy1);
        searchBtn->setMinimumSize(QSize(90, 40));
        searchBtn->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));

        gridLayout->addWidget(searchBtn, 2, 5, 1, 1);


        verticalLayout_main->addWidget(groupBox);

        tableWidget_favorites = new QTableWidget(favorite_dialog);
        if (tableWidget_favorites->columnCount() < 9)
            tableWidget_favorites->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_favorites->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tableWidget_favorites->setObjectName("tableWidget_favorites");
        tableWidget_favorites->setAlternatingRowColors(true);
        tableWidget_favorites->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableWidget_favorites->setVerticalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        tableWidget_favorites->setHorizontalScrollMode(QAbstractItemView::ScrollMode::ScrollPerPixel);
        tableWidget_favorites->setShowGrid(true);
        tableWidget_favorites->horizontalHeader()->setHighlightSections(false);
        tableWidget_favorites->horizontalHeader()->setStretchLastSection(true);
        tableWidget_favorites->verticalHeader()->setVisible(false);

        verticalLayout_main->addWidget(tableWidget_favorites);


        retranslateUi(favorite_dialog);

        QMetaObject::connectSlotsByName(favorite_dialog);
    } // setupUi

    void retranslateUi(QWidget *favorite_dialog)
    {
        favorite_dialog->setWindowTitle(QCoreApplication::translate("favorite_dialog", "\346\210\221\347\232\204\346\224\266\350\227\217\345\244\271", nullptr));
        label_title->setText(QCoreApplication::translate("favorite_dialog", "\346\210\221\347\232\204\346\224\266\350\227\217", nullptr));
        btn_refresh->setText(QCoreApplication::translate("favorite_dialog", "\345\210\267\346\226\260", nullptr));
        btn_back->setText(QCoreApplication::translate("favorite_dialog", "\350\277\224\345\233\236", nullptr));
        groupBox->setTitle(QCoreApplication::translate("favorite_dialog", "\346\220\234\347\264\242", nullptr));
        label_datebegin->setText(QCoreApplication::translate("favorite_dialog", "\345\274\200\345\247\213\346\227\245\346\234\237\357\274\232", nullptr));
        label_dateend->setText(QCoreApplication::translate("favorite_dialog", "\347\273\223\346\235\237\346\227\245\346\234\237\357\274\232", nullptr));
        label_dep->setText(QCoreApplication::translate("favorite_dialog", "\345\207\272\345\217\221\345\234\260\357\274\232", nullptr));
        lineEdit_dep->setPlaceholderText(QCoreApplication::translate("favorite_dialog", "\344\276\213\345\246\202\357\274\232\345\214\227\344\272\254", nullptr));
        label_arr->setText(QCoreApplication::translate("favorite_dialog", "\347\233\256\347\232\204\345\234\260\357\274\232", nullptr));
        lineEdit_arr->setPlaceholderText(QCoreApplication::translate("favorite_dialog", "\344\276\213\345\246\202\357\274\232\344\270\212\346\265\267", nullptr));
        searchBtn->setText(QCoreApplication::translate("favorite_dialog", "\346\220\234\347\264\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_favorites->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("favorite_dialog", "\347\261\273\345\236\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_favorites->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("favorite_dialog", "\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_favorites->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("favorite_dialog", "\345\207\272\345\217\221\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_favorites->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("favorite_dialog", "\347\233\256\347\232\204\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_favorites->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("favorite_dialog", "\345\207\272\345\217\221\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_favorites->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("favorite_dialog", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_favorites->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("favorite_dialog", "\344\273\267\346\240\274\357\274\210\345\205\203\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_favorites->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("favorite_dialog", "\345\205\254\345\217\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_favorites->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("favorite_dialog", "\346\224\266\350\227\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class favorite_dialog: public Ui_favorite_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FAVORITE_DIALOG_H
