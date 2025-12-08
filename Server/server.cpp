#include "server.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QHostAddress>
#include <QDataStream>
#include "protocol.h"
#include <QSqlError>
#include <QDateTime>
#include <QRandomGenerator>

// 构造函数
Server::Server(QObject *parent) : QTcpServer(parent)
{
    initDatabase();
    
    // 连接新连接信号
    connect(this, &QTcpServer::newConnection,
            this, &Server::newConnection);
    
    qDebug() << "Server 初始化完成";
}

// 析构函数
Server::~Server()
{
    // 关闭所有客户端连接
    for (QTcpSocket *client : clients) {
        if (client) {
            client->disconnectFromHost();
            client->deleteLater();
        }
    }
    clients.clear();
    
    // 关闭数据库连接
    if (db.isOpen()) {
        db.close();
    }
}

// 初始化数据库
void Server::initDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");

    QString connectionString = "DRIVER={MySQL ODBC 9.5 Unicode Driver};"
                               "SERVER=127.0.0.1;"
                               "PORT=3306;"
                               "DATABASE=flightdb;"
                               "USER=root;"
                               "PASSWORD=@WUyh0601;"
                               "OPTION=3;";

    db.setDatabaseName(connectionString);

    if (!db.open()) {
        qDebug() << "服务端数据库连接失败：" << db.lastError().text();
    } else {
        qDebug() << "服务端数据库连接成功！";
    }
}

bool checkUserU(QString &username,QString &password){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "请先连接数据库！";
        return false;
    }
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString sql="SELECT Username, PWord FROM users where Username=? AND PWord=?";
    query.prepare(sql);
    query.addBindValue(username);
    query.addBindValue(password);

    bool result = false;
    if (query.exec() && query.next()) {
        result = true;
    }
    query.finish();
    return result;
}
bool checkUserI(QString &ID,QString &password){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "请先连接数据库！";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString sql="SELECT IDCard, PWord FROM users where IDCard=? AND PWord=?";
    query.prepare(sql);
    query.addBindValue(ID);
    query.addBindValue(password);

    bool result = false;
    if (query.exec() && query.next()) {
        result = true;
    }
    query.finish();
    return result;
}

QString GetUserID(QString &input,QString &password){
    if (!QSqlDatabase::database().isOpen()) {
        qDebug() << "请先连接数据库！";
        return QString();
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        qDebug() << "请先连接数据库！";
        return QString();
    }
    QSqlQuery query(db);  // 显式指定数据库连接

    query.prepare("SELECT UserID FROM users where Username=? AND PWord=?");
    query.addBindValue(input);
    query.addBindValue(password);
    if(query.exec()&&query.next()){

        QString uid = query.value(0).toString();
        query.finish();
        return uid;
    }
    query.prepare("SELECT UserID FROM users where IDCard=? AND PWord=?");
    query.addBindValue(input);
    query.addBindValue(password);
    if(query.exec()&&query.next()){
        QString uid = query.value(0).toString();
        query.finish();
        return uid;
    }
    query.finish();
    return QString();
}

void Server::handleLogin(QTcpSocket *client, const QJsonObject &data){
    QString username=data["username"].toString();
    QString password=data["password"].toString();
    
    QSqlQuery query(db);
    QString userid;
    
    // 先尝试用用户名登录
    query.prepare("SELECT UserID FROM users WHERE Username=? AND PWord=?");
    query.addBindValue(username);
    query.addBindValue(password);
    if (query.exec() && query.next()) {
        userid = query.value(0).toString();
    } else {
        // 再尝试用身份证登录
        query.prepare("SELECT UserID FROM users WHERE IDCard=? AND PWord=?");
        query.addBindValue(username);
        query.addBindValue(password);
        if (query.exec() && query.next()) {
            userid = query.value(0).toString();
        }
    }
    
    if (!userid.isEmpty()) {
        QJsonObject responseData;
        responseData["userID"] = userid;
        qDebug() << "登录成功，userID:" << userid;
        sendResponse(client, MSG_LOGIN_RESPONSE, true, "登录成功", responseData);
    } else {
        qDebug() << "登录失败：用户名或密码错误";
        sendResponse(client, MSG_LOGIN_RESPONSE, false, "用户名或密码错误");
    }
}

void Server::sendResponse(QTcpSocket *client, int msgType, bool success,
                          const QString &message, const QJsonObject &data)
{
    QJsonObject response;
    response["type"] = msgType;
    response["success"] = success;
    response["message"] = message;
    response["data"] = data;
    QJsonDocument doc(response);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream << (quint32)jsonData.size();
    packet.append(jsonData);

    client->write(packet);
    client->flush();
}
void Server::handleMessage(QTcpSocket *client, const QJsonObject &json)
{
    // 获取消息类型
    int msgType = json["type"].toInt();
    QJsonObject data = json["data"].toObject();

    qDebug() << "收到消息类型：" << msgType;

    // 根据消息类型分发到不同的处理函数
    switch (msgType) {
        case MSG_LOGIN:
            handleLogin(client, data);
            break;
        case MSG_REGISTER:
            handleRegister(client, data);
            break;
        case MSG_GET_USER_INFO:
            handleGetUserInfo(client, data);
            break;
        case MSG_UPDATE_USER_INFO:
            handleUpdateUserInfo(client, data);
            break;
        case MSG_SEARCH_TICKETS:
            handleSearchTickets(client, data);
            break;
        case MSG_CREATE_ORDER:
            handleCreateOrder(client, data);
            break;
        case MSG_GET_ORDERS:
            handleGetOrders(client, data);
            break;
        case MSG_CANCEL_ORDER:
            handleCancelOrder(client, data);
            break;
        case MSG_ADD_FAVORITE:
            handleAddFavorite(client, data);
            break;
        case MSG_GET_FAVORITES:
            handleGetFavorites(client, data);
            break;
        case MSG_DELETE_FAVORITE:
            handleDeleteFavorite(client, data);
            break;
        case MSG_PAY:
            handlePay(client, data);
            break;
        case MSG_GET_BALANCE:
            handleGetBalance(client, data);
            break;
        case MSG_ADD_PASSENGER:
            handleAddPassenger(client, data);
            break;
        case MSG_GET_PASSENGERS:
            handleGetPassengers(client, data);
            break;
        case MSG_DELETE_PASSENGER:
            handleDeletePassenger(client, data);
            break;
        case MSG_DELETE_ORDER:
            handleDeleteOrder(client, data);
            break;
        default:
            qDebug() << "未知的消息类型：" << msgType;
            sendResponse(client, msgType, false, "未知的消息类型");
            break;
    }
}

void Server::readClientData()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (!client) return;

    QDataStream in(client);
    in.setVersion(QDataStream::Qt_6_0);

    static QMap<QTcpSocket*, quint32> packetSizes;

    while (true) {
        if (packetSizes[client] == 0) {
            if (client->bytesAvailable() < static_cast<qint64>(sizeof(quint32))) {
                break; // 数据不够，等待
            }
            in >> packetSizes[client];
        }

        if (client->bytesAvailable() < static_cast<qint64>(packetSizes[client])) {
            break; // 数据不完整，等待
        }

        QByteArray jsonData = client->read(packetSizes[client]);
        packetSizes[client] = 0; // 重置

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);

        if (error.error == QJsonParseError::NoError && doc.isObject()) {
            handleMessage(client, doc.object());
        }
    }
}

// 新客户端连接
void Server::newConnection()
{
    QTcpSocket *client = this->nextPendingConnection();
    if (!client) return;
    
    clients.append(client);
    
    qDebug() << "新客户端连接：" << client->peerAddress().toString() 
             << ":" << client->peerPort();
    
    // 连接信号和槽
    connect(client, &QTcpSocket::readyRead,
            this, &Server::readClientData);
    
    connect(client, &QTcpSocket::disconnected,
            this, &Server::clientDisconnected);
}

// 客户端断开连接
void Server::clientDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        qDebug() << "客户端断开：" << client->peerAddress().toString();
        clients.removeAll(client);
        client->deleteLater();
    }
}

// 处理注册
void Server::handleRegister(QTcpSocket *client, const QJsonObject &data)
{
    QString username = data["username"].toString();
    QString password = data["password"].toString();
    QString idCard = data["idCard"].toString();
    
    // 检查用户名是否已存在
    QSqlQuery query(db);
    query.prepare("SELECT UserID FROM users WHERE Username=?");
    query.addBindValue(username);
    if (query.exec() && query.next()) {
        sendResponse(client, MSG_REGISTER_RESPONSE, false, "用户名已存在");
        return;
    }
    
    // 检查身份证是否已存在
    query.prepare("SELECT UserID FROM users WHERE IDCard=?");
    query.addBindValue(idCard);
    if (query.exec() && query.next()) {
        sendResponse(client, MSG_REGISTER_RESPONSE, false, "该ID已注册");
        return;
    }
    
    // 插入新用户
    query.prepare("INSERT INTO users (Username, PWord, IDCard) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(idCard);
    
    if (query.exec()) {
        QString userID = query.lastInsertId().toString();
        QJsonObject responseData;
        responseData["userID"] = userID;
        sendResponse(client, MSG_REGISTER_RESPONSE, true, "注册成功", responseData);
    } else {
        sendResponse(client, MSG_REGISTER_RESPONSE, false, "注册失败：" + query.lastError().text());
    }
}

// 处理获取用户信息
void Server::handleGetUserInfo(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    
    if (userID.isEmpty()) {
        sendResponse(client, MSG_GET_USER_INFO_RESPONSE, false, "用户ID不能为空");
        return;
    }
    
    QSqlQuery query(db);
    query.prepare("SELECT Username, IDCard, jianjie, avatar FROM users WHERE UserID = ?");
    query.addBindValue(userID.toInt());
    
    if (query.exec() && query.next()) {
        QJsonObject responseData;
        responseData["username"] = query.value(0).toString();
        responseData["idCard"] = query.value(1).toString();
        responseData["jianjie"] = query.value(2).toString();
        
        // 处理头像数据（转换为Base64）
        QByteArray avatarData = query.value(3).toByteArray();
        if (!avatarData.isEmpty()) {
            responseData["avatar"] = QString::fromLatin1(avatarData.toBase64());
        } else {
            responseData["avatar"] = "";
        }
        
        qDebug() << "获取用户信息成功，用户名：" << responseData["username"].toString();
        sendResponse(client, MSG_GET_USER_INFO_RESPONSE, true, "获取用户信息成功", responseData);
    } else {
        qDebug() << "获取用户信息失败：" << query.lastError().text();
        sendResponse(client, MSG_GET_USER_INFO_RESPONSE, false, "用户不存在或查询失败：" + query.lastError().text());
    }
}

// 处理更新用户信息
void Server::handleUpdateUserInfo(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    QString username = data["username"].toString();
    QString jianjie = data["jianjie"].toString();
    QString avatarBase64 = data["avatar"].toString();
    
    if (userID.isEmpty()) {
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, false, "用户ID不能为空");
        return;
    }
    
    QSqlQuery query(db);
    
    // 构建UPDATE语句
    QString sql = "UPDATE users SET ";
    QList<QVariant> bindValues;
    bool hasUpdate = false;
    
    if (!username.isEmpty()) {
        sql += "Username=?, ";
        bindValues.append(username);
        hasUpdate = true;
    }
    
    if (!jianjie.isEmpty() || data.contains("jianjie")) {
        sql += "jianjie=?, ";
        bindValues.append(jianjie);
        hasUpdate = true;
    }
    
    if (!avatarBase64.isEmpty()) {
        // 将Base64字符串转换为字节数组
        QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toLatin1());
        sql += "avatar=?, ";
        bindValues.append(avatarData);
        hasUpdate = true;
    }
    
    if (!hasUpdate) {
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, false, "没有需要更新的信息");
        return;
    }
    
    // 移除最后的 ", "
    sql.chop(2);
    sql += " WHERE UserID=?";
    bindValues.append(userID.toInt());
    
    query.prepare(sql);
    for (const auto &val : bindValues) {
        query.addBindValue(val);
    }
    
    if (query.exec()) {
        qDebug() << "更新用户信息成功，UserID:" << userID;
        QJsonObject responseData;
        responseData["userID"] = userID;
        if (!username.isEmpty()) {
            responseData["username"] = username;
        }
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, true, "用户信息更新成功", responseData);
    } else {
        qDebug() << "更新用户信息失败：" << query.lastError().text();
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, false, "更新失败：" + query.lastError().text());
    }
}

// 处理查询票务
void Server::handleSearchTickets(QTcpSocket *client, const QJsonObject &data)
{
    QString from = data["from"].toString();
    QString to = data["to"].toString();
    QString date = data["date"].toString();
    
    QSqlQuery query(db);
    QString sql = "SELECT flight_id, flight_number, departure_city, arrival_city, departure_time, "
                  "arrival_time, price, departure_airport, arrival_airport, airline_company, availableSeat "
                  "FROM flight_info WHERE status = 'On Time' "
                  "AND departure_time >= ? AND availableSeat > 0 ";
    
    if (!from.isEmpty()) {
        sql += "AND departure_city LIKE ? ";
    }
    if (!to.isEmpty()) {
        sql += "AND arrival_city LIKE ? ";
    }
    
    sql += "ORDER BY departure_time ASC";
    
    query.prepare(sql);
    query.addBindValue(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    
    if (!from.isEmpty()) {
        query.addBindValue(from + "%");
    }
    if (!to.isEmpty()) {
        query.addBindValue(to + "%");
    }
    
    QJsonArray ticketsArray;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject ticket;
            ticket["ticketID"] = query.value(0).toString();
            ticket["flightNumber"] = query.value(1).toString();
            ticket["departureCity"] = query.value(2).toString() + "-" + query.value(7).toString();
            ticket["arrivalCity"] = query.value(3).toString() + "-" + query.value(8).toString();
            
            QDateTime depTime = query.value(4).toDateTime();
            QDateTime arrTime = query.value(5).toDateTime();
            ticket["departureTime"] = depTime.toString("yyyy-MM-dd HH:mm");
            ticket["arrivalTime"] = arrTime.toString("yyyy-MM-dd HH:mm");
            
            ticket["price"] = query.value(6).toDouble();
            ticket["company"] = query.value(9).toString();
            ticket["availableSeats"] = query.value(10).toInt();
            
            ticketsArray.append(ticket);
        }
    }
    
    QJsonObject responseData;
    responseData["tickets"] = ticketsArray;
    sendResponse(client, MSG_SEARCH_RESPONSE, true, "查询成功", responseData);
}

// 检查时间冲突
bool Server::checkTimeConflict(const QString &passengerIDCard, int newTicketId)
{
    if (passengerIDCard.isEmpty()) {
        return false;
    }
    
    QSqlQuery newTicketQuery(db);
    newTicketQuery.prepare("SELECT departure_time, arrival_time FROM flight_info WHERE flight_id = ?");
    newTicketQuery.addBindValue(newTicketId);
    if (!newTicketQuery.exec() || !newTicketQuery.next()) {
        return false;
    }
    
    QDateTime newDepTime = newTicketQuery.value(0).toDateTime();
    QDateTime newArrTime = newTicketQuery.value(1).toDateTime();
    
    // 获取这个乘客未出行的订单
    QSqlQuery query(db);
    query.prepare("SELECT t.departure_time, t.arrival_time "
                  "FROM orders o "
                  "JOIN flight_info t ON o.TicketID = t.flight_id "
                  "WHERE o.PassengerIDCard = ? AND o.OrderStatus IN ('Pending', 'Confirmed', 'Paid') "
                  "AND t.departure_time > ?");
    query.addBindValue(passengerIDCard);
    query.addBindValue(QDateTime::currentDateTime());
    
    if (!query.exec()) {
        return false;
    }
    
    while (query.next()) {
        QDateTime existingDepTime = query.value(0).toDateTime();
        QDateTime existingArrTime = query.value(1).toDateTime();
        
        // 时间冲突判断逻辑
        bool timeOverlap = (newDepTime < existingArrTime && newArrTime > existingDepTime);
        
        if (timeOverlap) {
            return true;
        }
        
        // 检查换乘时间是否足够（最小30分钟）
        int minTransferTime = 30; // 分钟
        
        // 新票在已有票之后，检查换乘时间
        if (newDepTime > existingArrTime) {
            qint64 transferSeconds = existingArrTime.secsTo(newDepTime);
            if (transferSeconds < minTransferTime * 60) {
                return true;
            }
        }
        
        // 已有票在新票之后，检查换乘时间
        if (existingDepTime > newArrTime) {
            qint64 transferSeconds = newArrTime.secsTo(existingDepTime);
            if (transferSeconds < minTransferTime * 60) {
                return true;
            }
        }
    }
    return false;
}

// 处理创建订单
void Server::handleCreateOrder(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    QString ticketID = data["ticketID"].toString();
    QString passengerName = data["passengerName"].toString();
    QString passengerIDCard = data["passengerIDCard"].toString();
    QString contactPhone = data["contactPhone"].toString();
    int quantity = data["quantity"].toInt();
    
    // 验证输入
    if (passengerName.isEmpty()) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "请输入乘客姓名");
        return;
    }
    if (passengerIDCard.length() != 18) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "身份证号码必须是18位");
        return;
    }
    if (contactPhone.isEmpty()) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "请输入联系电话");
        return;
    }
    if (quantity <= 0) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "购票数量必须大于0");
        return;
    }
    
    // 获取票务信息
    QSqlQuery query(db);
    query.prepare("SELECT flight_id, flight_number, departure_city, arrival_city, departure_time, "
                  "arrival_time, price, departure_airport, arrival_airport, airline_company, availableSeat "
                  "FROM flight_info WHERE flight_id = ?");
    query.addBindValue(ticketID.toInt());
    
    if (!query.exec() || !query.next()) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "票务信息不存在");
        return;
    }
    
    double ticketPrice = query.value(6).toDouble();
    int availableSeat = query.value(10).toInt();
    QDateTime depTime = query.value(4).toDateTime();
    QDateTime arrTime = query.value(5).toDateTime();
    
    // 检查可用座位数
    if (availableSeat < quantity) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, 
                     QString("可用座位不足！当前可用：%1 张").arg(availableSeat));
        return;
    }
    
    // 检查时间冲突
    if (checkTimeConflict(passengerIDCard, ticketID.toInt())) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "检测到行程时间冲突！");
        return;
    }
    
    // 计算总价
    double totalPrice = ticketPrice * quantity;
    
    // 检查用户余额
    QSqlQuery balanceQuery(db);
    balanceQuery.prepare("SELECT Balance FROM users WHERE UserID = ?");
    balanceQuery.addBindValue(userID.toInt());
    if (!balanceQuery.exec() || !balanceQuery.next()) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "获取用户信息失败");
        return;
    }
    double userBalance = balanceQuery.value(0).toDouble();
    
    if (userBalance < totalPrice) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, 
                     QString("余额不足！当前余额: ¥%1，订单金额: ¥%2").arg(userBalance, 0, 'f', 2).arg(totalPrice, 0, 'f', 2));
        return;
    }
    
    // 生成订单号
    QString orderNo = "ORD" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss") +
                      QString::number(QRandomGenerator::global()->bounded(1000000), 10).rightJustified(6, '0');
    
    // 开始事务
    db.transaction();
    
    try {
        // 插入订单
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO orders (UserID, TicketID, OrderNo, PassengerName, "
                            "PassengerIDCard, ContactPhone, TicketCount, TotalPrice, OrderStatus) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, 'Paid')");
        insertQuery.addBindValue(userID.toInt());
        insertQuery.addBindValue(ticketID.toInt());
        insertQuery.addBindValue(orderNo);
        insertQuery.addBindValue(passengerName);
        insertQuery.addBindValue(passengerIDCard);
        insertQuery.addBindValue(contactPhone);
        insertQuery.addBindValue(quantity);
        insertQuery.addBindValue(totalPrice);
        
        if (!insertQuery.exec()) {
            db.rollback();
            sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "创建订单失败：" + insertQuery.lastError().text());
            return;
        }
        
        QString orderID = insertQuery.lastInsertId().toString();
        
        // 更新票务可用座位数
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE flight_info SET availableSeat = availableSeat - ? WHERE flight_id = ?");
        updateQuery.addBindValue(quantity);
        updateQuery.addBindValue(ticketID.toInt());
        
        if (!updateQuery.exec()) {
            db.rollback();
            sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "更新座位失败：" + updateQuery.lastError().text());
            return;
        }
        
        // 扣除用户余额
        QSqlQuery deductQuery(db);
        deductQuery.prepare("UPDATE users SET Balance = Balance - ? WHERE UserID = ?");
        deductQuery.addBindValue(totalPrice);
        deductQuery.addBindValue(userID.toInt());
        
        if (!deductQuery.exec()) {
            db.rollback();
            sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "扣款失败：" + deductQuery.lastError().text());
            return;
        }
        
        // 提交事务
        db.commit();
        
        QJsonObject responseData;
        responseData["orderID"] = orderID;
        responseData["orderNo"] = orderNo;
        responseData["totalPrice"] = totalPrice;
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, true, "订单创建成功", responseData);
    } catch (...) {
        db.rollback();
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "订票过程中发生错误");
    }
}

// 处理获取订单列表
void Server::handleGetOrders(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    
    QSqlQuery query(db);
    query.prepare("SELECT o.OrderID, o.OrderNo, o.OrderStatus, o.TicketCount, o.TotalPrice, "
                  "o.OrderTime, o.PassengerName, o.PassengerIDCard, o.ContactPhone, "
                  "t.departure_city, t.departure_airport, t.arrival_city, t.arrival_airport, "
                  "t.departure_time, t.arrival_time, t.flight_number, o.TicketID "
                  "FROM orders o "
                  "JOIN flight_info t ON o.TicketID = t.flight_id "
                  "WHERE o.UserID=? ORDER BY o.OrderTime DESC");
    query.addBindValue(userID.toInt());
    
    QJsonArray ordersArray;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject order;
            order["orderID"] = query.value(0).toString();
            order["orderNo"] = query.value(1).toString();
            order["status"] = query.value(2).toString();
            order["quantity"] = query.value(3).toInt();
            order["totalPrice"] = query.value(4).toDouble();
            order["orderDate"] = query.value(5).toString();
            order["passengerName"] = query.value(6).toString();
            order["passengerIDCard"] = query.value(7).toString();
            order["contactPhone"] = query.value(8).toString();
            order["departureCity"] = query.value(9).toString() + query.value(10).toString();
            order["arrivalCity"] = query.value(11).toString() + query.value(12).toString();
            
            QDateTime depTime = query.value(13).toDateTime();
            QDateTime arrTime = query.value(14).toDateTime();
            order["departureTime"] = depTime.toString("yyyy-MM-dd HH:mm");
            order["arrivalTime"] = arrTime.toString("yyyy-MM-dd HH:mm");
            
            order["flightNumber"] = query.value(15).toString();
            order["ticketID"] = query.value(16).toString();
            
            ordersArray.append(order);
        }
    }
    
    QJsonObject responseData;
    responseData["orders"] = ordersArray;
    sendResponse(client, MSG_GET_ORDERS_RESPONSE, true, "获取订单列表成功", responseData);
}

// 处理取消订单
void Server::handleCancelOrder(QTcpSocket *client, const QJsonObject &data)
{
    QString orderID = data["orderID"].toString();
    
    // 获取订单信息
    QSqlQuery orderQuery(db);
    orderQuery.prepare("SELECT TicketID, TicketCount, TotalPrice, UserID FROM orders WHERE OrderID = ?");
    orderQuery.addBindValue(orderID.toInt());
    
    if (!orderQuery.exec() || !orderQuery.next()) {
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "获取订单信息失败");
        return;
    }
    
    int ticketId = orderQuery.value(0).toInt();
    int ticketCount = orderQuery.value(1).toInt();
    double refundAmount = orderQuery.value(2).toDouble();
    int userId = orderQuery.value(3).toInt();
    
    // 开始事务
    db.transaction();
    
    try {
        // 更新订单状态
        QSqlQuery updateOrderQuery(db);
        updateOrderQuery.prepare("UPDATE orders SET OrderStatus = 'Cancelled' WHERE OrderID = ?");
        updateOrderQuery.addBindValue(orderID.toInt());
        if (!updateOrderQuery.exec()) {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "取消订单失败：" + updateOrderQuery.lastError().text());
            return;
        }
        
        // 恢复座位数
        QSqlQuery updateTicketQuery(db);
        updateTicketQuery.prepare("UPDATE flight_info SET availableSeat = availableSeat + ? WHERE flight_id = ?");
        updateTicketQuery.addBindValue(ticketCount);
        updateTicketQuery.addBindValue(ticketId);
        if (!updateTicketQuery.exec()) {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "恢复座位失败：" + updateTicketQuery.lastError().text());
            return;
        }
        
        // 退款到用户余额
        QSqlQuery refundQuery(db);
        refundQuery.prepare("UPDATE users SET Balance = Balance + ? WHERE UserID = ?");
        refundQuery.addBindValue(refundAmount);
        refundQuery.addBindValue(userId);
        if (!refundQuery.exec()) {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "退款失败：" + refundQuery.lastError().text());
            return;
        }
        
        // 提交事务
        if (!db.commit()) {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "提交事务失败");
            return;
        }
        
        QJsonObject responseData;
        responseData["refundAmount"] = refundAmount;
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, true, "订单已取消！订单金额已按原路返回！", responseData);
    } catch (...) {
        db.rollback();
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "取消订单过程中发生错误");
    }
}

// 处理添加收藏
void Server::handleAddFavorite(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    QString ticketID = data["ticketID"].toString();
    
    // 检查是否已收藏
    QSqlQuery query(db);
    query.prepare("SELECT FavoriteID FROM favorites WHERE UserID=? AND TicketID=?");
    query.addBindValue(userID);
    query.addBindValue(ticketID);
    
    if (query.exec() && query.next()) {
        sendResponse(client, MSG_ADD_FAVORITE_RESPONSE, false, "该票务已收藏");
        return;
    }
    
    // 添加收藏
    query.prepare("INSERT INTO favorites (UserID, TicketID) VALUES (?, ?)");
    query.addBindValue(userID);
    query.addBindValue(ticketID);
    
    if (query.exec()) {
        sendResponse(client, MSG_ADD_FAVORITE_RESPONSE, true, "收藏成功");
    } else {
        sendResponse(client, MSG_ADD_FAVORITE_RESPONSE, false, "收藏失败：" + query.lastError().text());
    }
}

// 处理获取收藏列表
void Server::handleGetFavorites(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    
    QSqlQuery query(db);
    query.prepare("SELECT f.*, t.FlightNumber, t.DepartureCity, t.ArrivalCity, "
                  "t.DepartureTime, t.ArrivalTime, t.FlightDate, "
                  "t.EconomyPrice, t.BusinessPrice, t.FirstClassPrice "
                  "FROM favorites f "
                  "JOIN tickets t ON f.TicketID = t.TicketID "
                  "WHERE f.UserID=?");
    query.addBindValue(userID);
    
    QJsonArray favoritesArray;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject favorite;
            favorite["favoriteID"] = query.value("FavoriteID").toString();
            favorite["ticketID"] = query.value("TicketID").toString();
            favorite["flightNumber"] = query.value("FlightNumber").toString();
            favorite["departureCity"] = query.value("DepartureCity").toString();
            favorite["arrivalCity"] = query.value("ArrivalCity").toString();
            favorite["departureTime"] = query.value("DepartureTime").toString();
            favorite["arrivalTime"] = query.value("ArrivalTime").toString();
            favorite["flightDate"] = query.value("FlightDate").toString();
            favorite["economyPrice"] = query.value("EconomyPrice").toDouble();
            favorite["businessPrice"] = query.value("BusinessPrice").toDouble();
            favorite["firstClassPrice"] = query.value("FirstClassPrice").toDouble();
            
            favoritesArray.append(favorite);
        }
    }
    
    QJsonObject responseData;
    responseData["favorites"] = favoritesArray;
    sendResponse(client, MSG_GET_FAVORITES_RESPONSE, true, "获取收藏列表成功", responseData);
}

// 处理删除收藏
void Server::handleDeleteFavorite(QTcpSocket *client, const QJsonObject &data)
{
    QString favoriteID = data["favoriteID"].toString();
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM favorites WHERE FavoriteID=?");
    query.addBindValue(favoriteID);
    
    if (query.exec() && query.numRowsAffected() > 0) {
        sendResponse(client, MSG_DELETE_FAVORITE_RESPONSE, true, "删除收藏成功");
    } else {
        sendResponse(client, MSG_DELETE_FAVORITE_RESPONSE, false, "删除收藏失败");
    }
}

// 处理支付请求
void Server::handlePay(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    double amount = data["amount"].toDouble();
    
    if (userID.isEmpty()) {
        sendResponse(client, MSG_PAY_RESPONSE, false, "用户ID不能为空");
        return;
    }
    
    if (amount <= 0) {
        sendResponse(client, MSG_PAY_RESPONSE, false, "充值金额必须大于0");
        return;
    }
    
    QSqlQuery query(db);
    db.transaction();
    
    // 更新 users 表中的 Balance 字段
    query.prepare("UPDATE users SET Balance = Balance + ? WHERE UserID = ?");
    query.addBindValue(amount);
    query.addBindValue(userID.toInt());
    
    if (query.exec()) {
        db.commit();
        
        // 获取更新后的余额
        query.prepare("SELECT Balance FROM users WHERE UserID = ?");
        query.addBindValue(userID.toInt());
        double newBalance = 0;
        if (query.exec() && query.next()) {
            newBalance = query.value(0).toDouble();
        }
        
        QJsonObject responseData;
        responseData["amount"] = amount;
        responseData["balance"] = newBalance;
        
        qDebug() << "支付成功，用户ID:" << userID << "，充值金额:" << amount << "，新余额:" << newBalance;
        sendResponse(client, MSG_PAY_RESPONSE, true, "充值成功", responseData);
    } else {
        db.rollback();
        qDebug() << "支付失败：" << query.lastError().text();
        sendResponse(client, MSG_PAY_RESPONSE, false, "充值失败：" + query.lastError().text());
    }
}

// 处理获取余额请求
void Server::handleGetBalance(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    
    if (userID.isEmpty()) {
        sendResponse(client, MSG_GET_BALANCE_RESPONSE, false, "用户ID不能为空");
        return;
    }
    
    QSqlQuery query(db);
    query.prepare("SELECT Balance FROM users WHERE UserID = ?");
    query.addBindValue(userID.toInt());
    
    if (query.exec() && query.next()) {
        double balance = query.value(0).toDouble();
        QJsonObject responseData;
        responseData["balance"] = balance;
        sendResponse(client, MSG_GET_BALANCE_RESPONSE, true, "获取余额成功", responseData);
    } else {
        sendResponse(client, MSG_GET_BALANCE_RESPONSE, false, "获取余额失败：" + query.lastError().text());
    }
}

// 处理添加乘客请求
void Server::handleAddPassenger(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    QString name = data["name"].toString();
    QString idCard = data["idCard"].toString();
    QString phone = data["phone"].toString();
    
    // 验证输入
    if (name.isEmpty() || idCard.isEmpty() || phone.isEmpty()) {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "姓名、身份证和手机号不能为空");
        return;
    }
    
    if (name.length() > 50) {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "姓名长度不能超过50个字符");
        return;
    }
    
    if (idCard.length() != 18) {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "身份证号码必须是18位");
        return;
    }
    
    if (phone.length() != 11) {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "手机号必须是11位");
        return;
    }
    
    // 检查身份证是否已存在
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT PassengerID FROM passengers WHERE UserID = ? AND IDCard = ?");
    checkQuery.addBindValue(userID.toInt());
    checkQuery.addBindValue(idCard);
    if (checkQuery.exec() && checkQuery.next()) {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "该身份证号码已存在");
        return;
    }
    
    // 插入乘客
    QSqlQuery query(db);
    query.prepare("INSERT INTO passengers (UserID, Name, IDCard, Phone) VALUES (?, ?, ?, ?)");
    query.addBindValue(userID.toInt());
    query.addBindValue(name);
    query.addBindValue(idCard);
    query.addBindValue(phone);
    
    if (query.exec()) {
        QString passengerID = query.lastInsertId().toString();
        QJsonObject responseData;
        responseData["passengerID"] = passengerID;
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, true, "乘客添加成功", responseData);
    } else {
        QString error = query.lastError().text();
        if (error.contains("unique_user_idcard") || error.contains("UNIQUE")) {
            sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "该身份证号码已存在");
        } else {
            sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "添加失败：" + error);
        }
    }
}

// 处理获取乘客列表请求
void Server::handleGetPassengers(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    
    if (userID.isEmpty()) {
        sendResponse(client, MSG_GET_PASSENGERS_RESPONSE, false, "用户ID不能为空");
        return;
    }
    
    QSqlQuery query(db);
    query.prepare("SELECT PassengerID, Name, IDCard, Phone FROM passengers WHERE UserID = ? ORDER BY CreatedTime DESC");
    query.addBindValue(userID.toInt());
    
    QJsonArray passengersArray;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject passenger;
            passenger["passengerID"] = query.value(0).toString();
            passenger["name"] = query.value(1).toString();
            passenger["idCard"] = query.value(2).toString();
            passenger["phone"] = query.value(3).toString();
            passengersArray.append(passenger);
        }
    }
    
    QJsonObject responseData;
    responseData["passengers"] = passengersArray;
    sendResponse(client, MSG_GET_PASSENGERS_RESPONSE, true, "获取乘客列表成功", responseData);
}

// 处理删除乘客请求
void Server::handleDeletePassenger(QTcpSocket *client, const QJsonObject &data)
{
    QString passengerID = data["passengerID"].toString();
    
    if (passengerID.isEmpty()) {
        sendResponse(client, MSG_DELETE_PASSENGER_RESPONSE, false, "乘客ID不能为空");
        return;
    }
    
    QSqlQuery query(db);
    query.prepare("DELETE FROM passengers WHERE PassengerID = ?");
    query.addBindValue(passengerID.toInt());
    
    if (query.exec() && query.numRowsAffected() > 0) {
        sendResponse(client, MSG_DELETE_PASSENGER_RESPONSE, true, "乘客删除成功");
    } else {
        sendResponse(client, MSG_DELETE_PASSENGER_RESPONSE, false, "删除失败：" + query.lastError().text());
    }
}

// 处理删除订单请求
void Server::handleDeleteOrder(QTcpSocket *client, const QJsonObject &data)
{
    QString orderID = data["orderID"].toString();
    
    if (orderID.isEmpty()) {
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "订单ID不能为空");
        return;
    }
    
    // 获取订单信息
    QSqlQuery orderQuery(db);
    orderQuery.prepare("SELECT TicketID, TicketCount FROM orders WHERE OrderID = ?");
    orderQuery.addBindValue(orderID.toInt());
    
    if (!orderQuery.exec() || !orderQuery.next()) {
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "获取订单信息失败");
        return;
    }
    
    // 开始事务
    db.transaction();
    
    try {
        // 更新订单状态为已取消
        QSqlQuery updateOrderQuery(db);
        updateOrderQuery.prepare("UPDATE orders SET OrderStatus = 'Cancelled' WHERE OrderID = ?");
        updateOrderQuery.addBindValue(orderID.toInt());
        if (!updateOrderQuery.exec()) {
            db.rollback();
            sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "删除订单失败：" + updateOrderQuery.lastError().text());
            return;
        }
        
        // 提交事务
        db.commit();
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, true, "订单已删除");
    } catch (...) {
        db.rollback();
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "删除订单过程中发生错误");
    }
}
