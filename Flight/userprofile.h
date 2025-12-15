#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>

namespace Ui {
class UserProfile;
}

class UserProfile : public QWidget
{
    Q_OBJECT

public:
    QString userID;
    QString username;
    explicit UserProfile(QWidget *parent = nullptr);
    // 修复：修改构造函数参数，去掉多余的 username 参数，匹配 Deal::Deal 中的调用
    explicit UserProfile(const QString &userID, QWidget *parent = nullptr);
    ~UserProfile();

public slots:
    void getData(const QString &userID);

signals:
    void backRequested();
    void myOrdersRequested();
    void logoutRequested();
    void myFavoritesRequested();

private slots:
    void on_btn_back_clicked();
    void on_pushButton_4_clicked(); // 我的订单
    void on_pushButton_8_clicked(); // 注册
    void on_pushButton_7_clicked(); // 登录
    void on_pushButton_9_clicked(); // 注销
    void on_pushButton_10_clicked();//增加乘客
    void on_pushButton_5_clicked();//编辑个人资料
    void on_btn_favorites_clicked();//收藏
    void on_btn_recharge_clicked();//充值
    void onGetUserInfoResponse(int msgType, bool success, const QString &message, const QJsonObject &data);

private:
    Ui::UserProfile *ui;
    QString currentUsername;
};

#endif // USERPROFILE_H