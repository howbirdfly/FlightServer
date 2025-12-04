#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include "sign_in.h"
#include "deal.h"
#include "userprofile.h"
#include "networkmanager.h"
#include "protocol.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_log_in_clicked()
{
    QString username = ui->Usernamet->text().trimmed();
    QString password = ui->Passwordt->text().trimmed();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
        return;
    }
    
    NetworkClient *client = NetworkManager::instance()->client();
    
    // 连接响应信号（使用Qt::UniqueConnection避免重复连接）
    connect(client, &NetworkClient::responseReceived,
            this, &MainWindow::onLoginResponse, Qt::UniqueConnection);
    
    // 构造请求数据
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    
    // 发送登录请求
    client->sendRequest(MSG_LOGIN, data);
}

void MainWindow::onLoginResponse(int msgType, bool success,
                                  const QString &message, const QJsonObject &data)
{
    // 只处理登录响应
    if (msgType != MSG_LOGIN_RESPONSE) {
        return;
    }
    
    // 断开信号连接（避免重复处理）
    disconnect(NetworkManager::instance()->client(), 
               &NetworkClient::responseReceived,
               this, &MainWindow::onLoginResponse);
    
    if (success) {
        QString userID = data["userID"].toString();
        qDebug() << "收到登录响应，userID:" << userID;
        
        if (userID.isEmpty()) {
            QMessageBox::warning(this, "错误", "登录成功但未获取到用户ID，请重试！");
            return;
        }
        
        QMessageBox::information(this, "成功", "登录成功！");
        
        // 打开主窗口
        Deal *d = new Deal(userID);
        d->setAttribute(Qt::WA_DeleteOnClose);
        d->show();
        this->close();
    } else {
        QMessageBox::warning(this, "失败", message);
    }
}
void MainWindow::on_sign_in_clicked()
{
    Sign_in *s=new Sign_in();
    s->setAttribute(Qt::WA_DeleteOnClose);
    s->show();
}

