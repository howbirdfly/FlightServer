#include "userprofile.h"
#include "ui_userprofile.h"
#include "sign_in.h"
#include "edit_infor.h"
#include "passenger.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QPixmap>
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
    passenger*s=new passenger(currentUsername);
    s->show();
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
        
        ui->txt_Username->setText(username);
        this->currentUsername = username;
        ui->txt_UserAccount->setText(idCard);
        ui->txt_jianjie->setText(jianjie);
        
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
    } else {
        qDebug() << "获取用户信息失败：" << message;
        QMessageBox::warning(this, "错误", "获取用户信息失败：" + message);
    }
}
void UserProfile::on_btn_favorites_clicked()
{
    emit myFavoritesRequested();
}