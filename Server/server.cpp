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
                               "DATABASE=flight;"
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
            if (client->bytesAvailable() < sizeof(quint32)) {
                break; // 数据不够，等待
            }
            in >> packetSizes[client];
        }

        if (client->bytesAvailable() < packetSizes[client]) {
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
    QString type = data["type"].toString();
    
    QSqlQuery query(db);
    QString sql = "SELECT * FROM tickets WHERE DepartureCity=? AND ArrivalCity=? AND FlightDate=?";
    
    if (type == "经济舱") {
        sql += " AND EconomyPrice IS NOT NULL";
    } else if (type == "商务舱") {
        sql += " AND BusinessPrice IS NOT NULL";
    } else if (type == "头等舱") {
        sql += " AND FirstClassPrice IS NOT NULL";
    }
    
    query.prepare(sql);
    query.addBindValue(from);
    query.addBindValue(to);
    query.addBindValue(date);
    
    QJsonArray ticketsArray;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject ticket;
            ticket["ticketID"] = query.value("TicketID").toString();
            ticket["flightNumber"] = query.value("FlightNumber").toString();
            ticket["departureCity"] = query.value("DepartureCity").toString();
            ticket["arrivalCity"] = query.value("ArrivalCity").toString();
            ticket["departureTime"] = query.value("DepartureTime").toString();
            ticket["arrivalTime"] = query.value("ArrivalTime").toString();
            ticket["flightDate"] = query.value("FlightDate").toString();
            ticket["economyPrice"] = query.value("EconomyPrice").toDouble();
            ticket["businessPrice"] = query.value("BusinessPrice").toDouble();
            ticket["firstClassPrice"] = query.value("FirstClassPrice").toDouble();
            ticket["availableSeats"] = query.value("AvailableSeats").toInt();
            
            ticketsArray.append(ticket);
        }
    }
    
    QJsonObject responseData;
    responseData["tickets"] = ticketsArray;
    sendResponse(client, MSG_SEARCH_RESPONSE, true, "查询成功", responseData);
}

// 处理创建订单
void Server::handleCreateOrder(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    QString ticketID = data["ticketID"].toString();
    QString seatType = data["seatType"].toString();
    int quantity = data["quantity"].toInt();
    
    // 获取票价
    QSqlQuery query(db);
    query.prepare("SELECT * FROM tickets WHERE TicketID=?");
    query.addBindValue(ticketID);
    
    if (!query.exec() || !query.next()) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "票务信息不存在");
        return;
    }
    
    double price = 0;
    if (seatType == "经济舱") {
        price = query.value("EconomyPrice").toDouble();
    } else if (seatType == "商务舱") {
        price = query.value("BusinessPrice").toDouble();
    } else if (seatType == "头等舱") {
        price = query.value("FirstClassPrice").toDouble();
    }
    
    double totalPrice = price * quantity;
    QString orderDate = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    
    // 创建订单
    query.prepare("INSERT INTO orders (UserID, TicketID, SeatType, Quantity, TotalPrice, OrderDate, Status) "
                  "VALUES (?, ?, ?, ?, ?, ?, '待支付')");
    query.addBindValue(userID);
    query.addBindValue(ticketID);
    query.addBindValue(seatType);
    query.addBindValue(quantity);
    query.addBindValue(totalPrice);
    query.addBindValue(orderDate);
    
    if (query.exec()) {
        QString orderID = query.lastInsertId().toString();
        QJsonObject responseData;
        responseData["orderID"] = orderID;
        responseData["totalPrice"] = totalPrice;
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, true, "订单创建成功", responseData);
    } else {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "订单创建失败：" + query.lastError().text());
    }
}

// 处理获取订单列表
void Server::handleGetOrders(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    
    QSqlQuery query(db);
    query.prepare("SELECT o.*, t.FlightNumber, t.DepartureCity, t.ArrivalCity, "
                  "t.DepartureTime, t.ArrivalTime, t.FlightDate "
                  "FROM orders o "
                  "JOIN tickets t ON o.TicketID = t.TicketID "
                  "WHERE o.UserID=? ORDER BY o.OrderDate DESC");
    query.addBindValue(userID);
    
    QJsonArray ordersArray;
    
    if (query.exec()) {
        while (query.next()) {
            QJsonObject order;
            order["orderID"] = query.value("OrderID").toString();
            order["ticketID"] = query.value("TicketID").toString();
            order["flightNumber"] = query.value("FlightNumber").toString();
            order["departureCity"] = query.value("DepartureCity").toString();
            order["arrivalCity"] = query.value("ArrivalCity").toString();
            order["departureTime"] = query.value("DepartureTime").toString();
            order["arrivalTime"] = query.value("ArrivalTime").toString();
            order["flightDate"] = query.value("FlightDate").toString();
            order["seatType"] = query.value("SeatType").toString();
            order["quantity"] = query.value("Quantity").toInt();
            order["totalPrice"] = query.value("TotalPrice").toDouble();
            order["orderDate"] = query.value("OrderDate").toString();
            order["status"] = query.value("Status").toString();
            
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
    
    QSqlQuery query(db);
    query.prepare("UPDATE orders SET Status='已取消' WHERE OrderID=?");
    query.addBindValue(orderID);
    
    if (query.exec() && query.numRowsAffected() > 0) {
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, true, "订单取消成功");
    } else {
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "订单取消失败");
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
