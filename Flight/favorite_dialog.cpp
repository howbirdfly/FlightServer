#include "favorite_dialog.h"
#include "ui_favorite_dialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QPushButton>
#include <QHeaderView>
#include <QDateTime>
#include <QTableWidgetItem>
#include <QJsonArray>
#include <QJsonValue>
#include "networkmanager.h"
#include "protocol.h"

favorite_dialog::favorite_dialog(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::favorite_dialog)
{
    ui->setupUi(this);
}

favorite_dialog::favorite_dialog(const QString &userID, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::favorite_dialog)
    , currentUserID(userID)
{
    ui->setupUi(this);
    initTable();
    loadFavorites(); // 构造时加载数据
}

favorite_dialog::~favorite_dialog()
{
    delete ui;
}

void favorite_dialog::initTable()
{
    QStringList headers;
    headers << "类型" << "编号" << "出发地" << "目的地"
            << "出发时间" << "到达时间" << "价格（元）" << "公司" <<"收藏";
    ui->tableWidget_favorites->setHorizontalHeaderLabels(headers);
    ui->tableWidget_favorites->setColumnCount(headers.size());
    ui->tableWidget_favorites->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget_favorites->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_favorites->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_favorites->verticalHeader()->setVisible(false);
}

void favorite_dialog::loadFavorites()
{
    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "提示", "未登录用户，无法加载收藏！");
        return;
    }

    // 清空现有表格
    ui->tableWidget_favorites->setRowCount(0);

    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &favorite_dialog::onGetFavoritesResponse, Qt::UniqueConnection);
    
    QJsonObject data;
    data["userID"] = currentUserID;
    
    client->sendRequest(MSG_GET_FAVORITES, data);
}

void favorite_dialog::onGetFavoritesResponse(int msgType, bool success,
                                            const QString &message, const QJsonObject &data)
{
    if (msgType != MSG_GET_FAVORITES_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &favorite_dialog::onGetFavoritesResponse);
    
    if (!success) {
        QMessageBox::warning(this, "错误", message);
        return;
    }
    
    // 解析收藏列表
    QJsonArray favorites = data["favorites"].toArray();
    ui->tableWidget_favorites->setRowCount(0);
    
    for (const QJsonValue &value : favorites) {
        QJsonObject favorite = value.toObject();
        
        int row = ui->tableWidget_favorites->rowCount();
        ui->tableWidget_favorites->insertRow(row);
        
        QString ticketType = favorite["ticketType"].toString();
        QString typeName = ticketType == "Flight" ? "航班" : (ticketType == "Train" ? "火车" : "汽车");
        
        ui->tableWidget_favorites->setItem(row, 0, new QTableWidgetItem(typeName));
        ui->tableWidget_favorites->setItem(row, 1, new QTableWidgetItem(favorite["ticketNo"].toString()));
        ui->tableWidget_favorites->setItem(row, 2, new QTableWidgetItem(favorite["departureCity"].toString()));
        ui->tableWidget_favorites->setItem(row, 3, new QTableWidgetItem(favorite["arrivalCity"].toString()));
        ui->tableWidget_favorites->setItem(row, 4, new QTableWidgetItem(favorite["departureTime"].toString()));
        ui->tableWidget_favorites->setItem(row, 5, new QTableWidgetItem(favorite["arrivalTime"].toString()));
        ui->tableWidget_favorites->setItem(row, 6, new QTableWidgetItem(QString::number(favorite["price"].toDouble(), 'f', 2)));
        ui->tableWidget_favorites->setItem(row, 7, new QTableWidgetItem(favorite["company"].toString()));
        
        // 保存favoriteID或ticketID到第一列的userData中
        int favoriteID = favorite["favoriteID"].toInt();
        ui->tableWidget_favorites->item(row, 0)->setData(Qt::UserRole, favoriteID);
        
        // 添加移除按钮
        QPushButton *btnRemove = new QPushButton("移除");
        btnRemove->setProperty("favoriteId", favoriteID);
        connect(btnRemove, &QPushButton::clicked, this, &favorite_dialog::onRemoveFavorite);
        ui->tableWidget_favorites->setCellWidget(row, 8, btnRemove);
    }
}

void favorite_dialog::refreshFavoriteList()
{
    loadFavorites();
}

void favorite_dialog::on_btn_back_clicked()
{
    emit backRequested();
}

void favorite_dialog::on_btn_refresh_clicked()
{
    refreshFavoriteList();
}


void favorite_dialog::onRemoveFavorite()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int favoriteId = btn->property("favoriteId").toInt();

    if (currentUserID.isEmpty()) {
        QMessageBox::warning(this, "错误", "未登录用户！");
        return;
    }

    NetworkClient *client = NetworkManager::instance()->client();
    
    connect(client, &NetworkClient::responseReceived,
            this, &favorite_dialog::onDeleteFavoriteResponse, Qt::UniqueConnection);
    
    QJsonObject requestData;
    requestData["favoriteID"] = favoriteId;
    
    client->sendRequest(MSG_DELETE_FAVORITE, requestData);
}

void favorite_dialog::onDeleteFavoriteResponse(int msgType, bool success,
                                              const QString &message, const QJsonObject &data)
{
    Q_UNUSED(data);
    
    if (msgType != MSG_DELETE_FAVORITE_RESPONSE) {
        return;
    }
    
    disconnect(NetworkManager::instance()->client(),
               &NetworkClient::responseReceived,
               this, &favorite_dialog::onDeleteFavoriteResponse);
    
    if (success) {
        QMessageBox::information(this, "成功", "已从收藏夹移除！");
        refreshFavoriteList(); // 刷新列表以移除该行
    } else {
        QMessageBox::warning(this, "失败", message);
    }
}


void favorite_dialog::on_searchBtn_clicked()
{
    // 搜索功能可以通过重新加载收藏列表实现，或者服务端支持搜索接口
    // 这里暂时使用重新加载的方式
    loadFavorites();
}
