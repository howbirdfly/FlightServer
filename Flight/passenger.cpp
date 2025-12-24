#include "passenger.h"
#include "ui_passenger.h"
#include "networkmanager.h"
#include "protocol.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QTableWidgetItem>
#include<QFile>
passenger::passenger(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::passenger)
{
    ui->setupUi(this);
    initTable();
    // 加载样式
    QFile qssFile(":/styles/passenger.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();
        qDebug() << "成功加载 style.qss";
    }
}

passenger::passenger(const QString &userID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::passenger),
    currentUserID(userID)
{
    ui->setupUi(this);
    initTable();
    loadPassengers();
    // 加载样式
    QFile qssFile(":/styles/passenger.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();

    }
}
void passenger::setUserId(const QString &userID)
{
    currentUserID = userID;
    loadPassengers(); // 设置用户名后立即加载乘客数据
}
void passenger::initTable()
{
    // 设置表格属性
    ui->table_passengers->setColumnCount(4);
    QStringList headers;
    headers << "姓名" << "身份证" << "手机号" << "操作";
    ui->table_passengers->setHorizontalHeaderLabels(headers);

    // 设置表格行为
    ui->table_passengers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table_passengers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->table_passengers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table_passengers->setAlternatingRowColors(true);

    // 设置列宽
    ui->table_passengers->setColumnWidth(0, 100);  // 姓名
    ui->table_passengers->setColumnWidth(1, 200);  // 身份证
    ui->table_passengers->setColumnWidth(2, 120);  // 手机号
    ui->table_passengers->horizontalHeader()->setStretchLastSection(true); // 操作列自动拉伸

    // 连接信号槽
    connect(ui->btn_add, &QPushButton::clicked, this, &passenger::on_btn_add_clicked);
    connect(ui->btn_refresh, &QPushButton::clicked, this, &passenger::on_btn_refresh_clicked);
    connect(ui->btn_close, &QPushButton::clicked, this, &passenger::on_btn_close_clicked);
    connect(ui->table_passengers, &QTableWidget::cellDoubleClicked,
            this, &passenger::onPassengerDoubleClicked);
}
int passenger::getUserId()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "错误", "用户未登录！");
        return -1;
    }

    bool ok = false;
    int userId = currentUserID.toInt(&ok);
    if (!ok || userId <= 0) {
        QMessageBox::warning(this, "错误", "用户信息无效！");
        return -1;
    }
    return userId;
}
void passenger::loadPassengers()
{
    int userId = getUserId();
    if (userId == -1) {
        return;
    }

    // 清空表格
    ui->table_passengers->setRowCount(0);

    NetworkClient *client = NetworkManager::instance()->client();
    connect(client, &NetworkClient::responseReceived,
            this, &passenger::onGetPassengersResponse, Qt::UniqueConnection);

    QJsonObject data;
    data["userID"] = QString::number(userId);

    client->sendRequest(MSG_GET_PASSENGERS, data);
}
bool passenger::validateInput()
{
    QString name = ui->edit_name->text().trimmed();
    QString idCard = ui->edit_idcard->text().trimmed();
    QString phone = ui->edit_phone->text().trimmed();

    // 检查是否为空
    if (name.isEmpty() || idCard.isEmpty() || phone.isEmpty()) {
        return false;
    }

    // 验证姓名长度
    if (name.length() > 50) {
        QMessageBox::warning(this, "输入错误", "姓名长度不能超过50个字符！");
        return false;
    }

    // 验证身份证格式
    if (idCard.length() != 18) {
        QMessageBox::warning(this, "输入错误", "身份证号码必须是18位！");
        return false;
    }

    // 验证手机号格式
    if (phone.length() != 11) {
        QMessageBox::warning(this, "输入错误", "手机号必须是11位！");
        return false;
    }

    // 简单验证手机号是否为数字
    bool ok;
    phone.toLongLong(&ok);
    if (!ok) {
        QMessageBox::warning(this, "输入错误", "手机号必须为数字！");
        return false;
    }

    return true;
}
void passenger::clearInput()
{
    ui->edit_name->clear();
    ui->edit_idcard->clear();
    ui->edit_phone->clear();
    ui->edit_name->setFocus(); // 将焦点设置回姓名输入框
}

void passenger::on_btn_add_clicked()
{
    if (!validateInput()) {
        return;
    }

    int userId = getUserId();
    if (userId == -1) {
        return;
    }

    QString name = ui->edit_name->text().trimmed();
    QString idCard = ui->edit_idcard->text().trimmed();
    QString phone = ui->edit_phone->text().trimmed();

    NetworkClient *client = NetworkManager::instance()->client();
    connect(client, &NetworkClient::responseReceived,
            this, &passenger::onAddPassengerResponse, Qt::UniqueConnection);

    QJsonObject data;
    data["userID"] = QString::number(userId);
    data["name"] = name;
    data["idCard"] = idCard;
    data["phone"] = phone;

    client->sendRequest(MSG_ADD_PASSENGER, data);
}

void passenger::on_btn_refresh_clicked()
{
    loadPassengers();
}

void passenger::on_btn_close_clicked()
{
    emit backRequested();
    this->close();
}

void passenger::onDeletePassenger()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int passengerId = btn->property("passengerId").toInt();
    QString passengerName = btn->property("passengerName").toString();

    // 确认删除
    int ret = QMessageBox::question(this, "确认删除",
                                    QString("确定要删除乘客\"%1\"吗？").arg(passengerName),
                                    QMessageBox::Yes | QMessageBox::No);

    if (ret != QMessageBox::Yes) {
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    connect(client, &NetworkClient::responseReceived,
            this, &passenger::onDeletePassengerResponse, Qt::UniqueConnection);

    QJsonObject data;
    data["passengerID"] = passengerId;

    client->sendRequest(MSG_DELETE_PASSENGER, data);
}

void passenger::onPassengerDoubleClicked(int row, int column)
{
    Q_UNUSED(column);

    if (!ui->table_passengers) {
        return;
    }

    QTableWidgetItem *nameItem = ui->table_passengers->item(row, 0);
    QTableWidgetItem *idItem = ui->table_passengers->item(row, 1);
    QTableWidgetItem *phoneItem = ui->table_passengers->item(row, 2);
    if (!nameItem || !idItem || !phoneItem) {
        return;
    }

    QString name = nameItem->text().trimmed();
    QString idCard = idItem->text().trimmed();
    QString phone = phoneItem->text().trimmed();
    if (idCard.isEmpty()) {
        return;
    }

    emit passengerSelected(name, idCard, phone);
    close();
}

void passenger::onGetPassengersResponse(int msgType, bool success, const QString &message, const QJsonObject &data)
{
    if (msgType != MSG_GET_PASSENGERS_RESPONSE) {
        return;
    }

    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &passenger::onGetPassengersResponse);

    if (!success) {
        QMessageBox::warning(this, "错误", message);
        return;
    }

    QJsonArray passengers = data["passengers"].toArray();
    ui->table_passengers->setRowCount(0);

    int row = 0;
    for (const QJsonValue &value : passengers) {
        QJsonObject passengerObj = value.toObject();
        ui->table_passengers->insertRow(row);

        int passengerId = passengerObj["passengerID"].toInt();
        QString name = passengerObj["name"].toString();
        QString idCard = passengerObj["idCard"].toString();
        QString phone = passengerObj["phone"].toString();

        ui->table_passengers->setItem(row, 0, new QTableWidgetItem(name));
        ui->table_passengers->setItem(row, 1, new QTableWidgetItem(idCard));
        ui->table_passengers->setItem(row, 2, new QTableWidgetItem(phone));

        QPushButton *btnDelete = new QPushButton("删除");
        btnDelete->setProperty("passengerId", passengerId);
        btnDelete->setProperty("passengerName", name);
        connect(btnDelete, &QPushButton::clicked, this, &passenger::onDeletePassenger);

        QWidget *widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(widget);
        layout->addWidget(btnDelete);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(2, 2, 2, 2);
        widget->setLayout(layout);
        ui->table_passengers->setCellWidget(row, 3, widget);

        row++;
    }

    if (row == 0) {
        ui->table_passengers->setRowCount(1);
        ui->table_passengers->setItem(0, 0, new QTableWidgetItem("暂无乘客信息"));
        for (int i = 1; i < 4; ++i) {
            ui->table_passengers->setItem(0, i, new QTableWidgetItem(""));
        }
        ui->table_passengers->setSpan(0, 0, 1, 4);
    }
}

void passenger::onAddPassengerResponse(int msgType, bool success, const QString &message, const QJsonObject &data)
{
    Q_UNUSED(data);

    if (msgType != MSG_ADD_PASSENGER_RESPONSE) {
        return;
    }

    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &passenger::onAddPassengerResponse);

    if (success) {
        QMessageBox::information(this, "成功", "乘客添加成功！");
        clearInput();
        loadPassengers();
    } else {
        QMessageBox::warning(this, "错误", message);
    }
}

void passenger::onDeletePassengerResponse(int msgType, bool success, const QString &message, const QJsonObject &data)
{
    Q_UNUSED(data);

    if (msgType != MSG_DELETE_PASSENGER_RESPONSE) {
        return;
    }

    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &passenger::onDeletePassengerResponse);

    if (success) {
        QMessageBox::information(this, "成功", "乘客删除成功！");
        loadPassengers();
    } else {
        QMessageBox::warning(this, "错误", message);
    }
}
passenger::~passenger()
{
    delete ui;
}
