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
    for (QTcpSocket *client : clients)
    {
        if (client)
        {
            client->disconnectFromHost();
            client->deleteLater();
        }
    }
    clients.clear();

    // 关闭数据库连接
    if (db.isOpen())
    {
        db.close();
    }
}

// 初始化数据库
void Server::initDatabase()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setConnectOptions("SQL_ATTR_ODBC_VERSION=SQL_OV_ODBC3");

    QString connectionString = "DRIVER={MySQL ODBC 9.5 Unicode Driver};"
                               "SERVER=localhost;"
                               "PORT=3306;"
                               "DATABASE=flight;"
                               "USER=root;"
                               "PASSWORD=123456;"
                               "OPTION=3;";

    db.setDatabaseName(connectionString);

    if (!db.open())
    {
        qDebug() << "数据库连接失败:" << db.lastError().text();
    }
    else
    {
        qDebug() << "数据库连接成功";
    }
}


bool checkUserU(QString &username, QString &password)
{
    if (!QSqlDatabase::database().isOpen())
    {
        qDebug() << "请先连接数据库！";
        return false;
    }
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString sql = "SELECT Username, PWord FROM users where Username=? AND PWord=?";
    query.prepare(sql);
    query.addBindValue(username);
    query.addBindValue(password);

    bool result = false;
    if (query.exec() && query.next())
    {
        result = true;
    }
    query.finish();
    return result;
}
bool checkUserI(QString &ID, QString &password)
{
    if (!QSqlDatabase::database().isOpen())
    {
        qDebug() << "请先连接数据库！";
        return false;
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);
    QString sql = "SELECT IDCard, PWord FROM users where IDCard=? AND PWord=?";
    query.prepare(sql);
    query.addBindValue(ID);
    query.addBindValue(password);

    bool result = false;
    if (query.exec() && query.next())
    {
        result = true;
    }
    query.finish();
    return result;
}

QString GetUserID(QString &input, QString &password)
{
    if (!QSqlDatabase::database().isOpen())
    {
        qDebug() << "请先连接数据库！";
        return QString();
    }

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen())
    {
        qDebug() << "请先连接数据库！";
        return QString();
    }
    QSqlQuery query(db); // 显式指定数据库连接

    query.prepare("SELECT UserID FROM users where Username=? AND PWord=?");
    query.addBindValue(input);
    query.addBindValue(password);
    if (query.exec() && query.next())
    {

        QString uid = query.value(0).toString();
        query.finish();
        return uid;
    }
    query.prepare("SELECT UserID FROM users where IDCard=? AND PWord=?");
    query.addBindValue(input);
    query.addBindValue(password);
    if (query.exec() && query.next())
    {
        QString uid = query.value(0).toString();
        query.finish();
        return uid;
    }
    query.finish();
    return QString();
}

void Server::handleLogin(QTcpSocket *client, const QJsonObject &data)
{
    QString username = data["username"].toString();
    QString password = data["password"].toString();

    QSqlQuery query(db);
    QString userid;

    // 先尝试用用户名登录
    query.prepare("SELECT UserID FROM users WHERE Username=? AND PWord=?");
    query.addBindValue(username);
    query.addBindValue(password);
    if (query.exec() && query.next())
    {
        userid = query.value(0).toString();
    }
    else
    {
        // 再尝试用身份证登录
        query.prepare("SELECT UserID FROM users WHERE IDCard=? AND PWord=?");
        query.addBindValue(username);
        query.addBindValue(password);
        if (query.exec() && query.next())
        {
            userid = query.value(0).toString();
        }
    }

    if (!userid.isEmpty())
    {
        QJsonObject responseData;
        responseData["userID"] = userid;
        qDebug() << "登录成功，userID:" << userid;
        sendResponse(client, MSG_LOGIN_RESPONSE, true, "登录成功", responseData);
    }
    else
    {
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
    if (!db.isOpen())
    {
        if (!db.open())
        {
            sendResponse(client, json.value("type").toInt(), false,
                         "???????" + db.lastError().text());
            return;
        }
    }
    // 获取消息类型
    int msgType = json["type"].toInt();
    QJsonObject data = json["data"].toObject();

    qDebug() << "收到消息类型：" << msgType;

    // 根据消息类型分发到不同的处理函数
    switch (msgType)
    {
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
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if (!client)
        return;

    QDataStream in(client);
    in.setVersion(QDataStream::Qt_5_15);

    static QMap<QTcpSocket *, quint32> packetSizes;

    while (true)
    {
        if (packetSizes[client] == 0)
        {
            if (client->bytesAvailable() < static_cast<qint64>(sizeof(quint32)))
            {
                break; // 数据不够，等待
            }
            in >> packetSizes[client];
        }

        if (client->bytesAvailable() < static_cast<qint64>(packetSizes[client]))
        {
            break; // 数据不完整，等待
        }

        QByteArray jsonData = client->read(packetSizes[client]);
        packetSizes[client] = 0; // 重置

        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);

        if (error.error == QJsonParseError::NoError && doc.isObject())
        {
            handleMessage(client, doc.object());
        }
    }
}

// 新客户端连接
void Server::newConnection()
{
    QTcpSocket *client = this->nextPendingConnection();
    if (!client)
        return;

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
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());
    if (client)
    {
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
    if (query.exec() && query.next())
    {
        sendResponse(client, MSG_REGISTER_RESPONSE, false, "用户名已存在");
        return;
    }

    // 检查身份证是否已存在
    query.prepare("SELECT UserID FROM users WHERE IDCard=?");
    query.addBindValue(idCard);
    if (query.exec() && query.next())
    {
        sendResponse(client, MSG_REGISTER_RESPONSE, false, "该ID已注册");
        return;
    }

    // 插入新用户
    query.prepare("INSERT INTO users (Username, PWord, IDCard) VALUES (?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(idCard);

    bool useTransaction = db.transaction();

    if (query.exec())
    {
        QString userID = query.lastInsertId().toString();
        if (userID.isEmpty() || userID.toInt() <= 0) {
            QSqlQuery idQuery(db);
            idQuery.prepare("SELECT UserID FROM users WHERE Username=? AND IDCard=? ORDER BY UserID DESC LIMIT 1");
            idQuery.addBindValue(username);
            idQuery.addBindValue(idCard);
            if (idQuery.exec() && idQuery.next()) {
                userID = idQuery.value(0).toString();
            }
        }
        if (userID.isEmpty() || userID.toInt() <= 0) {
            if (useTransaction) {
                db.rollback();
            }
            sendResponse(client, MSG_REGISTER_RESPONSE, false, "注册失败：无法获取新用户ID");
            return;
        }

        QSqlQuery cleanupQuery(db);
        cleanupQuery.prepare("DELETE FROM favorites WHERE UserID=?");
        cleanupQuery.addBindValue(userID.toInt());
        if (!cleanupQuery.exec())
        {
            if (useTransaction) {
                db.rollback();
            }
            sendResponse(client, MSG_REGISTER_RESPONSE, false, "注册失败：" + cleanupQuery.lastError().text());
            return;
        }
        if (useTransaction) {
            if (!db.commit())
            {
                db.rollback();
                sendResponse(client, MSG_REGISTER_RESPONSE, false, "注册失败：" + db.lastError().text());
                return;
            }
        }
        qDebug() << "handleRegister new userID:" << userID << "username:" << username;
        QJsonObject responseData;
        responseData["userID"] = userID;
        sendResponse(client, MSG_REGISTER_RESPONSE, true, "注册成功", responseData);
    }
    else
    {
        if (useTransaction) {
            db.rollback();
        }
        sendResponse(client, MSG_REGISTER_RESPONSE, false, "注册失败：" + query.lastError().text());
    }
}

// 处理获取用户信息
void Server::handleGetUserInfo(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();

    if (userID.isEmpty())
    {
        sendResponse(client, MSG_GET_USER_INFO_RESPONSE, false, "用户ID不能为空");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT Username, IDCard, jianjie, avatar, Balance FROM users WHERE UserID = ?");
    query.addBindValue(userID.toInt());

    if (query.exec() && query.next())
    {
        QJsonObject responseData;
        responseData["username"] = query.value(0).toString();
        responseData["idCard"] = query.value(1).toString();
        responseData["jianjie"] = query.value(2).toString();
        responseData["balance"] = query.value(4).toDouble();

        // 处理头像数据（转换为Base64）
        QByteArray avatarData = query.value(3).toByteArray();
        if (!avatarData.isEmpty())
        {
            responseData["avatar"] = QString::fromLatin1(avatarData.toBase64());
        }
        else
        {
            responseData["avatar"] = "";
        }

        qDebug() << "获取用户信息成功，用户名：" << responseData["username"].toString();
        sendResponse(client, MSG_GET_USER_INFO_RESPONSE, true, "获取用户信息成功", responseData);
    }
    else
    {
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

    if (userID.isEmpty())
    {
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, false, "用户ID不能为空");
        return;
    }

    QSqlQuery query(db);

    // 构建UPDATE语句
    QString sql = "UPDATE users SET ";
    QList<QVariant> bindValues;
    bool hasUpdate = false;

    if (!username.isEmpty())
    {
        sql += "Username=?, ";
        bindValues.append(username);
        hasUpdate = true;
    }

    if (!jianjie.isEmpty() || data.contains("jianjie"))
    {
        sql += "jianjie=?, ";
        bindValues.append(jianjie);
        hasUpdate = true;
    }

    if (!avatarBase64.isEmpty())
    {
        // 将Base64字符串转换为字节数组
        QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toLatin1());
        sql += "avatar=?, ";
        bindValues.append(avatarData);
        hasUpdate = true;
    }

    if (!hasUpdate)
    {
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, false, "没有需要更新的信息");
        return;
    }

    // 移除最后的 ", "
    sql.chop(2);
    sql += " WHERE UserID=?";
    bindValues.append(userID.toInt());

    query.prepare(sql);
    for (const auto &val : bindValues)
    {
        query.addBindValue(val);
    }

    if (query.exec())
    {
        qDebug() << "更新用户信息成功，UserID:" << userID;
        QJsonObject responseData;
        responseData["userID"] = userID;
        if (!username.isEmpty())
        {
            responseData["username"] = username;
        }
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, true, "用户信息更新成功", responseData);
    }
    else
    {
        qDebug() << "更新用户信息失败：" << query.lastError().text();
        sendResponse(client, MSG_UPDATE_USER_INFO_RESPONSE, false, "更新失败：" + query.lastError().text());
    }
}

// 处理查询票务（根据 Management 版 Deal 的逻辑改造，支持分页和收藏状态）
void Server::handleSearchTickets(QTcpSocket *client, const QJsonObject &data)
{
    // 精确查询（订单弹窗加载单条航班）
    int ticketIdFilter = data["ticketID"].toInt(0);
    if (ticketIdFilter <= 0)
    {
        ticketIdFilter = data["ticketId"].toInt(0);
    }
    QString userID = data["userID"].toString(); // 用于返回收藏状态
    if (ticketIdFilter > 0)
    {
        QSqlQuery singleQuery(db);
        singleQuery.prepare("SELECT flight_id, flight_number, departure_city, arrival_city, departure_time, "
                            "arrival_time, price, departure_airport, arrival_airport, airline_company, availableSeat "
                            "FROM flight_info WHERE flight_id = ?");
        singleQuery.addBindValue(ticketIdFilter);

        if (!singleQuery.exec() || !singleQuery.next())
        {
            sendResponse(client, MSG_SEARCH_RESPONSE, false, "未找到对应航班");
            return;
        }

        QJsonArray ticketsArray;
        QJsonObject ticket;
        ticket["ticketID"] = singleQuery.value(0).toInt();
        ticket["ticketNo"] = singleQuery.value(1).toString();
        ticket["ticketType"] = "Flight";

        QString depCity = singleQuery.value(2).toString();
        QString depAirport = singleQuery.value(7).toString();
        QString arrCity = singleQuery.value(3).toString();
        QString arrAirport = singleQuery.value(8).toString();
        ticket["departureCity"] = depCity + "-" + depAirport;
        ticket["arrivalCity"] = arrCity + "-" + arrAirport;

        QDateTime depTime = singleQuery.value(4).toDateTime();
        QDateTime arrTime = singleQuery.value(5).toDateTime();
        ticket["departureTime"] = depTime.toString("yyyy-MM-dd HH:mm");
        ticket["arrivalTime"] = arrTime.toString("yyyy-MM-dd HH:mm");

        ticket["price"] = singleQuery.value(6).toDouble();
        ticket["company"] = singleQuery.value(9).toString();
        ticket["availableSeats"] = singleQuery.value(10).toInt();
        ticketsArray.append(ticket);

        QJsonObject responseData;
        responseData["tickets"] = ticketsArray;
        responseData["totalCount"] = 1;
        responseData["totalPage"] = 1;
        responseData["currentPage"] = 1;
        responseData["pageSize"] = 1;

        if (!userID.isEmpty())
        {
            QJsonArray favoritesArray;
            QSqlQuery favQuery(db);
            favQuery.prepare("SELECT TicketID FROM favorites WHERE UserID = ?");
            favQuery.addBindValue(userID.toInt());
            if (favQuery.exec())
            {
                while (favQuery.next())
                {
                    favoritesArray.append(favQuery.value(0).toInt());
                }
            }
            responseData["favorites"] = favoritesArray;
        }

        sendResponse(client, MSG_SEARCH_RESPONSE, true, "查询成功", responseData);
        return;
    }

    QString from = data["from"].toString();
    QString to = data["to"].toString();
    QString dateStr = data["date"].toString();  // yyyy-MM-dd
    QString type = data["type"].toString();     // 目前仅支持 Flight，可预留
    // userID 已在上方声明
    int page = data["page"].toInt(1);
    int pageSize = data["pageSize"].toInt(50);

    if (page <= 0)
        page = 1;
    if (pageSize <= 0)
        pageSize = 50;

    // 计算查询起始时间：取“用户选择的日期 00:00:00”和“当前时间”中的较大者
    QString startTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString searchTimeStr = startTimeStr;
    if (!dateStr.isEmpty()) {
        QDateTime searchTime = QDateTime::fromString(dateStr, "yyyy-MM-dd hh:mm:ss");
        if (!searchTime.isValid()) {
            QDate queryDate = QDate::fromString(dateStr, "yyyy-MM-dd");
            if (queryDate.isValid()) {
                searchTime = QDateTime(queryDate, QTime(0, 0, 0));
            }
        }
        if (searchTime.isValid()) {
            searchTimeStr = searchTime.toString("yyyy-MM-dd hh:mm:ss");
        }
    }
    QString startTime = (searchTimeStr > startTimeStr) ? searchTimeStr : startTimeStr;

    QSqlQuery query(db);
    QString baseSql = "FROM flight_info WHERE status = 'On Time' "
                      "AND departure_time >= ? AND availableSeat > 0 ";

    if (!from.isEmpty())
    {
        baseSql += "AND departure_city LIKE ? ";
    }
    if (!to.isEmpty())
    {
        baseSql += "AND arrival_city LIKE ? ";
    }

    // 目前仅有航班业务，如果以后有火车/汽车，可在此扩展 type 过滤
    Q_UNUSED(type);

    // 先查询总条数
    QString countSql = "SELECT COUNT(*) " + baseSql;
    if (!query.prepare(countSql))
    {
        sendResponse(client, MSG_SEARCH_RESPONSE, false,
                     "统计总数预处理失败：" + query.lastError().text());
        return;
    }

    query.addBindValue(startTime);
    if (!from.isEmpty())
    {
        query.addBindValue(from + "%");
    }
    if (!to.isEmpty())
    {
        query.addBindValue(to + "%");
    }

    int totalCount = 0;
    if (query.exec() && query.next())
    {
        totalCount = query.value(0).toInt();
    }
    else
    {
        sendResponse(client, MSG_SEARCH_RESPONSE, false,
                     "统计总数执行失败：" + query.lastError().text());
        return;
    }

    int totalPage = 0;
    if (totalCount > 0)
    {
        totalPage = (totalCount + pageSize - 1) / pageSize;
    }
    if (totalPage > 0 && page > totalPage)
    {
        page = totalPage;
    }

    // 再查询当前页数据
    int limit = pageSize;
    int offset = (page - 1) * pageSize;
    if (offset < 0)
        offset = 0;
    QString dataSql = "SELECT flight_id, flight_number, departure_city, arrival_city, departure_time, "
                      "arrival_time, price, departure_airport, arrival_airport, airline_company, availableSeat " +
                      baseSql +
                      QString(" ORDER BY departure_time ASC LIMIT %1, %2").arg(offset).arg(limit);

    query.clear();
    if (!query.prepare(dataSql))
    {
        sendResponse(client, MSG_SEARCH_RESPONSE, false,
                     "查询预处理失败：" + query.lastError().text());
        return;
    }

    query.addBindValue(startTime);

    if (!from.isEmpty())
    {
        query.addBindValue(from + "%");
    }
    if (!to.isEmpty())
    {
        query.addBindValue(to + "%");
    }

    QJsonArray ticketsArray;

    if (query.exec())
    {
        while (query.next())
        {
            QJsonObject ticket;

            int ticketId = query.value(0).toInt();
            ticket["ticketID"] = ticketId;
            ticket["ticketNo"] = query.value(1).toString(); // 编号
            ticket["ticketType"] = "Flight";                // 当前只有航班
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
    else
    {
        sendResponse(client, MSG_SEARCH_RESPONSE, false,
                     "查询执行失败：" + query.lastError().text());
        return;
    }

    QJsonObject responseData;
    responseData["tickets"] = ticketsArray;
    responseData["totalCount"] = totalCount;
    responseData["totalPage"] = totalPage;
    responseData["currentPage"] = page;
    responseData["pageSize"] = pageSize;

    // 如果提供了 userID，则一并返回该用户已收藏的 ticketID 列表
    if (!userID.isEmpty())
    {
        QJsonArray favoritesArray;
        QSqlQuery favQuery(db);
        favQuery.prepare("SELECT TicketID FROM favorites WHERE UserID = ?");
        favQuery.addBindValue(userID.toInt());
        if (favQuery.exec())
        {
            while (favQuery.next())
            {
                favoritesArray.append(favQuery.value(0).toInt());
            }
        }
        responseData["favorites"] = favoritesArray;
    }

    sendResponse(client, MSG_SEARCH_RESPONSE, true, "查询成功", responseData);
}

// 检查时间冲突
bool Server::checkTimeConflict(const QString &passengerIDCard, int newTicketId)
{
    if (passengerIDCard.isEmpty())
    {
        return false;
    }

    QSqlQuery newTicketQuery(db);
    newTicketQuery.prepare("SELECT departure_time, arrival_time FROM flight_info WHERE flight_id = ?");
    newTicketQuery.addBindValue(newTicketId);
    if (!newTicketQuery.exec() || !newTicketQuery.next())
    {
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

    if (!query.exec())
    {
        return false;
    }

    while (query.next())
    {
        QDateTime existingDepTime = query.value(0).toDateTime();
        QDateTime existingArrTime = query.value(1).toDateTime();

        // 时间冲突判断逻辑
        bool timeOverlap = (newDepTime < existingArrTime && newArrTime > existingDepTime);

        if (timeOverlap)
        {
            return true;
        }

        // 检查换乘时间是否足够（最小30分钟）
        int minTransferTime = 30; // 分钟

        // 新票在已有票之后，检查换乘时间
        if (newDepTime > existingArrTime)
        {
            qint64 transferSeconds = existingArrTime.secsTo(newDepTime);
            if (transferSeconds < minTransferTime * 60)
            {
                return true;
            }
        }

        // 已有票在新票之后，检查换乘时间
        if (existingDepTime > newArrTime)
        {
            qint64 transferSeconds = newArrTime.secsTo(existingDepTime);
            if (transferSeconds < minTransferTime * 60)
            {
                return true;
            }
        }
    }
    return false;
}

// 处理创建订单
void Server::handleCreateOrder(QTcpSocket *client, const QJsonObject &data)
{
    int userId = data["userID"].toInt();
    if (userId == 0) {
        userId = data["userId"].toInt();
    }
    if (userId == 0) {
        userId = data["userID"].toString().toInt();
    }
    if (userId == 0) {
        userId = data["userId"].toString().toInt();
    }
    int ticketId = data["ticketID"].toInt();
    if (ticketId == 0) {
        ticketId = data["ticketID"].toString().toInt();
    }
    QString passengerName = data["passengerName"].toString();
    QString passengerIDCard = data["passengerIDCard"].toString();
    QString contactPhone = data["contactPhone"].toString();
    // 兼容旧前端字段 ticketCount
    int quantity = data["quantity"].toInt();
    if (quantity == 0)
    {
        quantity = data["ticketCount"].toInt();
    }

    // 验证输入
    if (userId <= 0) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "用户信息无效");
        return;
    }
    if (ticketId <= 0) {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "票务信息不存在");
        return;
    }
    if (passengerName.isEmpty())
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "请输入乘客姓名");
        return;
    }
    if (passengerIDCard.length() != 18)
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "身份证号码必须是18位");
        return;
    }
    if (contactPhone.isEmpty())
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "请输入联系电话");
        return;
    }
    if (quantity <= 0)
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "购票数量必须大于0");
        return;
    }

    // 获取票务信息
    QSqlQuery query(db);
    query.prepare("SELECT flight_id, flight_number, departure_city, arrival_city, departure_time, "
                  "arrival_time, price, departure_airport, arrival_airport, airline_company, availableSeat "
                  "FROM flight_info WHERE flight_id = ?");
    query.addBindValue(ticketId);

    if (!query.exec() || !query.next())
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "票务信息不存在");
        return;
    }

    double ticketPrice = query.value(6).toDouble();
    int availableSeat = query.value(10).toInt();
    QDateTime depTime = query.value(4).toDateTime();
    QDateTime arrTime = query.value(5).toDateTime();

    // 检查可用座位数
    if (availableSeat < quantity)
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false,
                     QString("可用座位不足！当前可用：%1 张").arg(availableSeat));
        return;
    }

    // 检查时间冲突
    if (checkTimeConflict(passengerIDCard, ticketId))
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "检测到行程时间冲突！");
        return;
    }

    QString cabinClass = data["cabinClass"].toString();
    if (cabinClass.isEmpty()) {
        cabinClass = "经济舱";
    }
    double unitPrice = ticketPrice;
    if (cabinClass == "商务舱" || cabinClass == "头等舱") {
        unitPrice += 200.0;
    }
    // 计算总价
    double totalPrice = unitPrice * quantity;

    // 检查用户余额
    QSqlQuery balanceQuery(db);
    balanceQuery.prepare("SELECT Balance FROM users WHERE UserID = ?");
    balanceQuery.addBindValue(userId);
    if (!balanceQuery.exec() || !balanceQuery.next())
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "获取用户信息失败");
        return;
    }
    double userBalance = balanceQuery.value(0).toDouble();

    if (userBalance < totalPrice)
    {
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false,
                     QString("余额不足！当前余额: ¥%1，订单金额: ¥%2").arg(userBalance, 0, 'f', 2).arg(totalPrice, 0, 'f', 2));
        return;
    }

    // 生成订单号
    QString orderNo = "ORD" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss") +
                      QString::number(QRandomGenerator::global()->bounded(1000000), 10).rightJustified(6, '0');

    // 开始事务
    db.transaction();

    try
    {
        // 插入订单
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO orders (UserID, TicketID, OrderNo, PassengerName, "
                            "PassengerIDCard, ContactPhone, TicketCount, TotalPrice, OrderStatus, CabinClass) "
                            "VALUES (?, ?, ?, ?, ?, ?, ?, ?, 'Paid', ?)");
        insertQuery.addBindValue(userId);
        insertQuery.addBindValue(ticketId);
        insertQuery.addBindValue(orderNo);
        insertQuery.addBindValue(passengerName);
        insertQuery.addBindValue(passengerIDCard);
        insertQuery.addBindValue(contactPhone);
        insertQuery.addBindValue(quantity);
        insertQuery.addBindValue(totalPrice);
        insertQuery.addBindValue(cabinClass);

        if (!insertQuery.exec())
        {
            db.rollback();
            sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "创建订单失败：" + insertQuery.lastError().text());
            return;
        }

        QString orderID = insertQuery.lastInsertId().toString();

        // 更新票务可用座位数
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE flight_info SET availableSeat = availableSeat - ? WHERE flight_id = ?");
        updateQuery.addBindValue(quantity);
        updateQuery.addBindValue(ticketId);

        if (!updateQuery.exec())
        {
            db.rollback();
            sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "更新座位失败：" + updateQuery.lastError().text());
            return;
        }

        // 扣除用户余额
        QSqlQuery deductQuery(db);
        deductQuery.prepare("UPDATE users SET Balance = Balance - ? WHERE UserID = ?");
        deductQuery.addBindValue(totalPrice);
        deductQuery.addBindValue(userId);

        if (!deductQuery.exec())
        {
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
    }
    catch (...)
    {
        db.rollback();
        sendResponse(client, MSG_CREATE_ORDER_RESPONSE, false, "订票过程中发生错误");
    }
}

// 处理获取订单列表
void Server::handleGetOrders(QTcpSocket *client, const QJsonObject &data)
{
    int userId = data["userID"].toInt();
    if (userId == 0)
    {
        userId = data["userID"].toString().toInt();
    }
    if (userId <= 0)
    {
        sendResponse(client, MSG_GET_ORDERS_RESPONSE, false, "用户信息无效");
        return;
    }

    qDebug() << "handleGetOrders userId:" << userId;

    QSqlQuery query(db);
    query.prepare("SELECT o.OrderID, o.OrderNo, o.OrderStatus, o.TicketCount, o.TotalPrice, "
                  "o.OrderTime, o.PassengerName, o.PassengerIDCard, o.ContactPhone, "
                  "t.departure_city, t.departure_airport, t.arrival_city, t.arrival_airport, "
                  "t.departure_time, t.arrival_time, t.flight_number, o.TicketID, o.CabinClass "
                  "FROM orders o "
                  "LEFT JOIN flight_info t ON o.TicketID = t.flight_id "
                  "WHERE o.UserID=? ORDER BY o.OrderTime DESC");
    query.addBindValue(userId);

    QJsonArray ordersArray;

    if (query.exec())
    {
        while (query.next())
        {
            QJsonObject order;
            order["orderID"] = query.value(0).toString();
            order["orderNo"] = query.value(1).toString();
            order["status"] = query.value(2).toString();
            order["quantity"] = query.value(3).toInt();
            order["totalPrice"] = query.value(4).toDouble();
            order["orderDate"] = query.value(5).toDateTime().toString("yyyy-MM-dd HH:mm:ss");
            order["passengerName"] = query.value(6).toString();
            order["passengerIDCard"] = query.value(7).toString();
            order["contactPhone"] = query.value(8).toString();
            QString depCity = query.value(9).toString();
            QString depAirport = query.value(10).toString();
            QString arrCity = query.value(11).toString();
            QString arrAirport = query.value(12).toString();
            QString departureCity = depCity;
            if (!depAirport.isEmpty()) {
                departureCity += "-" + depAirport;
            }
            QString arrivalCity = arrCity;
            if (!arrAirport.isEmpty()) {
                arrivalCity += "-" + arrAirport;
            }
            order["departureCity"] = departureCity;
            order["arrivalCity"] = arrivalCity;

            QDateTime depTime = query.value(13).toDateTime();
            QDateTime arrTime = query.value(14).toDateTime();
            if (depTime.isValid()) {
                order["departureTime"] = depTime.toString("yyyy-MM-dd HH:mm");
            } else {
                order["departureTime"] = query.value(13).toString();
            }
            if (arrTime.isValid()) {
                order["arrivalTime"] = arrTime.toString("yyyy-MM-dd HH:mm");
            } else {
                order["arrivalTime"] = query.value(14).toString();
            }

            order["flightNumber"] = query.value(15).toString();
            order["ticketID"] = query.value(16).toString();
            order["cabinClass"] = query.value(17).toString();
            order["ticketType"] = "Flight";
            order["ticketCount"] = order["quantity"];
            order["orderStatus"] = order["status"];

            ordersArray.append(order);
        }
    }

    QJsonObject responseData;
    responseData["orders"] = ordersArray;
    if (userId > 0)
    {
        QJsonArray favoritesArray;
        QSqlQuery favQuery(db);
        favQuery.prepare("SELECT TicketID FROM favorites WHERE UserID = ?");
        favQuery.addBindValue(userId);
        if (favQuery.exec())
        {
            while (favQuery.next())
            {
                favoritesArray.append(favQuery.value(0).toInt());
            }
        }
        responseData["favorites"] = favoritesArray;
    }
    qDebug() << "handleGetOrders count:" << ordersArray.size();
    sendResponse(client, MSG_GET_ORDERS_RESPONSE, true, "获取订单列表成功", responseData);
}

// 处理取消订单
void Server::handleCancelOrder(QTcpSocket *client, const QJsonObject &data)
{
    int orderId = data["orderID"].toInt();
    if (orderId == 0) {
        orderId = data["orderID"].toString().toInt();
    }
    if (orderId <= 0) {
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "订单ID无效");
        return;
    }

    // 获取订单信息
    QSqlQuery orderQuery(db);
    orderQuery.prepare("SELECT TicketID, TicketCount, TotalPrice, UserID FROM orders WHERE OrderID = ?");
    orderQuery.addBindValue(orderId);

    if (!orderQuery.exec() || !orderQuery.next())
    {
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "获取订单信息失败");
        return;
    }

    int ticketId = orderQuery.value(0).toInt();
    int ticketCount = orderQuery.value(1).toInt();
    double refundAmount = orderQuery.value(2).toDouble();
    int userId = orderQuery.value(3).toInt();

    // 开始事务
    db.transaction();

    try
    {
        // 更新订单状态
        QSqlQuery updateOrderQuery(db);
        updateOrderQuery.prepare("UPDATE orders SET OrderStatus = 'Cancelled' WHERE OrderID = ?");
        updateOrderQuery.addBindValue(orderId);
        if (!updateOrderQuery.exec())
        {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "取消订单失败：" + updateOrderQuery.lastError().text());
            return;
        }

        // 恢复座位数
        QSqlQuery updateTicketQuery(db);
        updateTicketQuery.prepare("UPDATE flight_info SET availableSeat = availableSeat + ? WHERE flight_id = ?");
        updateTicketQuery.addBindValue(ticketCount);
        updateTicketQuery.addBindValue(ticketId);
        if (!updateTicketQuery.exec())
        {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "恢复座位失败：" + updateTicketQuery.lastError().text());
            return;
        }

        // 退款到用户余额
        QSqlQuery refundQuery(db);
        refundQuery.prepare("UPDATE users SET Balance = Balance + ? WHERE UserID = ?");
        refundQuery.addBindValue(refundAmount);
        refundQuery.addBindValue(userId);
        if (!refundQuery.exec())
        {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "退款失败：" + refundQuery.lastError().text());
            return;
        }

        // 提交事务
        if (!db.commit())
        {
            db.rollback();
            sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "提交事务失败");
            return;
        }

        QJsonObject responseData;
        responseData["refundAmount"] = refundAmount;
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, true, "订单已取消！订单金额已按原路返回！", responseData);
    }
    catch (...)
    {
        db.rollback();
        sendResponse(client, MSG_CANCEL_ORDER_RESPONSE, false, "取消订单过程中发生错误");
    }
}

// 处理添加收藏
void Server::handleAddFavorite(QTcpSocket *client, const QJsonObject &data)
{
    int userId = data["userID"].toInt();
    if (userId == 0) {
        userId = data["userID"].toString().toInt();
    }
    int ticketId = data["ticketID"].toInt();
    if (ticketId == 0) {
        ticketId = data["ticketId"].toInt();
    }
    if (ticketId == 0) {
        ticketId = data["ticketID"].toString().toInt();
    }
    if (ticketId == 0) {
        ticketId = data["ticketId"].toString().toInt();
    }

    // 基础校验，避免空值写入导致数据库报错
    if (userId <= 0 || ticketId <= 0)
    {
        sendResponse(client, MSG_ADD_FAVORITE_RESPONSE, false, "用户或票务信息缺失");
        return;
    }

    // 检查是否已收藏
    QSqlQuery query(db);
    query.prepare("SELECT FavoriteID FROM favorites WHERE UserID=? AND TicketID=?");
    query.addBindValue(userId);
    query.addBindValue(ticketId);

    if (query.exec() && query.next())
    {
        sendResponse(client, MSG_ADD_FAVORITE_RESPONSE, false, "该票务已收藏");
        return;
    }

    // 添加收藏
    query.prepare("INSERT INTO favorites (UserID, TicketID) VALUES (?, ?)");
    query.addBindValue(userId);
    query.addBindValue(ticketId);

    if (query.exec())
    {
        sendResponse(client, MSG_ADD_FAVORITE_RESPONSE, true, "收藏成功");
    }
    else
    {
        sendResponse(client, MSG_ADD_FAVORITE_RESPONSE, false, "收藏失败：" + query.lastError().text());
    }
}

// 处理获取收藏列表
void Server::handleGetFavorites(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    qDebug() << "handleGetFavorites userID:" << userID;
    QSqlQuery query(db);
    query.prepare("SELECT f.FavoriteID, f.TicketID, "
                  "t.flight_number, t.departure_city, t.arrival_city, "
                  "t.departure_time, t.arrival_time, "
                  "t.price, t.departure_airport, t.arrival_airport, t.airline_company "
                  "FROM favorites f "
                  "JOIN flight_info t ON f.TicketID = t.flight_id "
                  "WHERE f.UserID = ?");
    query.addBindValue(userID.toInt());

    if (!query.exec())
    {
        sendResponse(client, MSG_GET_FAVORITES_RESPONSE, false,
                     "获取收藏列表失败：" + query.lastError().text());
        return;
    }

    QJsonArray favoritesArray;
    while (query.next())
    {
        QJsonObject favorite;
        favorite["favoriteID"] = query.value("FavoriteID").toInt();
        favorite["ticketID"] = query.value("TicketID").toInt();
        favorite["ticketType"] = "Flight";
        favorite["ticketNo"] = query.value("flight_number").toString();

        // 保持与搜索结果一致的城市/机场展示格式
        QString depCity = query.value("departure_city").toString();
        QString depAirport = query.value("departure_airport").toString();
        QString arrCity = query.value("arrival_city").toString();
        QString arrAirport = query.value("arrival_airport").toString();
        favorite["departureCity"] = depCity + "-" + depAirport;
        favorite["arrivalCity"] = arrCity + "-" + arrAirport;

        QDateTime depTime = query.value("departure_time").toDateTime();
        QDateTime arrTime = query.value("arrival_time").toDateTime();
        favorite["departureTime"] = depTime.toString("yyyy-MM-dd HH:mm");
        favorite["arrivalTime"] = arrTime.toString("yyyy-MM-dd HH:mm");

        favorite["price"] = query.value("price").toDouble();
        favorite["company"] = query.value("airline_company").toString();

        favoritesArray.append(favorite);
    }

    QJsonObject responseData;
    responseData["favorites"] = favoritesArray;
    qDebug() << "handleGetFavorites count:" << favoritesArray.size();
    sendResponse(client, MSG_GET_FAVORITES_RESPONSE, true, "获取收藏列表成功", responseData);
}

// 处理删除收藏
void Server::handleDeleteFavorite(QTcpSocket *client, const QJsonObject &data)
{
    int favoriteId = data["favoriteID"].toInt();
    if (favoriteId == 0) {
        favoriteId = data["favoriteID"].toString().toInt();
    }
    if (favoriteId <= 0) {
        sendResponse(client, MSG_DELETE_FAVORITE_RESPONSE, false, "收藏ID无效");
        return;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM favorites WHERE FavoriteID=?");
    query.addBindValue(favoriteId);

    if (query.exec() && query.numRowsAffected() > 0)
    {
        sendResponse(client, MSG_DELETE_FAVORITE_RESPONSE, true, "删除收藏成功");
    }
    else
    {
        sendResponse(client, MSG_DELETE_FAVORITE_RESPONSE, false, "删除收藏失败");
    }
}

// 处理支付请求
void Server::handlePay(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();
    double amount = data["amount"].toDouble();

    if (userID.isEmpty())
    {
        sendResponse(client, MSG_PAY_RESPONSE, false, "用户ID不能为空");
        return;
    }

    if (amount <= 0)
    {
        sendResponse(client, MSG_PAY_RESPONSE, false, "充值金额必须大于0");
        return;
    }

    QSqlQuery query(db);
    db.transaction();

    // 更新 users 表中的 Balance 字段
    query.prepare("UPDATE users SET Balance = Balance + ? WHERE UserID = ?");
    query.addBindValue(amount);
    query.addBindValue(userID.toInt());

    if (query.exec())
    {
        db.commit();

        // 获取更新后的余额
        query.prepare("SELECT Balance FROM users WHERE UserID = ?");
        query.addBindValue(userID.toInt());
        double newBalance = 0;
        if (query.exec() && query.next())
        {
            newBalance = query.value(0).toDouble();
        }

        QJsonObject responseData;
        responseData["amount"] = amount;
        responseData["balance"] = newBalance;

        qDebug() << "支付成功，用户ID:" << userID << "，充值金额:" << amount << "，新余额:" << newBalance;
        sendResponse(client, MSG_PAY_RESPONSE, true, "充值成功", responseData);
    }
    else
    {
        db.rollback();
        qDebug() << "支付失败：" << query.lastError().text();
        sendResponse(client, MSG_PAY_RESPONSE, false, "充值失败：" + query.lastError().text());
    }
}

// 处理获取余额请求
void Server::handleGetBalance(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();

    if (userID.isEmpty())
    {
        sendResponse(client, MSG_GET_BALANCE_RESPONSE, false, "用户ID不能为空");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT Balance FROM users WHERE UserID = ?");
    query.addBindValue(userID.toInt());

    if (query.exec() && query.next())
    {
        double balance = query.value(0).toDouble();
        QJsonObject responseData;
        responseData["balance"] = balance;
        sendResponse(client, MSG_GET_BALANCE_RESPONSE, true, "获取余额成功", responseData);
    }
    else
    {
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
    if (name.isEmpty() || idCard.isEmpty() || phone.isEmpty())
    {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "姓名、身份证和手机号不能为空");
        return;
    }

    if (name.length() > 50)
    {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "姓名长度不能超过50个字符");
        return;
    }

    if (idCard.length() != 18)
    {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "身份证号码必须是18位");
        return;
    }

    if (phone.length() != 11)
    {
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "手机号必须是11位");
        return;
    }

    // 检查身份证是否已存在
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT PassengerID FROM passengers WHERE UserID = ? AND IDCard = ?");
    checkQuery.addBindValue(userID.toInt());
    checkQuery.addBindValue(idCard);
    if (checkQuery.exec() && checkQuery.next())
    {
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

    if (query.exec())
    {
        QString passengerID = query.lastInsertId().toString();
        QJsonObject responseData;
        responseData["passengerID"] = passengerID;
        sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, true, "乘客添加成功", responseData);
    }
    else
    {
        QString error = query.lastError().text();
        if (error.contains("unique_user_idcard") || error.contains("UNIQUE"))
        {
            sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "该身份证号码已存在");
        }
        else
        {
            sendResponse(client, MSG_ADD_PASSENGER_RESPONSE, false, "添加失败：" + error);
        }
    }
}

// 处理获取乘客列表请求
void Server::handleGetPassengers(QTcpSocket *client, const QJsonObject &data)
{
    QString userID = data["userID"].toString();

    if (userID.isEmpty())
    {
        sendResponse(client, MSG_GET_PASSENGERS_RESPONSE, false, "用户ID不能为空");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT PassengerID, Name, IDCard, Phone FROM passengers WHERE UserID = ? ORDER BY CreatedTime DESC");
    query.addBindValue(userID.toInt());

    QJsonArray passengersArray;

    if (query.exec())
    {
        while (query.next())
        {
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

    if (passengerID.isEmpty())
    {
        sendResponse(client, MSG_DELETE_PASSENGER_RESPONSE, false, "乘客ID不能为空");
        return;
    }

    QSqlQuery query(db);
    query.prepare("DELETE FROM passengers WHERE PassengerID = ?");
    query.addBindValue(passengerID.toInt());

    if (query.exec() && query.numRowsAffected() > 0)
    {
        sendResponse(client, MSG_DELETE_PASSENGER_RESPONSE, true, "乘客删除成功");
    }
    else
    {
        sendResponse(client, MSG_DELETE_PASSENGER_RESPONSE, false, "删除失败：" + query.lastError().text());
    }
}

// 处理删除订单请求
void Server::handleDeleteOrder(QTcpSocket *client, const QJsonObject &data)
{
    int orderId = data["orderID"].toInt();
    if (orderId == 0) {
        orderId = data["orderID"].toString().toInt();
    }
    if (orderId <= 0) {
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "订单ID无效");
        return;
    }

    // 获取订单信息
    QSqlQuery orderQuery(db);
    orderQuery.prepare("SELECT TicketID, TicketCount FROM orders WHERE OrderID = ?");
    orderQuery.addBindValue(orderId);

    if (!orderQuery.exec() || !orderQuery.next())
    {
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "获取订单信息失败");
        return;
    }

    // 开始事务
    db.transaction();

    try
    {
        // 更新订单状态为已取消
        QSqlQuery updateOrderQuery(db);
        updateOrderQuery.prepare("UPDATE orders SET OrderStatus = 'Cancelled' WHERE OrderID = ?");
        updateOrderQuery.addBindValue(orderId);
        if (!updateOrderQuery.exec())
        {
            db.rollback();
            sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "删除订单失败：" + updateOrderQuery.lastError().text());
            return;
        }

        // 提交事务
        db.commit();
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, true, "订单已删除");
    }
    catch (...)
    {
        db.rollback();
        sendResponse(client, MSG_DELETE_ORDER_RESPONSE, false, "删除订单过程中发生错误");
    }
}
