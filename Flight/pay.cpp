#include "pay.h"
#include "ui_pay.h"
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QJsonObject>

Pay::Pay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Pay)
{
    ui->setupUi(this);
    ui->label_alipay_img->setPixmap(QPixmap(":/pay_imag/alipay.jpg"));
    ui->label_wechat_img->setPixmap(QPixmap(":/pay_imag/wechat.jpg"));

    connect(ui->spinBox_amount, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            this, &Pay::on_amount_changed);

    ui->label_amount->setText("¥ 0.00");
}

Pay::~Pay()
{
    delete ui;
}

void Pay::setUserID(const QString &id)
{
    this->currentUserID = id;
    resetInterface(); // 每次设置用户时重置界面
}

void Pay::setFixedAmount(double amount)
{
    ui->spinBox_amount->setValue(amount);
    ui->spinBox_amount->setEnabled(false); // 订单支付时禁止修改金额
}

void Pay::on_amount_changed(double val)
{
    // 当 spinBox 数值改变时，实时更新 label_amount 文本框
    ui->label_amount->setText(QString("¥ %1").arg(QString::number(val, 'f', 2)));
}

void Pay::on_btn_confirm_clicked()
{
    double amount = ui->spinBox_amount->value();

    if (amount <= 0) {
        QMessageBox::warning(this, "提示", "请输入有效的充值金额！");
        return;
    }

    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "错误", "未获取到用户信息，无法充值！");
        return;
    }

    // 检查网络连接
    NetworkClient *client = NetworkManager::instance()->client();
    if (!client->isConnected()) {
        QMessageBox::warning(this, "错误", "未连接到服务器！");
        return;
    }

    // 连接响应信号
    connect(client, &NetworkClient::responseReceived,
            this, &Pay::onPayResponse, Qt::UniqueConnection);

    // 构造请求数据
    QJsonObject data;
    data["userID"] = currentUserID;
    data["amount"] = amount;

    // 发送支付请求
    client->sendRequest(MSG_PAY, data);
    
    qDebug() << "发送支付请求，用户ID:" << currentUserID << "，金额:" << amount;
}

void Pay::onPayResponse(int msgType, bool success,
                        const QString &message, const QJsonObject &data)
{
    // 只处理支付响应
    if (msgType != MSG_PAY_RESPONSE) {
        return;
    }

    // 断开信号连接
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &Pay::onPayResponse);

    if (success) {
        double amount = data["amount"].toDouble();
        double balance = data["balance"].toDouble();
        
        QMessageBox::information(this, "成功", 
            QString("充值成功！\n已充值: %1 元\n当前余额: %2 元")
                .arg(amount).arg(balance));

        // 发送成功信号
        emit paymentSuccess();

        // 关闭窗口
        this->close();
    } else {
        QMessageBox::critical(this, "失败", "充值失败：" + message);
    }
}

void Pay::on_btn_cancel_clicked()
{
    resetInterface();
    QMessageBox::information(this, "取消", QString("本次充值已取消"));
}

void Pay::resetInterface()
{
    // 恢复金额为 0
    ui->spinBox_amount->setEnabled(true); // 恢复可编辑
    ui->spinBox_amount->setValue(0.00);
    ui->label_amount->setText("¥ 0.00");
}
