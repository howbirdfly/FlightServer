#ifndef PASSENGER_H
#define PASSENGER_H

#include <QWidget>
#include <QJsonObject>

namespace Ui {
class passenger;
}

class passenger : public QWidget
{
    Q_OBJECT

public:
    explicit passenger(QWidget *parent = nullptr);
    explicit passenger(const QString &userID, QWidget *parent = nullptr);
    ~passenger();

    void setUserId(const QString &userID);

signals:
    void backRequested();
    void passengerSelected(const QString &name, const QString &idCard, const QString &phone);

private slots:
    void on_btn_add_clicked();
    void on_btn_refresh_clicked();
    void on_btn_close_clicked();
    void onDeletePassenger();
    void onPassengerDoubleClicked(int row, int column);
    void onGetPassengersResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onAddPassengerResponse(int msgType, bool success, const QString &message, const QJsonObject &data);
    void onDeletePassengerResponse(int msgType, bool success, const QString &message, const QJsonObject &data);

private:
    Ui::passenger *ui;
    QString currentUserID;

    void initTable();
    void loadPassengers();
    int getUserId();
    bool validateInput();
    void clearInput();
};

#endif // PASSENGER_H
