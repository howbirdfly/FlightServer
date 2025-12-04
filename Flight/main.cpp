#include "MainWindow.h"
#include "networkmanager.h"
#include <QApplication>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 连接服务器
    if (!NetworkManager::instance()->connectToServer()) {
        QMessageBox::critical(nullptr, "错误", 
            "无法连接到服务器！\n请确保服务端已启动。");
        return -1;
    }
    
    qDebug() << "客户端已连接到服务器";
    
    MainWindow w;
    w.show();
    return a.exec();
}
