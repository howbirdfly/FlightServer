#include "order_dialog.h"
#include "ui_order_dialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QRandomGenerator>
#include <QJsonArray>
#include <QComboBox>
#include <QDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include "networkmanager.h"
#include "protocol.h"
#include<QFile>
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
    , userBalance(0.0)
{
    ui->setupUi(this);
    setWindowTitle("填写订单信息");
    setModal(true);

    QComboBox *combo = findChild<QComboBox*>("comboBox_class");
    if (combo) {
        combo->clear();
        combo->addItem("经济舱");
        combo->addItem("商务舱");
        connect(combo, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &OrderDialog::calculateTotal);
    }

    loadTicketInfo();
    requestUserBalance();
    ui->spinBox_count->setMinimum(1);
    ui->spinBox_count->setMaximum(10);
    ui->spinBox_count->setValue(1);

    connect(ui->spinBox_count, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &OrderDialog::on_spinBox_count_valueChanged);
    // 加载样式
    QFile qssFile(":/styles/order_dialog.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();
        qDebug() << "成功加载 style.qss";
    }
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

void OrderDialog::on_btn_passenger_clicked()
{
    if (userId <= 0) {
        QMessageBox::warning(this, "提示", "用户信息无效，无法获取乘客列表！");
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    if (!client->isConnected()) {
        QMessageBox::warning(this, "错误", "未连接到服务器！");
        return;
    }

    connect(client, &NetworkClient::responseReceived,
            this, &OrderDialog::onGetPassengersResponse, Qt::UniqueConnection);

    QJsonObject data;
    data["userID"] = QString::number(userId);
    client->sendRequest(MSG_GET_PASSENGERS, data);
}

void OrderDialog::onGetPassengersResponse(int msgType, bool success,
                                          const QString &message, const QJsonObject &data)
{
    if (msgType != MSG_GET_PASSENGERS_RESPONSE) {
        return;
    }

    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &OrderDialog::onGetPassengersResponse);

    if (!success) {
        QMessageBox::warning(this, "错误", message);
        return;
    }

    QJsonArray passengers = data["passengers"].toArray();
    if (passengers.isEmpty()) {
        QMessageBox::information(this, "提示", "您还没有添加常用乘机人，请先去个人中心添加。");
        return;
    }

    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("选择乘机人");
    dlg->resize(350, 450);

    QVBoxLayout *layout = new QVBoxLayout(dlg);
    QListWidget *listWidget = new QListWidget(dlg);
    listWidget->setStyleSheet(
        "QListWidget { border: 1px solid #ccc; outline: none; }"
        "QListWidget::item { padding: 10px; border-bottom: 1px solid #eee; }"
        "QListWidget::item:hover { background-color: #f5f5f5; }"
        "QListWidget::item:selected { background-color: #e6f7ff; color: #333; }"
        "QListWidget::indicator { width: 20px; height: 20px; }"
    );
    layout->addWidget(listWidget);

    for (const QJsonValue &value : passengers) {
        QJsonObject passenger = value.toObject();
        QString name = passenger["name"].toString();
        QString idCard = passenger["idCard"].toString();
        QString phone = passenger["phone"].toString();

        QListWidgetItem *item = new QListWidgetItem(name);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        item->setData(Qt::UserRole, idCard);
        item->setData(Qt::UserRole + 1, phone);
        listWidget->addItem(item);
    }

    connect(listWidget, &QListWidget::itemClicked, dlg, [listWidget](QListWidgetItem *item){
        listWidget->blockSignals(true);
        for (int i = 0; i < listWidget->count(); ++i) {
            QListWidgetItem *it = listWidget->item(i);
            it->setCheckState(Qt::Unchecked);
            it->setSelected(false);
        }
        item->setCheckState(Qt::Checked);
        item->setSelected(true);
        listWidget->blockSignals(false);
    });

    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnOk = new QPushButton("确定", dlg);
    QPushButton *btnCancel = new QPushButton("取消", dlg);
    btnOk->setStyleSheet("background-color: #4CAF50; color: white; border-radius: 4px; padding: 6px 15px;");
    btnCancel->setStyleSheet("background-color: #f44336; color: white; border-radius: 4px; padding: 6px 15px;");
    btnLayout->addStretch();
    btnLayout->addWidget(btnOk);
    btnLayout->addWidget(btnCancel);
    layout->addLayout(btnLayout);

    connect(btnOk, &QPushButton::clicked, dlg, &QDialog::accept);
    connect(btnCancel, &QPushButton::clicked, dlg, &QDialog::reject);
    connect(listWidget, &QListWidget::itemDoubleClicked, dlg, [dlg](QListWidgetItem *item){
        item->setCheckState(Qt::Checked);
        dlg->accept();
    });

    if (dlg->exec() == QDialog::Accepted) {
        QListWidgetItem *selectedItem = nullptr;
        for (int i = 0; i < listWidget->count(); ++i) {
            if (listWidget->item(i)->checkState() == Qt::Checked) {
                selectedItem = listWidget->item(i);
                break;
            }
        }

        if (selectedItem) {
            ui->lineEdit_name->setText(selectedItem->text());
            ui->lineEdit_id->setText(selectedItem->data(Qt::UserRole).toString());
            ui->lineEdit_phone->setText(selectedItem->data(Qt::UserRole + 1).toString());
        } else {
            QMessageBox::warning(this, "提示", "未选择任何乘机人！");
        }
    }

    delete dlg;
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
    double currentPrice = ticketPrice;
    QComboBox *combo = findChild<QComboBox*>("comboBox_class");
    if (combo && combo->currentText() == "商务舱") {
        currentPrice += 200.0;
    }
    double total = currentPrice * count;
    ui->label_total->setText(QString::number(total, 'f', 2) + " 元");
    QLabel *balanceLabel = findChild<QLabel*>("label_balance");
    if (balanceLabel) {
        if (userBalance > 0 && userBalance < total) {
            balanceLabel->setStyleSheet("color: red; font-weight: bold;");
        } else {
            balanceLabel->setStyleSheet("color: green; font-weight: bold;");
        }
    }
}

void OrderDialog::requestUserBalance()
{
    if (userId <= 0) {
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    if (!client->isConnected()) {
        return;
    }

    connect(client, &NetworkClient::responseReceived,
            this, &OrderDialog::onGetBalanceResponse, Qt::UniqueConnection);

    QJsonObject data;
    data["userID"] = QString::number(userId);
    client->sendRequest(MSG_GET_BALANCE, data);
}

void OrderDialog::onGetBalanceResponse(int msgType, bool success,
                                       const QString &message, const QJsonObject &data)
{
    Q_UNUSED(message);

    if (msgType != MSG_GET_BALANCE_RESPONSE) {
        return;
    }

    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &OrderDialog::onGetBalanceResponse);

    if (success) {
        userBalance = data["balance"].toDouble();
        QLabel *balanceLabel = findChild<QLabel*>("label_balance");
        if (balanceLabel) {
            balanceLabel->setText(QString("当前余额: ¥ %1").arg(QString::number(userBalance, 'f', 2)));
        }
        calculateTotal();
    }
}
void OrderDialog::on_btn_confirm_clicked()
{
    QString passengerName = ui->lineEdit_name->text().trimmed();
    QString passengerID = ui->lineEdit_id->text().trimmed();
    QString contactPhone = ui->lineEdit_phone->text().trimmed();
    int count = ui->spinBox_count->value();
    double currentPrice = ticketPrice;
    QComboBox *combo = findChild<QComboBox*>("comboBox_class");
    if (combo && combo->currentText() == "商务舱") {
        currentPrice += 200.0;
    }
    double totalCost = currentPrice * count;

    if (userBalance > 0 && totalCost > userBalance) {
        QMessageBox::critical(this, "支付失败",
                              QString("您的余额不足！\n当前余额: ¥%1\n订单金额: ¥%2\n请先充值。")
                                  .arg(QString::number(userBalance, 'f', 2))
                                  .arg(QString::number(totalCost, 'f', 2)));
        return;
    }

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
    data["userID"] = QString::number(userId);
    data["ticketID"] = QString::number(ticketId);
    data["passengerName"] = passengerName;
    data["passengerIDCard"] = passengerID;
    data["contactPhone"] = contactPhone;
    data["quantity"] = count;  // 服务端兼容 ticketCount，但优先使用 quantity
    if (combo) {
        data["cabinClass"] = combo->currentText();
    }
    
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
