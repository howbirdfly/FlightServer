#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include <QTcpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QDataStream>

class NetworkClient : public QObject
{
    Q_OBJECT

public:
    explicit NetworkClient(QObject *parent = nullptr);
    ~NetworkClient();
    
    // 连接和断开
    bool connectToServer(const QString &host = "127.0.0.1", quint16 port = 8080);
    void disconnectFromServer();
    bool isConnected() const;
    
    // 发送请求
    void sendRequest(int msgType, const QJsonObject &data);

signals:
    // 响应信号
    void responseReceived(int msgType, bool success, const QString &message, const QJsonObject &data);
    
    // 连接状态信号
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &error);

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError error);

private:
    QTcpSocket *socket;
    quint32 expectedDataSize;  // 期望接收的数据大小
};

#endif // NETWORKCLIENT_H

