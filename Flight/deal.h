#ifndef DEAL_H
#define DEAL_H
#include "userprofile.h"
#include <QWidget>
#include <QString>
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
    void onSearchResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onAddFavoriteResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
private:
    void initTable();
    void searchTickets();
    QString currentUserID;

    Ui::Deal *ui;
    Single_Center *m_personalCenterPage;
    UserProfile *m_userProfilePage;
    favorite_dialog *m_favoriteDialogPage;
};

#endif // DEAL_H
