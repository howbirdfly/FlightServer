#include "edit_infor.h"
#include "ui_edit_infor.h"
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <QBuffer>
#include <QPixmap>
#include <QIODevice>
#include "networkmanager.h"
#include "protocol.h"
#include <QJsonObject>
#include <QByteArray>
#include "networkmanager.h"
#include "protocol.h"
#include <QJsonObject>
#include <QByteArray>
edit_infor::edit_infor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::edit_infor)
{
    ui->setupUi(this);
}

edit_infor::edit_infor(QString userID, QString username, QWidget *parent)
    : QDialog(parent)
    , userID(userID)
    , username(username)
    , avatarChanged(false)
    , ui(new Ui::edit_infor)
{
    ui->setupUi(this);


    ui->old_name->setText(username);

    qDebug() << "edit_infor 初始化 - UserID:" << userID << " 传入的Username:" << username;

    // 通过网络请求获取用户信息
    NetworkClient *client = NetworkManager::instance()->client();
    
    // 连接响应信号
    connect(client, &NetworkClient::responseReceived,
            this, &edit_infor::onGetUserInfoResponse, Qt::UniqueConnection);
    
    // 构造请求数据
    QJsonObject data;
    data["userID"] = userID;
    
    // 发送获取用户信息请求
    client->sendRequest(MSG_GET_USER_INFO, data);
}

edit_infor::~edit_infor()
{
    delete ui;
}

void edit_infor::on_pushButton_clicked()
{
    // 打开文件对话框选择图片
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择头像"), QString(), tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (filePath.isEmpty()) {
        return;
    }

    QPixmap image(filePath);
    if (image.isNull()) {
        QMessageBox::warning(this, tr("无效图片"), tr("无法加载所选文件。"));
        return;
    }

    // 缩放图片，避免数据库存储过大的原始图片 (例如限制为 300x300)
    QPixmap scaledPixmap = image.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 更新预览和成员变量
    ui->label_5->setPixmap(scaledPixmap.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    this->Avatar = scaledPixmap;
    this->avatarChanged = true;
}


void edit_infor::accept()
{
    QString newUsername = ui->new_name->text().trimmed();
    QString newJianjie = ui->new_jianjie->text().trimmed();

    // 检查是否有更改
    bool hasChanged = false;
    if (!newUsername.isEmpty() && newUsername != this->username) {
        hasChanged = true;
    }
    if (newJianjie != this->jianjie) {
        hasChanged = true;
    }
    if (this->avatarChanged && !this->Avatar.isNull()) {
        hasChanged = true;
    }

    if (!hasChanged) {
        QDialog::accept();
        return;
    }

    // 准备头像数据（转换为Base64）
    QString avatarBase64;
    if (this->avatarChanged && !this->Avatar.isNull()) {
        QByteArray avatarData;
        QBuffer buffer(&avatarData);
        if (buffer.open(QIODevice::WriteOnly)) {
            this->Avatar.save(&buffer, "PNG");
            if (!avatarData.isEmpty()) {
                avatarBase64 = QString::fromLatin1(avatarData.toBase64());
            }
        }
    }

    // 通过网络请求更新用户信息
    NetworkClient *client = NetworkManager::instance()->client();
    
    // 连接响应信号
    connect(client, &NetworkClient::responseReceived,
            this, &edit_infor::onUpdateUserInfoResponse, Qt::UniqueConnection);
    
    // 构造请求数据
    QJsonObject data;
    data["userID"] = this->userID;
    
    // 只发送有更改的字段
    if (!newUsername.isEmpty() && newUsername != this->username) {
        data["username"] = newUsername;
    }
    if (newJianjie != this->jianjie) {
        data["jianjie"] = newJianjie;
    }
    if (!avatarBase64.isEmpty()) {
        data["avatar"] = avatarBase64;
    }
    
    // 发送更新用户信息请求
    client->sendRequest(MSG_UPDATE_USER_INFO, data);
}

void edit_infor::onGetUserInfoResponse(int msgType, bool success,
                                      const QString &message, const QJsonObject &data)
{
    // 只处理获取用户信息响应
    if (msgType != MSG_GET_USER_INFO_RESPONSE) {
        return;
    }
    
    // 断开信号连接
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &edit_infor::onGetUserInfoResponse);
    
    if (success) {
        QString dbUsername = data["username"].toString();
        if (!dbUsername.isEmpty()) {
            ui->old_name->setText(dbUsername);
            this->username = dbUsername;
        }
        this->jianjie = data["jianjie"].toString();
        ui->new_jianjie->setText(this->jianjie);
        
        // 处理头像数据（从Base64解码）
        QString avatarBase64 = data["avatar"].toString();
        if (!avatarBase64.isEmpty()) {
            QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toLatin1());
            QPixmap pixmap;
            if (pixmap.loadFromData(avatarData)) {
                this->Avatar = pixmap;
                ui->label_5->setPixmap(pixmap.scaled(ui->label_5->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            } else {
                ui->label_5->setText("暂无头像");
            }
        } else {
            ui->label_5->setText("暂无头像");
        }
        
        qDebug() << "获取用户信息成功";
    } else {
        qDebug() << "获取用户信息失败：" << message;
        QMessageBox::warning(this, "错误", "获取用户信息失败：" + message);
    }
}

void edit_infor::onUpdateUserInfoResponse(int msgType, bool success,
                                         const QString &message, const QJsonObject &data)
{
    Q_UNUSED(data); // 参数未使用，消除警告
    
    // 只处理更新用户信息响应
    if (msgType != MSG_UPDATE_USER_INFO_RESPONSE) {
        return;
    }
    
    // 断开信号连接
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &edit_infor::onUpdateUserInfoResponse);
    
    if (success) {
        QString newUsername = ui->new_name->text().trimmed();
        QString newJianjie = ui->new_jianjie->text().trimmed();
        
        // 发送信号更新界面
        if (!newUsername.isEmpty() && newUsername != this->username) {
            emit change_name(this->username, newUsername);
            this->username = newUsername;  // 更新当前用户名
        }
        if (newJianjie != this->jianjie) {
            emit change_jianjie(this->jianjie, newJianjie);
            this->jianjie = newJianjie;  // 更新当前简介
        }
        if (this->avatarChanged && !this->Avatar.isNull()) {
            emit change_avatar(this->Avatar);
            this->avatarChanged = false;  // 重置标志
        }
        
        QMessageBox::information(this, "成功", "用户信息修改成功！");
        QDialog::accept();
    } else {
        qDebug() << "更新用户信息失败：" << message;
        QMessageBox::warning(this, "错误", "更新用户信息失败：" + message);
    }
}
