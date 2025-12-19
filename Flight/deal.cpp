#include "deal.h"
#include "ui_deal.h"
#include "single_center.h"
#include "order_dialog.h"
#include "userprofile.h"
#include <QMessageBox>
#include <QDebug>
#include <QDate>
#include <QPushButton>
#include <QHeaderView>
#include <QDateTime>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QIntValidator>
#include <QLineEdit>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QSize>
#include "mainwindow.h"
#include "userprofile.h"
#include "networkmanager.h"
#include "protocol.h"
Deal::Deal(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Deal)
{
    ui->setupUi(this);
    currentUserID = "";
    initTable();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    ui->stackedWidget->setCurrentWidget(ui->page_tickets);
    
    // 加载样式
    QFile qssFile(":/styles/Dealstyle.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();
        qDebug() << "成功加载 Dealstyle.qss";
    }

    // 初始化分页（如果 UI 中有相关控件则启用）
    initPagination();
}

Deal::Deal(const QString &userID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Deal)
{
    ui->setupUi(this);
    currentUserID = userID;
    initTable();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit->setMinimumDate(QDate::currentDate());
    // 移除自动搜索，等待用户手动输入后点击搜索按钮

    m_personalCenterPage = new Single_Center(currentUserID, this);
    ui->stackedWidget->addWidget(m_personalCenterPage);
    connect(m_personalCenterPage, &Single_Center::backRequested, this, &Deal::showTicketSearchPage);

    m_userProfilePage = new UserProfile(userID,this);
    ui->stackedWidget->addWidget(m_userProfilePage);
    connect(m_userProfilePage, &UserProfile::backRequested, this, &Deal::showTicketSearchPage);

    // 创建收藏夹页面对象
    m_favoriteDialogPage = new favorite_dialog(currentUserID, this);

    // 将其添加到 stackedWidget (页面栈) 中
    ui->stackedWidget->addWidget(m_favoriteDialogPage);

    // 连接信号：从收藏夹点击"返回"时，回到票务搜索页
    connect(m_favoriteDialogPage, &favorite_dialog::backRequested, this, &Deal::showTicketSearchPage);

    //连接信号：从个人中心点击"我的收藏"时，跳转到收藏夹
    connect(m_userProfilePage, &UserProfile::myFavoritesRequested, this, [=](){
        m_favoriteDialogPage->refreshFavoriteList();
        ui->stackedWidget->setCurrentWidget(m_favoriteDialogPage);
    });

    connect(m_userProfilePage, &UserProfile::myOrdersRequested, this, [=](){
        m_personalCenterPage->refreshOrderList();
        ui->stackedWidget->setCurrentWidget(m_personalCenterPage);
    });


    connect(m_userProfilePage, &UserProfile::logoutRequested, this, [=](){
        MainWindow *loginWindow = new MainWindow();
        loginWindow->show();
        this->close();
    });
    // 头像更新后，刷新右上角圆形头像
    connect(m_userProfilePage, &UserProfile::avatarUpdated, this, [=](){
        if (!currentUserID.isEmpty()) {
            getData(currentUserID);
        }
    });

    ui->stackedWidget->setCurrentWidget(ui->page_tickets);
    
    // 加载样式
    QFile qssFile(":/styles/Dealstyle.qss");
    if (qssFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(qssFile.readAll());
        this->setStyleSheet(styleSheet);
        qssFile.close();
        qDebug() << "成功加载 Dealstyle.qss";
    }

    // 初始化分页（如果 UI 中有相关控件则启用）
    initPagination();

    // 初始化头像（如果已登录）
    if (!currentUserID.isEmpty()) {
        getData(currentUserID);
    }
}

Deal::~Deal()
{
    delete ui;
}

void Deal::initTable()
{
    QStringList headers;
    headers << "类型" << "编号" << "出发地" << "目的地" << "出发时间"
            << "到达时间" << "价格(元)" << "可用座位" << "公司" << "操作"<<"收藏";
    ui->tableWidget_tickets->setHorizontalHeaderLabels(headers);
    ui->tableWidget_tickets->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_tickets->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_tickets->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_tickets->verticalHeader()->setVisible(false);
}

// 绘制 40x40 的圆形头像到 Avatar 按钮
void Deal::setCircularAvatar(const QByteArray &avatarData)
{
    if (!ui->Avatar) return;

    QPixmap pixmap;
    if (!avatarData.isEmpty() && pixmap.loadFromData(avatarData)) {
        QPixmap circularPixmap(40, 40);
        circularPixmap.fill(Qt::transparent);

        QPainter painter(&circularPixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);

        QPainterPath path;
        path.addEllipse(0, 0, 40, 40);
        painter.setClipPath(path);

        QPixmap scaled = pixmap.scaled(40, 40, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        painter.drawPixmap(0, 0, scaled);

        painter.setPen(QPen(QColor(255, 255, 255, 153), 1));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(0, 0, 39, 39);

        ui->Avatar->setIcon(QIcon(circularPixmap));
        ui->Avatar->setIconSize(QSize(40, 40));
    }
}

// 通过网络从服务端获取头像信息
void Deal::getData(const QString &userID)
{
    qDebug() << "Deal::getData called with userID:" << userID;
    if (userID.isEmpty()) return;

    NetworkClient *client = NetworkManager::instance()->client();

    // 连接响应信号（专用于头像）
    connect(client, &NetworkClient::responseReceived,
            this, &Deal::onGetUserInfoForAvatar, Qt::UniqueConnection);

    QJsonObject data;
    data["userID"] = userID;

    client->sendRequest(MSG_GET_USER_INFO, data);
}

void Deal::searchTickets()
{
    QString from = ui->lineEdit_from->text().trimmed();
    QString to = ui->lineEdit_to->text().trimmed();
    QDate date = ui->dateEdit->date();
    QString type = ui->comboBox_type->currentText();

    if (from.isEmpty() || to.isEmpty()) {
        QMessageBox::warning(this, "提示", "请填写出发地和目的地！");
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    
    // 连接响应信号
    connect(client, &NetworkClient::responseReceived,
            this, &Deal::onSearchResponse, Qt::UniqueConnection);
    
    // 构造请求数据
    QJsonObject data;
    data["from"] = from;
    data["to"] = to;
    data["date"] = date.toString("yyyy-MM-dd");
    data["type"] = type;
    if (!currentUserID.isEmpty()) {
        data["userID"] = currentUserID;  // 用于服务端返回收藏状态
    }
    // 分页参数（与 Management 的 PAGE_SIZE 一致）
    data["page"] = currentPage;
    data["pageSize"] = 50;
    
    // 发送查询请求
    client->sendRequest(MSG_SEARCH_TICKETS, data);
    
    // 清空表格，准备显示新结果
    ui->tableWidget_tickets->setRowCount(0);
}

void Deal::onSearchResponse(int msgType, bool success,
                            const QString &message, const QJsonObject &data)
{
    if (msgType != MSG_SEARCH_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &Deal::onSearchResponse);
    
    if (!success) {
        QMessageBox::warning(this, "错误", message);
        return;
    }
    
    // 解析分页信息（如果有）
    if (data.contains("totalPage")) {
        totalPage = data["totalPage"].toInt();
    }
    if (data.contains("currentPage")) {
        currentPage = data["currentPage"].toInt();
    }
    
    // 解析票务列表
    QJsonArray tickets = data["tickets"].toArray();
    QJsonArray favorites = data["favorites"].toArray();  // 收藏的票务ID列表
    
    // 将收藏列表转换为QList
    QList<int> favoriteTicketIds;
    for (const QJsonValue &value : favorites) {
        favoriteTicketIds.append(value.toInt());
    }
    
    ui->tableWidget_tickets->setRowCount(0);
    
    for (const QJsonValue &value : tickets) {
        QJsonObject ticket = value.toObject();
        
        int row = ui->tableWidget_tickets->rowCount();
        ui->tableWidget_tickets->insertRow(row);
        
        int ticketId = ticket["ticketID"].toInt();
        QString ticketType = ticket["ticketType"].toString();
        QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");
        
        ui->tableWidget_tickets->setItem(row, 0, new QTableWidgetItem(typeName));
        ui->tableWidget_tickets->setItem(row, 1, new QTableWidgetItem(ticket["ticketNo"].toString()));
        ui->tableWidget_tickets->setItem(row, 2, new QTableWidgetItem(ticket["departureCity"].toString()));
        ui->tableWidget_tickets->setItem(row, 3, new QTableWidgetItem(ticket["arrivalCity"].toString()));
        
        QString depTimeStr = ticket["departureTime"].toString();
        QString arrTimeStr = ticket["arrivalTime"].toString();
        ui->tableWidget_tickets->setItem(row, 4, new QTableWidgetItem(depTimeStr));
        ui->tableWidget_tickets->setItem(row, 5, new QTableWidgetItem(arrTimeStr));
        
        ui->tableWidget_tickets->setItem(row, 6, new QTableWidgetItem(QString::number(ticket["price"].toDouble(), 'f', 2)));
        ui->tableWidget_tickets->setItem(row, 7, new QTableWidgetItem(ticket["availableSeats"].toString()));
        ui->tableWidget_tickets->setItem(row, 8, new QTableWidgetItem(ticket["company"].toString()));
        
        // 保存ticketID到第一列的userData中
        ui->tableWidget_tickets->item(row, 0)->setData(Qt::UserRole, ticketId);
        
        QPushButton *btnBook = new QPushButton("订票");
        btnBook->setProperty("ticketId", ticketId);
        connect(btnBook, &QPushButton::clicked, this, &Deal::onBookTicket);
        ui->tableWidget_tickets->setCellWidget(row, 9, btnBook);
        
        bool isFavorited = favoriteTicketIds.contains(ticketId);
        QPushButton *btnFav = new QPushButton(isFavorited ? "已收藏" : "收藏");
        btnFav->setProperty("ticketId", ticketId);
        
        if (isFavorited) {
            btnFav->setEnabled(false);
        }
        connect(btnFav, &QPushButton::clicked, this, &Deal::onAddFavorite);
        ui->tableWidget_tickets->setCellWidget(row, 10, btnFav);
    }
    
    if (tickets.isEmpty()) {
        QMessageBox::information(this, "提示", "未找到符合条件的票务");
    }

    // 更新分页显示
    updatePageContainerText();
}

void Deal::on_btn_search_clicked()
{
    searchTickets();
}


void Deal::onBookTicket()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }

    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int ticketId = btn->property("ticketId").toInt();
    
    // 获取当前用户ID
    //QSqlQuery query;
    //query.prepare("SELECT UserID FROM users WHERE Username = ?");
    //query.addBindValue(currentUserID);
    //if (!query.exec() || !query.next()) {
    //    QMessageBox::warning(this, "错误", "获取用户信息失败！");
    //    return;
    //}
    int userId = currentUserID.toInt();

    // 打开订单对话框
    OrderDialog *dialog = new OrderDialog(ticketId, userId, this);
    if (dialog->exec() == QDialog::Accepted) {
        refreshTicketList();
        QMessageBox::information(this, "成功", "订票成功！");
    }
    delete dialog;
}

void Deal::refreshTicketList()
{
    searchTickets();
}

void Deal::on_Single_Center_clicked()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    m_userProfilePage->getData(currentUserID);
    ui->stackedWidget->setCurrentWidget(m_userProfilePage);
    // Single_Center *center = new Single_Center(currentUsername, this);
    // center->setAttribute(Qt::WA_DeleteOnClose);
    // center->show();
}

void Deal::on_Deal_2_clicked()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    m_personalCenterPage->refreshOrderList();
    ui->stackedWidget->setCurrentWidget(m_personalCenterPage);

}
void Deal::showTicketSearchPage()
{
    // 只切换页面，不自动搜索（避免在输入框为空时弹出提示）
    ui->stackedWidget->setCurrentWidget(ui->page_tickets);
}
void Deal::onAddFavorite()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }
    
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    int ticketId = btn->property("ticketId").toInt();
    
    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &Deal::onAddFavoriteResponse, Qt::UniqueConnection);
    
    QJsonObject data;
    data["userID"] = currentUserID;
    data["ticketID"] = ticketId;
    
    client->sendRequest(MSG_ADD_FAVORITE, data);
}

void Deal::onAddFavoriteResponse(int msgType, bool success,
                                 const QString &message, const QJsonObject &data)
{
    Q_UNUSED(data);
    
    if (msgType != MSG_ADD_FAVORITE_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &Deal::onAddFavoriteResponse);
    
    if (success) {
        QMessageBox::information(this, "成功", "已添加到收藏夹！");
        // 找到对应的按钮并更新状态
        QPushButton *btn = qobject_cast<QPushButton*>(sender());
        if (btn) {
            btn->setEnabled(false);
            btn->setText("已收藏");
        }
    } else {
        QMessageBox::warning(this, "失败", message);
    }
}

void Deal::on_favorite_button_clicked()
{
    // 1. 检查是否登录
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先登录！");
        return;
    }

    // 2. 刷新收藏列表数据 (确保显示最新数据)
    m_favoriteDialogPage->refreshFavoriteList();

    // 3. 切换界面显示到收藏夹页面
    ui->stackedWidget->setCurrentWidget(m_favoriteDialogPage);
}

// 头像信息响应处理
void Deal::onGetUserInfoForAvatar(int msgType, bool success,
                                  const QString &message, const QJsonObject &data)
{
    Q_UNUSED(message);

    if (msgType != MSG_GET_USER_INFO_RESPONSE) {
        return;
    }

    // 断开与头像相关的连接
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &Deal::onGetUserInfoForAvatar);

    if (!success) {
        qDebug() << "获取用户头像失败：" << message;
        return;
    }

    QString avatarBase64 = data["avatar"].toString();
    if (!avatarBase64.isEmpty()) {
        QByteArray avatarData = QByteArray::fromBase64(avatarBase64.toLatin1());
        setCircularAvatar(avatarData);
    }
}

void Deal::on_lineEdit_pageNum_returnPressed()
{
    // 若 UI 中没有分页控件，直接返回
    if (!ui->lineEdit_pageNum || !ui->label_pageInfo) {
        return;
    }

    if (totalPage == 0) {
        QMessageBox::warning(this, "提示", "暂无数据，无法跳转！");
        ui->lineEdit_pageNum->setText("");
        return;
    }

    QString inputText = ui->lineEdit_pageNum->text().trimmed();
    if (inputText.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入有效页码！");
        ui->lineEdit_pageNum->setText(QString::number(currentPage));
        return;
    }

    bool isNumber = false;
    int targetPage = inputText.toInt(&isNumber);
    if (!isNumber) {
        QMessageBox::warning(this, "提示", "页码必须是正整数！");
        ui->lineEdit_pageNum->setText(QString::number(currentPage));
        return;
    }

    if (targetPage < 1) {
        targetPage = 1;
    } else if (targetPage > totalPage) {
        targetPage = totalPage;
    }

    currentPage = targetPage;
    searchTickets();
}

void Deal::updatePageContainerText()
{
    // UI 中没有这些控件时直接忽略
    if (!ui->label_pageInfo || !ui->lineEdit_pageNum) {
        return;
    }

    if (totalPage <= 0) {
        ui->label_pageInfo->setText("  页 / 共 0 页");
        ui->lineEdit_pageNum->setEnabled(false);
        ui->lineEdit_pageNum->setText("");
        if (ui->btn_prev) ui->btn_prev->setEnabled(false);
        if (ui->btn_next) ui->btn_next->setEnabled(false);
        return;
    }

    QString pageText = QString("  页 / 共 %1 页").arg(totalPage);
    ui->label_pageInfo->setText(pageText);
    ui->lineEdit_pageNum->setEnabled(true);
    ui->lineEdit_pageNum->setText(QString::number(currentPage));

    if (ui->btn_prev) ui->btn_prev->setEnabled(currentPage > 1);
    if (ui->btn_next) ui->btn_next->setEnabled(currentPage < totalPage);
}

void Deal::on_home_clicked(){
    this->showTicketSearchPage();
}

// 初始化分页控件和信号（如果 UI 中存在这些控件）
void Deal::initPagination()
{
    // 兼容没有分页控件的 UI：如果任何一个为 nullptr，直接返回
    if (!ui->btn_prev || !ui->btn_next || !ui->lineEdit_pageNum || !ui->label_pageInfo) {
        return;
    }

    ui->lineEdit_pageNum->setAlignment(Qt::AlignCenter);

    QIntValidator *validator = new QIntValidator(1, 999, this);
    ui->lineEdit_pageNum->setValidator(validator);

    // 上一页
    connect(ui->btn_prev, &QPushButton::clicked, this, [=](){
        if (currentPage > 1) {
            currentPage--;
            searchTickets();
        }
    });

    // 下一页
    connect(ui->btn_next, &QPushButton::clicked, this, [=](){
        if (currentPage < totalPage) {
            currentPage++;
            searchTickets();
        }
    });

    // 页码回车跳转
    connect(ui->lineEdit_pageNum, &QLineEdit::returnPressed,
            this, &Deal::on_lineEdit_pageNum_returnPressed);

    updatePageContainerText();
}
