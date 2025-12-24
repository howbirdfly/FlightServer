#include "networkclient.h"
#include <QDebug>
#include <QHostAddress>

NetworkClient::NetworkClient(QObject *parent)
    : QObject(parent)
    , socket(nullptr)
    , expectedDataSize(0)
{
    socket = new QTcpSocket(this);
    
    // 连接信号
    connect(socket, &QTcpSocket::readyRead, this, &NetworkClient::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, &NetworkClient::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &NetworkClient::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::errorOccurred),
            this, &NetworkClient::onError);
}

NetworkClient::~NetworkClient()
{
    if (socket) {
        socket->disconnectFromHost();
        socket->deleteLater();
    }
}

bool NetworkClient::connectToServer(const QString &host, quint16 port)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "已经连接到服务器";
        return true;
    }
    
    socket->connectToHost(host, port);
    return socket->waitForConnected(3000);  // 等待3秒
}

void NetworkClient::disconnectFromServer()
{
    if (socket) {
        socket->disconnectFromHost();
    }
}

bool NetworkClient::isConnected() const
{
    return socket && socket->state() == QAbstractSocket::ConnectedState;
}

void NetworkClient::sendRequest(int msgType, const QJsonObject &data)
{
    if (!socket || socket->state() != QAbstractSocket::ConnectedState) {
        emit errorOccurred("未连接到服务器");
        return;
    }
    
    // 构造请求消息
    QJsonObject request;
    request["type"] = msgType;
    request["data"] = data;
    
    // 转换为JSON
    QJsonDocument doc(request);
    QByteArray jsonData = doc.toJson(QJsonDocument::Compact);
    
    // 添加长度前缀
    QByteArray packet;
    QDataStream stream(&packet, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_5_15);
    stream << (quint32)jsonData.size();
    packet.append(jsonData);
    
    // 发送数据
    socket->write(packet);
    socket->flush();
    
    qDebug() << "发送消息类型：" << msgType << "，数据大小：" << jsonData.size() << "字节";
}

void NetworkClient::onReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_5_15);
    
    // 循环处理可能的多条消息（粘包处理）
    while (true) {
        // 如果还没有读取长度，先读取长度
        if (expectedDataSize == 0) {
            if (socket->bytesAvailable() < static_cast<qint64>(sizeof(quint32))) {
                break;  // 长度字段都不完整，等待
            }
            in >> expectedDataSize;
        }
        
        // 检查数据是否完整
        if (socket->bytesAvailable() < expectedDataSize) {
            break;  // 数据不完整，等待
        }
        
        // 读取完整的JSON数据
        QByteArray jsonData = socket->read(expectedDataSize);
        expectedDataSize = 0;  // 重置，准备读取下一条消息
        
        // 解析JSON
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(jsonData, &error);
        
        if (error.error == QJsonParseError::NoError && doc.isObject()) {
            QJsonObject obj = doc.object();
            int msgType = obj["type"].toInt();
            bool success = obj["success"].toBool();
            QString message = obj["message"].toString();
            QJsonObject data = obj["data"].toObject();
            
            // 发出响应信号
            emit responseReceived(msgType, success, message, data);
        } else {
            qDebug() << "JSON解析错误：" << error.errorString();
        }
    }
}

void NetworkClient::onConnected()
{
    qDebug() << "已连接到服务器";
    emit connectionStatusChanged(true);
}

void NetworkClient::onDisconnected()
{
    qDebug() << "与服务器断开连接";
    expectedDataSize = 0;  // 重置状态
    emit connectionStatusChanged(false);
}

void NetworkClient::onError(QAbstractSocket::SocketError error)
{
    QString errorString = "网络错误：";
    switch (error) {
        case QAbstractSocket::ConnectionRefusedError:
            errorString += "连接被拒绝";
            break;
        case QAbstractSocket::RemoteHostClosedError:
            errorString += "服务器关闭连接";
            break;
        case QAbstractSocket::HostNotFoundError:
            errorString += "找不到服务器";
            break;
        case QAbstractSocket::NetworkError:
            errorString += "网络错误";
            break;
        default:
            errorString += socket->errorString();
            break;
    }
    
    qDebug() << errorString;
    emit errorOccurred(errorString);
}

