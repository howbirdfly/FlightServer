#ifndef DEAL_H
#define DEAL_H
#include "userprofile.h"
#include <QWidget>
#include <QString>
#include <QPointer>
#include <QPushButton>
#include <QJsonObject>
#include "single_center.h"
#include"favorite_dialog.h"
namespace Ui {
class Deal;
}

class Deal : public QWidget
{
    Q_OBJECT

public:
    explicit Deal(QWidget *parent = nullptr);
    explicit Deal(const QString &username, QWidget *parent = nullptr);
    ~Deal();

private slots:
    void on_Single_Center_clicked();
    void on_btn_search_clicked();
    void on_favorite_button_clicked();
   // void on_btn_reset_clicked();
    void on_Deal_2_clicked();
    void onBookTicket();
    void onAddFavorite();
    void refreshTicketList();
    void showTicketSearchPage();
    void on_Avatar_clicked();
    void onSearchResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onAddFavoriteResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    // 获取头像信息的响应槽
    void onGetUserInfoForAvatar(int msgType, bool success, const QString &message, const QJsonObject &data);
    void on_lineEdit_pageNum_returnPressed();
    void updatePageContainerText();
    void on_home_clicked();

private:
    void initTable();
    void setCircularAvatar(const QByteArray &avatarData);  // 圆形头像绘制
    void getData(const QString &userID);                   // 获取头像数据
    void searchTickets();
    int getTotalPage();      // 预留：如需本地计算分页（现在由服务端完成）
    void initPagination();   // 初始化分页控件和信号
    QString currentUserID;
    int currentPage = 1;
    int totalPage = 0;

    Ui::Deal *ui;
    Single_Center *m_personalCenterPage;
    UserProfile *m_userProfilePage;
    favorite_dialog *m_favoriteDialogPage;
    QPointer<QPushButton> pendingFavoriteButton;
};

#endif // DEAL_H
