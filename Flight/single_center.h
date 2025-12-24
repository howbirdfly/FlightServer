#ifndef SINGLE_CENTER_H
#define SINGLE_CENTER_H

#include <QWidget>
#include <QString>
#include <QJsonObject>
#include <QPointer>
#include <QPushButton>

namespace Ui {
class Single_Center;
}

class Single_Center : public QWidget
{
    Q_OBJECT

public:
    explicit Single_Center(QWidget *parent = nullptr);
    explicit Single_Center(const QString &username, QWidget *parent = nullptr);
    ~Single_Center();
    void refreshOrderList();
signals:
    void backRequested();
private slots:

    void onCancelOrder();
    void onDeleteOrder();
    void onViewOrder();
    void on_btn_back_clicked();
    void onGetOrdersResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onCancelOrderResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onAddFavorite();
    void onAddFavoriteResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
private:
    void initTable();
    void loadOrders();
    QString currentUsername;
    int getUserId();

    Ui::Single_Center *ui;
    QPointer<QPushButton> pendingFavoriteButton;
};

#endif // SINGLE_CENTER_H
