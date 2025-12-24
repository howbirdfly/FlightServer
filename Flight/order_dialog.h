#ifndef ORDER_DIALOG_H
#define ORDER_DIALOG_H

#include <QDialog>
#include <QJsonObject>
#include "ui_order_dialog.h"

class OrderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OrderDialog(int ticketId, int userId, QWidget *parent = nullptr);
    ~OrderDialog();

private slots:
    void on_btn_confirm_clicked();
    void on_btn_cancel_clicked();
    void on_spinBox_count_valueChanged(int count);
    void on_btn_passenger_clicked();
    void onLoadTicketResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onCreateOrderResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onGetPassengersResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onGetBalanceResponse(int msgType, bool success, const QString &message, const QJsonObject &data);

private:
    void loadTicketInfo();
    void requestUserBalance();
    void calculateTotal();

    Ui::OrderDialog *ui;
    int ticketId;
    int userId;
    double ticketPrice;
    double userBalance;
};

#endif // ORDER_DIALOG_H
