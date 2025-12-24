/********************************************************************************
** Form generated from reading UI file 'deal.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEAL_H
#define UI_DEAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Deal
{
public:
    QVBoxLayout *verticalLayout_main;
    QFrame *HeaderBar;
    QHBoxLayout *horizontalLayout_header;
    QLabel *Title;
    QSpacerItem *horizontalSpacer_header;
    QPushButton *Avatar;
    QHBoxLayout *horizontalLayout_body;
    QFrame *btn_frame;
    QVBoxLayout *verticalLayout_sidebar;
    QPushButton *home;
    QPushButton *Deal_2;
    QPushButton *favorite_button;
    QPushButton *Single_Center;
    QSpacerItem *verticalSpacer_sidebar;
    QStackedWidget *stackedWidget;
    QWidget *page_tickets;
    QVBoxLayout *verticalLayout_content;
    QGroupBox *searchGroup;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_search_2;
    QLabel *label_from;
    QLineEdit *lineEdit_from;
    QLabel *label_to;
    QLineEdit *lineEdit_to;
    QLabel *label_date;
    QDateEdit *dateEdit;
    QSpacerItem *horizontalSpacer_search_3;
    QPushButton *btn_search;
    QSpacerItem *horizontalSpacer_search;
    QTableWidget *tableWidget_tickets;
    QFrame *paginationFrame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_pag_left;
    QPushButton *btn_prev;
    QLabel *label_pageInfo_2;
    QLineEdit *lineEdit_pageNum;
    QLabel *label_pageInfo;
    QPushButton *btn_next;
    QSpacerItem *horizontalSpacer_pag_right;

    void setupUi(QWidget *Deal)
    {
        if (Deal->objectName().isEmpty())
            Deal->setObjectName(QString::fromUtf8("Deal"));
        Deal->resize(1270, 900);
        verticalLayout_main = new QVBoxLayout(Deal);
        verticalLayout_main->setSpacing(0);
        verticalLayout_main->setObjectName(QString::fromUtf8("verticalLayout_main"));
        verticalLayout_main->setContentsMargins(0, 0, 0, 0);
        HeaderBar = new QFrame(Deal);
        HeaderBar->setObjectName(QString::fromUtf8("HeaderBar"));
        HeaderBar->setMinimumSize(QSize(0, 71));
        HeaderBar->setMaximumSize(QSize(16777215, 71));
        HeaderBar->setFrameShape(QFrame::Shape::StyledPanel);
        HeaderBar->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_header = new QHBoxLayout(HeaderBar);
        horizontalLayout_header->setObjectName(QString::fromUtf8("horizontalLayout_header"));
        Title = new QLabel(HeaderBar);
        Title->setObjectName(QString::fromUtf8("Title"));
        Title->setMinimumSize(QSize(151, 31));

        horizontalLayout_header->addWidget(Title);

        horizontalSpacer_header = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_header->addItem(horizontalSpacer_header);

        Avatar = new QPushButton(HeaderBar);
        Avatar->setObjectName(QString::fromUtf8("Avatar"));
        Avatar->setMinimumSize(QSize(41, 41));
        Avatar->setFlat(true);

        horizontalLayout_header->addWidget(Avatar);


        verticalLayout_main->addWidget(HeaderBar);

        horizontalLayout_body = new QHBoxLayout();
        horizontalLayout_body->setSpacing(0);
        horizontalLayout_body->setObjectName(QString::fromUtf8("horizontalLayout_body"));
        btn_frame = new QFrame(Deal);
        btn_frame->setObjectName(QString::fromUtf8("btn_frame"));
        btn_frame->setMinimumSize(QSize(231, 0));
        btn_frame->setMaximumSize(QSize(231, 16777215));
        btn_frame->setFrameShape(QFrame::Shape::StyledPanel);
        btn_frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_sidebar = new QVBoxLayout(btn_frame);
        verticalLayout_sidebar->setSpacing(30);
        verticalLayout_sidebar->setObjectName(QString::fromUtf8("verticalLayout_sidebar"));
        verticalLayout_sidebar->setContentsMargins(30, 90, 20, -1);
        home = new QPushButton(btn_frame);
        home->setObjectName(QString::fromUtf8("home"));
        home->setMinimumSize(QSize(0, 51));
        home->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_sidebar->addWidget(home);

        Deal_2 = new QPushButton(btn_frame);
        Deal_2->setObjectName(QString::fromUtf8("Deal_2"));
        Deal_2->setMinimumSize(QSize(0, 51));
        Deal_2->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_sidebar->addWidget(Deal_2);

        favorite_button = new QPushButton(btn_frame);
        favorite_button->setObjectName(QString::fromUtf8("favorite_button"));
        favorite_button->setMinimumSize(QSize(0, 51));
        favorite_button->setStyleSheet(QString::fromUtf8("color: #000000;"));

        verticalLayout_sidebar->addWidget(favorite_button);

        Single_Center = new QPushButton(btn_frame);
        Single_Center->setObjectName(QString::fromUtf8("Single_Center"));
        Single_Center->setMinimumSize(QSize(0, 51));
        Single_Center->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_sidebar->addWidget(Single_Center);

        verticalSpacer_sidebar = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_sidebar->addItem(verticalSpacer_sidebar);


        horizontalLayout_body->addWidget(btn_frame);

        stackedWidget = new QStackedWidget(Deal);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setAutoFillBackground(true);
        page_tickets = new QWidget();
        page_tickets->setObjectName(QString::fromUtf8("page_tickets"));
        page_tickets->setEnabled(true);
        verticalLayout_content = new QVBoxLayout(page_tickets);
        verticalLayout_content->setObjectName(QString::fromUtf8("verticalLayout_content"));
        searchGroup = new QGroupBox(page_tickets);
        searchGroup->setObjectName(QString::fromUtf8("searchGroup"));
        searchGroup->setMinimumSize(QSize(0, 80));
        searchGroup->setAutoFillBackground(false);
        searchGroup->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(searchGroup);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_search_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_search_2);

        label_from = new QLabel(searchGroup);
        label_from->setObjectName(QString::fromUtf8("label_from"));
        label_from->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_from);

        lineEdit_from = new QLineEdit(searchGroup);
        lineEdit_from->setObjectName(QString::fromUtf8("lineEdit_from"));
        lineEdit_from->setMinimumSize(QSize(100, 25));
        lineEdit_from->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(lineEdit_from);

        label_to = new QLabel(searchGroup);
        label_to->setObjectName(QString::fromUtf8("label_to"));
        label_to->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_to);

        lineEdit_to = new QLineEdit(searchGroup);
        lineEdit_to->setObjectName(QString::fromUtf8("lineEdit_to"));
        lineEdit_to->setMinimumSize(QSize(100, 25));
        lineEdit_to->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(lineEdit_to);

        label_date = new QLabel(searchGroup);
        label_date->setObjectName(QString::fromUtf8("label_date"));
        label_date->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_date);

        dateEdit = new QDateEdit(searchGroup);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setMinimumSize(QSize(120, 33));
        dateEdit->setStyleSheet(QString::fromUtf8(""));
        dateEdit->setCalendarPopup(true);

        horizontalLayout->addWidget(dateEdit);

        horizontalSpacer_search_3 = new QSpacerItem(30, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_search_3);

        btn_search = new QPushButton(searchGroup);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));
        btn_search->setMinimumSize(QSize(81, 41));
        btn_search->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(btn_search);

        horizontalSpacer_search = new QSpacerItem(30, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_search);


        verticalLayout_content->addWidget(searchGroup);

        tableWidget_tickets = new QTableWidget(page_tickets);
        if (tableWidget_tickets->columnCount() < 10)
            tableWidget_tickets->setColumnCount(10);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_tickets->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        tableWidget_tickets->setObjectName(QString::fromUtf8("tableWidget_tickets"));
        tableWidget_tickets->setAutoFillBackground(false);
        tableWidget_tickets->setStyleSheet(QString::fromUtf8(""));
        tableWidget_tickets->setFrameShadow(QFrame::Shadow::Sunken);
        tableWidget_tickets->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableWidget_tickets->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

        verticalLayout_content->addWidget(tableWidget_tickets);

        paginationFrame = new QFrame(page_tickets);
        paginationFrame->setObjectName(QString::fromUtf8("paginationFrame"));
        paginationFrame->setMinimumSize(QSize(0, 51));
        paginationFrame->setStyleSheet(QString::fromUtf8("QFrame#paginationFrame {\n"
"    background-color: #7bed9f;\n"
"    color: #333333;\n"
"    border: 1px solid #6bda8d;\n"
"    border-radius: 6px;\n"
"    padding: 0px;\n"
"}"));
        paginationFrame->setFrameShape(QFrame::Shape::StyledPanel);
        paginationFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout_2 = new QHBoxLayout(paginationFrame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_pag_left = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_pag_left);

        btn_prev = new QPushButton(paginationFrame);
        btn_prev->setObjectName(QString::fromUtf8("btn_prev"));
        btn_prev->setMinimumSize(QSize(31, 28));
        btn_prev->setMaximumSize(QSize(31, 28));

        horizontalLayout_2->addWidget(btn_prev);

        label_pageInfo_2 = new QLabel(paginationFrame);
        label_pageInfo_2->setObjectName(QString::fromUtf8("label_pageInfo_2"));

        horizontalLayout_2->addWidget(label_pageInfo_2);

        lineEdit_pageNum = new QLineEdit(paginationFrame);
        lineEdit_pageNum->setObjectName(QString::fromUtf8("lineEdit_pageNum"));
        lineEdit_pageNum->setMinimumSize(QSize(30, 25));
        lineEdit_pageNum->setMaximumSize(QSize(40, 25));

        horizontalLayout_2->addWidget(lineEdit_pageNum);

        label_pageInfo = new QLabel(paginationFrame);
        label_pageInfo->setObjectName(QString::fromUtf8("label_pageInfo"));

        horizontalLayout_2->addWidget(label_pageInfo);

        btn_next = new QPushButton(paginationFrame);
        btn_next->setObjectName(QString::fromUtf8("btn_next"));
        btn_next->setMinimumSize(QSize(31, 28));
        btn_next->setMaximumSize(QSize(31, 28));

        horizontalLayout_2->addWidget(btn_next);

        horizontalSpacer_pag_right = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_pag_right);


        verticalLayout_content->addWidget(paginationFrame);

        stackedWidget->addWidget(page_tickets);

        horizontalLayout_body->addWidget(stackedWidget);


        verticalLayout_main->addLayout(horizontalLayout_body);


        retranslateUi(Deal);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Deal);
    } // setupUi

    void retranslateUi(QWidget *Deal)
    {
        Deal->setWindowTitle(QCoreApplication::translate("Deal", "\350\256\242\347\245\250\347\263\273\347\273\237", nullptr));
        Title->setText(QCoreApplication::translate("Deal", "\350\210\252\347\217\255\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        Avatar->setText(QString());
        home->setText(QCoreApplication::translate("Deal", "\351\246\226\351\241\265", nullptr));
        Deal_2->setText(QCoreApplication::translate("Deal", "\350\241\214\347\250\213", nullptr));
        favorite_button->setText(QCoreApplication::translate("Deal", "\346\224\266\350\227\217", nullptr));
        Single_Center->setText(QCoreApplication::translate("Deal", "\344\270\252\344\272\272\344\270\255\345\277\203", nullptr));
        searchGroup->setTitle(QCoreApplication::translate("Deal", "\346\220\234\347\264\242\347\245\250\345\212\241", nullptr));
        label_from->setText(QCoreApplication::translate("Deal", "\345\207\272\345\217\221\345\234\260\357\274\232", nullptr));
        lineEdit_from->setPlaceholderText(QCoreApplication::translate("Deal", "\344\276\213\345\246\202\357\274\232\345\214\227\344\272\254", nullptr));
        label_to->setText(QCoreApplication::translate("Deal", "\347\233\256\347\232\204\345\234\260\357\274\232", nullptr));
        lineEdit_to->setPlaceholderText(QCoreApplication::translate("Deal", "\344\276\213\345\246\202\357\274\232\344\270\212\346\265\267", nullptr));
        label_date->setText(QCoreApplication::translate("Deal", "\346\227\245\346\234\237\357\274\232", nullptr));
        btn_search->setText(QCoreApplication::translate("Deal", "\346\220\234\347\264\242", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_tickets->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Deal", "\347\274\226\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_tickets->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Deal", "\345\207\272\345\217\221\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_tickets->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Deal", "\347\233\256\347\232\204\345\234\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_tickets->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Deal", "\345\207\272\345\217\221\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_tickets->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("Deal", "\345\210\260\350\276\276\346\227\266\351\227\264", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_tickets->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("Deal", "\344\273\267\346\240\274\357\274\210\345\205\203\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_tickets->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("Deal", "\345\217\257\347\224\250\345\272\247\344\275\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_tickets->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("Deal", "\345\205\254\345\217\270", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_tickets->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("Deal", "\346\223\215\344\275\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_tickets->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("Deal", "\346\224\266\350\227\217", nullptr));
        btn_prev->setText(QString());
        label_pageInfo_2->setText(QCoreApplication::translate("Deal", "<html><head/><body><p><span style=\" font-size:12pt;\">\347\254\254</span></p></body></html>", nullptr));
        label_pageInfo->setText(QCoreApplication::translate("Deal", "<html><head/><body><p><span style=\" font-size:12pt;\">\351\241\265/ \345\205\261 0 \351\241\265</span></p></body></html>", nullptr));
        btn_next->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Deal: public Ui_Deal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEAL_H
