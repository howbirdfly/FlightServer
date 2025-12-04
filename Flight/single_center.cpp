#include "single_center.h"
#include "ui_single_center.h"
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QHeaderView>
#include <QDateTime>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <QJsonValue>
#include "networkmanager.h"
#include "protocol.h"

Single_Center::Single_Center(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Single_Center)
{
    ui->setupUi(this);
    currentUsername = "";
    initTable();
}

Single_Center::Single_Center(const QString &username, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Single_Center)
{
    ui->setupUi(this);
    currentUsername = username;
    initTable();
    loadOrders();
    connect(ui->btn_refresh, &QPushButton::clicked, this, &Single_Center::refreshOrderList);
    connect(ui->btn_back, &QPushButton::clicked, this, &Single_Center::on_btn_back_clicked);
}

Single_Center::~Single_Center()
{
    delete ui;
}
void Single_Center::on_btn_back_clicked()
{
    emit backRequested(); // 发出"返回请求"信号
}
void Single_Center::initTable()
{
    ui->tableWidget_orders->setColumnCount(9);
    QStringList headers;
    headers << "订单号" << "票务类型" << "路线" << "出发时间" << "到达时间"
            << "数量" << "总价(元)" << "状态" << "操作"<<"收藏";
    ui->tableWidget_orders->setHorizontalHeaderLabels(headers);
    ui->tableWidget_orders->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_orders->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_orders->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_orders->verticalHeader()->setVisible(false);
}

int Single_Center::getUserId()
{
    if (currentUsername.isEmpty()) {
        return -1;
    }
    bool ok;
    int userId = currentUsername.toInt(&ok);
    if (ok && userId > 0) {
        return userId;
    }
    return -1;
}

void Single_Center::loadOrders()
{
    int userId = getUserId();
    if (userId == -1) {
        QMessageBox::warning(this, "错误", "获取用户信息失败！");
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &Single_Center::onGetOrdersResponse, Qt::UniqueConnection);
    
    QJsonObject data;
    data["userID"] = userId;
    
    client->sendRequest(MSG_GET_ORDERS, data);
}

void Single_Center::onGetOrdersResponse(int msgType, bool success,
                                      const QString &message, const QJsonObject &data)
{
    if (msgType != MSG_GET_ORDERS_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &Single_Center::onGetOrdersResponse);
    
    if (!success) {
        QMessageBox::warning(this, "错误", message);
        return;
    }
    
    // 解析订单列表
    QJsonArray orders = data["orders"].toArray();
    ui->tableWidget_orders->setRowCount(0);
    
    for (const QJsonValue &value : orders) {
        QJsonObject order = value.toObject();
        
        int row = ui->tableWidget_orders->rowCount();
        ui->tableWidget_orders->insertRow(row);
        
        int orderId = order["orderID"].toInt();
        QString orderNo = order["orderNo"].toString();
        QString status = order["orderStatus"].toString();
        int count = order["ticketCount"].toInt();
        double totalPrice = order["totalPrice"].toDouble();
        QString ticketType = order["ticketType"].toString();
        QString route = order["departureCity"].toString() + " → " + order["arrivalCity"].toString();
        QString depTimeStr = order["departureTime"].toString();
        QString arrTimeStr = order["arrivalTime"].toString();
        QDateTime depTime = QDateTime::fromString(depTimeStr, "yyyy-MM-dd hh:mm:ss");
        QDateTime arrTime = QDateTime::fromString(arrTimeStr, "yyyy-MM-dd hh:mm:ss");
        
        QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");
        QString statusName = status == "Paid" ? "已支付" : (status == "Cancelled" ? "已取消" : "待支付");
        
        // 判断订单是否过期
        if (status == "Paid") {
            if (arrTime < QDateTime::currentDateTime()) {
                statusName = "已过期";
            } else {
                statusName = "已支付";
            }
        } else if (status == "Cancelled") {
            statusName = "已取消";
        } else {
            if (depTime < QDateTime::currentDateTime()) {
                statusName = "已过期";
            } else {
                statusName = "待支付";
            }
        }
        
        ui->tableWidget_orders->setItem(row, 0, new QTableWidgetItem(orderNo));
        ui->tableWidget_orders->setItem(row, 1, new QTableWidgetItem(typeName));
        ui->tableWidget_orders->setItem(row, 2, new QTableWidgetItem(route));
        ui->tableWidget_orders->setItem(row, 3, new QTableWidgetItem(depTimeStr));
        ui->tableWidget_orders->setItem(row, 4, new QTableWidgetItem(arrTimeStr));
        ui->tableWidget_orders->setItem(row, 5, new QTableWidgetItem(QString::number(count)));
        ui->tableWidget_orders->setItem(row, 6, new QTableWidgetItem(QString::number(totalPrice, 'f', 2)));
        ui->tableWidget_orders->setItem(row, 7, new QTableWidgetItem(statusName));
        
        // 保存orderID到第一列的userData中
        ui->tableWidget_orders->item(row, 0)->setData(Qt::UserRole, orderId);
        
        // 添加取消订单按钮（只有已支付的订单可以取消）
        if (status == "Paid" && arrTime > QDateTime::currentDateTime()) {
            QPushButton *btnCancel = new QPushButton("取消订单");
            btnCancel->setProperty("orderId", orderId);
            connect(btnCancel, &QPushButton::clicked, this, &Single_Center::onCancelOrder);
            ui->tableWidget_orders->setCellWidget(row, 8, btnCancel);
        } else if (status == "Paid" && arrTime < QDateTime::currentDateTime()) {
            QPushButton *btndelete = new QPushButton("删除订单");
            btndelete->setProperty("orderId", orderId);
            connect(btndelete, &QPushButton::clicked, this, &Single_Center::onDeleteOrder);
            ui->tableWidget_orders->setCellWidget(row, 8, btndelete);
        } else {
            ui->tableWidget_orders->setItem(row, 8, new QTableWidgetItem("-"));
        }
    }
}

void Single_Center::refreshOrderList()
{
    loadOrders();
}

void Single_Center::onCancelOrder()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int orderId = btn->property("orderId").toInt();

    int ret = QMessageBox::question(this, "确认", "确定要取消这个订单吗？",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &Single_Center::onCancelOrderResponse, Qt::UniqueConnection);
    
    QJsonObject data;
    data["orderID"] = orderId;
    
    client->sendRequest(MSG_CANCEL_ORDER, data);
}

void Single_Center::onCancelOrderResponse(int msgType, bool success,
                                         const QString &message, const QJsonObject &data)
{
    Q_UNUSED(data);
    
    if (msgType != MSG_CANCEL_ORDER_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &Single_Center::onCancelOrderResponse);
    
    if (success) {
        QMessageBox::information(this, "成功", "订单已取消");
        loadOrders();  // 重新加载订单列表
    } else {
        QMessageBox::warning(this, "失败", message);
    }
}

//删除按钮
void Single_Center::onDeleteOrder()
{
    // 删除订单功能可以通过取消订单接口实现，或者需要服务端支持删除订单接口
    // 这里暂时使用取消订单的逻辑
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int orderId = btn->property("orderId").toInt();

    int ret = QMessageBox::question(this, "确认", "确定要删除这个订单吗？",
                                    QMessageBox::Yes | QMessageBox::No);
    if (ret != QMessageBox::Yes) {
        return;
    }

    // 使用取消订单接口（服务端可以处理已过期订单的删除）
    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &Single_Center::onCancelOrderResponse, Qt::UniqueConnection);
    
    QJsonObject data;
    data["orderID"] = orderId;
    
    client->sendRequest(MSG_CANCEL_ORDER, data);
}

void Single_Center::onViewOrder()
{

}
