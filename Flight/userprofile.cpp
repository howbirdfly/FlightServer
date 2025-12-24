#include "userprofile.h"
#include "ui_userprofile.h"
#include "sign_in.h"
#include "edit_infor.h"
#include "passenger.h"
#include "pay.h"
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QFile>
#include "networkmanager.h"
#include "protocol.h"
#include <QJsonObject>
#include <QByteArray>

UserProfile::UserProfile(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
    
    // 加载样式
    QFile qssFile(":/styles/userprofile.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();
        qDebug() << "成功加载 userprofile.qss";
    }
}


UserProfile::UserProfile(const QString &userID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserProfile)
{
    ui->setupUi(this);
    this->userID = userID;
    connect(ui->btn_back, &QPushButton::clicked, this, &UserProfile::on_btn_back_clicked);
    if (!this->userID.isEmpty()) {
        getData(this->userID);
    }
    
    // 加载样式
    QFile qssFile(":/styles/userprofile.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();
        qDebug() << "成功加载 userprofile.qss";
    }
}

UserProfile::~UserProfile()
{
    delete ui;
}

void UserProfile::on_btn_back_clicked()
{
    emit backRequested();
}

void UserProfile::on_pushButton_4_clicked()
{
    emit myOrdersRequested();
}

void UserProfile::on_pushButton_8_clicked()
{
    Sign_in *s = new Sign_in();
    s->show();
}

void UserProfile::on_pushButton_7_clicked()
{
    QMessageBox msgBox(QMessageBox::Question, "取消登录", "确定要退出登录吗？",
                       QMessageBox::Yes | QMessageBox::No, this);

    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: white;"
        "}"
        "QLabel {"
        "    color: black; "
        "}"
        "QPushButton {"
        "    min-width: 80px; "
        "   color:black;"
        "   background-color:white;"
        "   border: 1px solid black; "
        "}"
        );

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        emit logoutRequested();
    }
}

void UserProfile::on_pushButton_9_clicked()
{
    QMessageBox msgBox(QMessageBox::Question, "注销", "确定要注销吗？",
                       QMessageBox::Yes | QMessageBox::No, this);

    msgBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: white;"
        "}"
        "QLabel {"
        "    color: black; "
        "}"
        "QPushButton {"
        "    min-width: 80px;"
        "   color:black;"
        "   background-color:white; "
        "   border: 1px solid black;"
        "}"
        );

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes) {
        emit logoutRequested();
    }
}

void UserProfile::on_pushButton_10_clicked(){
    if (this->userID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    passenger *p = new passenger(this->userID);
    p->setAttribute(Qt::WA_DeleteOnClose);
    p->show();
}

void UserProfile::on_pushButton_5_clicked()
{
    edit_infor *e = new edit_infor(this->userID, ui->txt_Username->text(), this);

    connect(e, &edit_infor::change_name, this, [this](QString old, QString name){
        if (name == ""){
            ui->txt_Username->setText(old);
            this->currentUsername = name;
        } else {
            ui->txt_Username->setText(name);
            this->currentUsername = old;
        }
    });

    connect(e, &edit_infor::change_jianjie, this, [this](QString old, QString jianjie){
        if (jianjie == ""){
            ui->txt_jianjie->setText(old);
        } else {
            ui->txt_jianjie->setText(jianjie);
        }
    });

    connect(e, &edit_infor::change_avatar, this, [this](QPixmap pixmap){
        ui->label_2->setPixmap(pixmap);
    });

    connect(e, &QDialog::finished, this, [this]{
        this->show();
        if (!this->userID.isEmpty()) {
            getData(this->userID);
        }
    });
    this->hide();
    e->exec();
}

void UserProfile::getData(const QString &userID)
{
    qDebug() << "getData called with userID:" << userID;
    if (userID.isEmpty()) {
        qDebug() << "userID为空，无法获取用户信息";
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    
    // 连接响应信号
    connect(client, &NetworkClient::responseReceived,
            this, &UserProfile::onGetUserInfoResponse, Qt::UniqueConnection);
    
    // 构造请求数据
    QJsonObject data;
    data["userID"] = userID;
    
    // 发送获取用户信息请求
    client->sendRequest(MSG_GET_USER_INFO, data);
}

void UserProfile::onGetUserInfoResponse(int msgType, bool success,
                                        const QString &message, const QJsonObject &data)
{
    // 只处理获取用户信息响应
    if (msgType != MSG_GET_USER_INFO_RESPONSE) {
        return;
    }
    
    // 断开信号连接
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &UserProfile::onGetUserInfoResponse);
    
    if (success) {
        QString username = data["username"].toString();
        QString idCard = data["idCard"].toString();
        QString jianjie = data["jianjie"].toString();
        QString avatarBase64 = data["avatar"].toString();
        double balance= data["balance"].toDouble();
        
        ui->txt_Username->setText(username);
        this->currentUsername = username;
        ui->txt_UserAccount->setText(idCard);
        ui->txt_jianjie->setText(jianjie);
        ui->txt_yu->setText(QString::number(balance, 'f', 2));
        
        // 处理头像数据（从Base64解码）
        if (!avatarBase64.isEmpty()) {
            QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toLatin1());
            QPixmap pixmap;
            if (pixmap.loadFromData(avatarData)) {
                ui->label_2->setPixmap(pixmap.scaled(ui->label_2->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                ui->label_2->clear();
            }
        } else {
            ui->label_2->clear();
        }
        
        qDebug() << "用户信息加载成功：" << username;
        // 通知外部（如 Deal）头像或用户信息已更新
        emit avatarUpdated();
    } else {
        qDebug() << "获取用户信息失败：" << message;
        QMessageBox::warning(this, "错误", "获取用户信息失败：" + message);
    }
}
void UserProfile::on_btn_favorites_clicked()
{
    emit myFavoritesRequested();
}

void UserProfile::on_btn_recharge_clicked()
{
    // 充值功能：打开支付窗口
    Pay *payWindow = new Pay();
    
    // 设置用户ID
    payWindow->setUserID(this->userID);
    
    // 当支付成功时，刷新个人中心数据
    connect(payWindow, &Pay::paymentSuccess, this, [this](){
        if (!this->userID.isEmpty()) {
            this->getData(this->userID); // 刷新余额显示
        }
    });
    
    payWindow->show();
    payWindow->raise();
    payWindow->activateWindow();
}
