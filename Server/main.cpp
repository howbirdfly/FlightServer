#include "server.h"
#include <QCoreApplication>
#include <QDebug>
#include <QHostAddress>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    if (!server.listen(QHostAddress::Any, 8888)) {
        qDebug() << "服务端启动失败：" << server.errorString();
        return -1;
    }

    qDebug() << "========================================";
    qDebug() << "服务端已启动，监听端口：8888";
    qDebug() << "等待客户端连接...";
    qDebug() << "========================================";

    return a.exec();
}
