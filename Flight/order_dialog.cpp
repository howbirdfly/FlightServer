#include "order_dialog.h"
#include "ui_order_dialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>
#include <QJsonArray>
#include "networkmanager.h"
#include "protocol.h"

OrderDialog::~OrderDialog()
{
    delete ui;
}

OrderDialog::OrderDialog(int ticketId, int userId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OrderDialog)
    , ticketId(ticketId)
    , userId(userId)
    , ticketPrice(0.0)
{
    ui->setupUi(this);
    setWindowTitle("填写订单信息");
    setModal(true);

    loadTicketInfo();
    ui->spinBox_count->setMinimum(1);
    ui->spinBox_count->setMaximum(10);
    ui->spinBox_count->setValue(1);

    connect(ui->spinBox_count, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &OrderDialog::on_spinBox_count_valueChanged);
}

void OrderDialog::loadTicketInfo()
{
    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &OrderDialog::onLoadTicketResponse, Qt::UniqueConnection);
    
    // 使用查询票务的接口，但只查询单个票务
    QJsonObject data;
    data["ticketID"] = ticketId;
    
    client->sendRequest(MSG_SEARCH_TICKETS, data);
}

void OrderDialog::onLoadTicketResponse(int msgType, bool success,
                                      const QString &message, const QJsonObject &data)
{
    if (msgType != MSG_SEARCH_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &OrderDialog::onLoadTicketResponse);
    
    if (!success) {
        QMessageBox::critical(this, "错误", "获取票务信息失败：" + message);
        reject();
        return;
    }
    
    // 解析票务信息（应该只有一个）
    QJsonArray tickets = data["tickets"].toArray();
    if (tickets.isEmpty()) {
        QMessageBox::critical(this, "错误", "未找到票务信息！");
        reject();
        return;
    }
    
    QJsonObject ticket = tickets[0].toObject();
    
    QString ticketType = ticket["ticketType"].toString();
    QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");
    
    ui->label_type->setText(typeName);
    ui->label_ticketNo->setText(ticket["ticketNo"].toString());
    ui->label_route->setText(ticket["departureCity"].toString() + " → " + ticket["arrivalCity"].toString());
    
    QString depTimeStr = ticket["departureTime"].toString();
    QString arrTimeStr = ticket["arrivalTime"].toString();
    ui->label_departure->setText(depTimeStr);
    ui->label_arrival->setText(arrTimeStr);
    
    ticketPrice = ticket["price"].toDouble();
    ui->label_price->setText(QString::number(ticketPrice, 'f', 2) + " 元");
    
    int availableSeats = ticket["availableSeats"].toInt();
    ui->label_available->setText(QString::number(availableSeats) + " 张");
    ui->label_company->setText(ticket["company"].toString());
    
    ui->spinBox_count->setMaximum(availableSeats);
    calculateTotal();
}
void OrderDialog::on_spinBox_count_valueChanged(int count)
{
    Q_UNUSED(count);
    calculateTotal();
}

void OrderDialog::calculateTotal()
{
    int count = ui->spinBox_count->value();
    double total = ticketPrice * count;
    ui->label_total->setText(QString::number(total, 'f', 2) + " 元");
}
void OrderDialog::on_btn_confirm_clicked()
{
    QString passengerName = ui->lineEdit_name->text().trimmed();
    QString passengerID = ui->lineEdit_id->text().trimmed();
    QString contactPhone = ui->lineEdit_phone->text().trimmed();
    int count = ui->spinBox_count->value();

    // 输入验证
    if (passengerName.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入乘客姓名！");
        return;
    }
    if (contactPhone.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入联系电话！");
        return;
    }
    if (passengerID.length() != 18) {
        QMessageBox::warning(this, "提示", "请输入18位身份证号码！");
        ui->lineEdit_id->setFocus();
        ui->lineEdit_id->selectAll();
        return;
    }
    
    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &OrderDialog::onCreateOrderResponse, Qt::UniqueConnection);
    
    // 构造请求数据
    QJsonObject data;
    data["userID"] = userId;
    data["ticketID"] = ticketId;
    data["passengerName"] = passengerName;
    data["passengerIDCard"] = passengerID;
    data["contactPhone"] = contactPhone;
    data["ticketCount"] = count;
    data["totalPrice"] = ticketPrice * count;
    
    // 发送创建订单请求
    client->sendRequest(MSG_CREATE_ORDER, data);
}

void OrderDialog::onCreateOrderResponse(int msgType, bool success,
                                       const QString &message, const QJsonObject &data)
{
    if (msgType != MSG_CREATE_ORDER_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &OrderDialog::onCreateOrderResponse);
    
    if (success) {
        QString orderNo = data["orderNo"].toString();
        double totalPrice = data["totalPrice"].toDouble();
        QMessageBox::information(this, "成功", 
            QString("订单创建成功！\n订单号：%1\n总价：%2元").arg(orderNo).arg(totalPrice));
        accept();
    } else {
        QMessageBox::warning(this, "失败", message);
    }
}
void OrderDialog::on_btn_cancel_clicked()
{
    reject();
}
