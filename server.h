#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSqlDatabase>
#include <QSqlQuery>

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);
    ~Server();

private slots:
    void newConnection();
    void clientDisconnected();
    void readClientData();

private:
    void initDatabase();
    void handleMessage(QTcpSocket *client, const QJsonObject &json);

    // 消息处理函数
    void handleLogin(QTcpSocket *client, const QJsonObject &data);
    void handleRegister(QTcpSocket *client, const QJsonObject &data);
    void handleGetUserInfo(QTcpSocket *client, const QJsonObject &data);
    void handleSearchTickets(QTcpSocket *client, const QJsonObject &data);
    void handleCreateOrder(QTcpSocket *client, const QJsonObject &data);
    void handleGetOrders(QTcpSocket *client, const QJsonObject &data);
    void handleCancelOrder(QTcpSocket *client, const QJsonObject &data);
    void handleAddFavorite(QTcpSocket *client, const QJsonObject &data);
    void handleGetFavorites(QTcpSocket *client, const QJsonObject &data);
    void handleDeleteFavorite(QTcpSocket *client, const QJsonObject &data);
    void handleUpdateUserInfo(QTcpSocket *client, const QJsonObject &data);
    // 发送响应
    void sendResponse(QTcpSocket *client, int msgType, bool success,
                      const QString &message, const QJsonObject &data = QJsonObject());

    QList<QTcpSocket*> clients;
    QSqlDatabase db;
};

#endif // SERVER_H
