#include "sign_in.h"
#include "ui_sign_in.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include "networkmanager.h"
#include "protocol.h"

Sign_in::Sign_in(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Sign_in)
{
    ui->setupUi(this);
    
    // 加载样式（使用与登录页面相同的样式）
    QFile qssFile(":/styles/style.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();
        qDebug() << "成功加载 style.qss";
    }
}

Sign_in::~Sign_in()
{
    delete ui;
}

void Sign_in::on_Sign_in_Button_clicked()
{
    QString username = ui->Sign_in_UsernameT->text().trimmed();
    QString password = ui->Sign_in_PassWordT->text().trimmed();
    QString passwordA = ui->Sign_in_PassWordAT->text().trimmed();
    QString ID = ui->ID->text().trimmed();
    
    // 输入验证
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "提示", "用户名或密码不能为空！");
        return;
    }
    if (passwordA.isEmpty()) {
        QMessageBox::warning(this, "提示", "请确认密码");
        return;
    }
    if (passwordA != password) {
        QMessageBox::warning(this, "提示", "请确认两次密码是否一致");
        return;
    }
    if (ID.isEmpty()) {
        QMessageBox::warning(this, "提示", "ID不能为空！");
        return;
    }
    
    NetworkClient *client = NetworkManager::instance()->client();
    
    // 连接响应信号
    connect(client, &NetworkClient::responseReceived,
            this, &Sign_in::onRegisterResponse, Qt::UniqueConnection);
    
    // 构造请求数据
    QJsonObject data;
    data["username"] = username;
    data["password"] = password;
    data["idCard"] = ID;
    
    // 发送注册请求
    client->sendRequest(MSG_REGISTER, data);
}

void Sign_in::onRegisterResponse(int msgType, bool success,
                                  const QString &message, const QJsonObject &data)
{
    Q_UNUSED(data);
    
    if (msgType != MSG_REGISTER_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &Sign_in::onRegisterResponse);
    
    if (success) {
        QMessageBox::information(this, "成功", "注册成功！");
        this->close();  // 关闭注册窗口
    } else {
        QMessageBox::warning(this, "失败", message);
    }
}


void Sign_in::on_Sign_in_Cencel_clicked()
{
    this->close();
}
