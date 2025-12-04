#ifndef FAVORITE_DIALOG_H
#define FAVORITE_DIALOG_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class favorite_dialog;
}

class favorite_dialog : public QWidget
{
    Q_OBJECT

public:
    explicit favorite_dialog(QWidget *parent = nullptr);

    // 修改：接收 userID 而不是 username
    explicit favorite_dialog(const QString &userID, QWidget *parent = nullptr);

    ~favorite_dialog();
    void refreshFavoriteList();

signals:
    void backRequested();

private slots:
    void on_btn_back_clicked();
    void on_btn_refresh_clicked();
    void on_searchBtn_clicked();
    void onRemoveFavorite();
    void onGetFavoritesResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onDeleteFavoriteResponse(int msgType, bool success, const QString &message, const QJsonObject &data);

private:
    Ui::favorite_dialog *ui;

    QString currentUserID; // 修改：存储 UserID

    QString currentUsername;

    void initTable();
    void loadFavorites();
};

#endif // FAVORITE_DIALOG_H
