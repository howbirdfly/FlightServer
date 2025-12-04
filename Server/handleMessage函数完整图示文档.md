# handleMessage 函数完整图示文档

## 📍 函数定义位置

**定义位置**：`server.cpp` 第 67-109 行  
**声明位置**：`server.h` 第 26 行  
**调用位置**：`server.cpp` 第 140 行（在 `readClientData()` 中）

## 🎯 函数的作用

`handleMessage` 是一个**消息分发器（Message Dispatcher）**，它的作用是：

1. 接收客户端发送的 JSON 消息
2. 根据消息中的 `type` 字段，判断消息类型
3. 将消息分发到相应的处理函数进行处理

**类比**：就像邮局的分拣员，根据地址将邮件分发到不同的邮箱。

## 📝 函数签名

```cpp
void Server::handleMessage(QTcpSocket *client, const QJsonObject &json)
```

**参数说明**：
- `QTcpSocket *client`：发送消息的客户端Socket对象
- `const QJsonObject &json`：客户端发送的JSON消息对象

## 🔍 完整代码实现

```cpp
void Server::handleMessage(QTcpSocket *client, const QJsonObject &json)
{
    // 步骤1：获取消息类型
    int msgType = json["type"].toInt();
    QJsonObject data = json["data"].toObject();

    qDebug() << "收到消息类型：" << msgType;

    // 步骤2：根据消息类型分发到不同的处理函数
    switch (msgType) {
        case MSG_LOGIN:
            handleLogin(client, data);
            break;
        case MSG_REGISTER:
            handleRegister(client, data);
            break;
        case MSG_SEARCH_TICKETS:
            handleSearchTickets(client, data);
            break;
        case MSG_CREATE_ORDER:
            handleCreateOrder(client, data);
            break;
        case MSG_GET_ORDERS:
            handleGetOrders(client, data);
            break;
        case MSG_CANCEL_ORDER:
            handleCancelOrder(client, data);
            break;
        case MSG_ADD_FAVORITE:
            handleAddFavorite(client, data);
            break;
        case MSG_GET_FAVORITES:
            handleGetFavorites(client, data);
            break;
        case MSG_DELETE_FAVORITE:
            handleDeleteFavorite(client, data);
            break;
        default:
            qDebug() << "未知的消息类型：" << msgType;
            sendResponse(client, msgType, false, "未知的消息类型");
            break;
    }
}
```

## 📊 完整工作流程图

```
客户端发送消息
    ↓
readClientData() 接收并解析JSON
    ↓
调用 handleMessage(client, json)
    ↓
提取 type 字段（如：1001）
    ↓
switch 语句判断类型
    ↓
    ├─ MSG_LOGIN (1001)      → handleLogin()
    ├─ MSG_REGISTER (1003)   → handleRegister()
    ├─ MSG_SEARCH_TICKETS    → handleSearchTickets()
    └─ ... 其他类型 ...
    ↓
相应的处理函数处理业务逻辑
    ↓
调用 sendResponse() 发送响应
```

## 🎬 实际执行示例

### 示例1：登录请求

```
1. 客户端发送：
{
    "type": 1001,
    "data": {
        "username": "zhangsan",
        "password": "123456"
    }
}

2. readClientData() 解析后调用：
   handleMessage(client, json对象)

3. handleMessage() 执行：
   - 提取 type = 1001
   - switch(1001) → case MSG_LOGIN
   - 调用 handleLogin(client, data)

4. handleLogin() 处理：
   - 验证用户名密码
   - 发送响应给客户端
```

### 示例2：查询票务

```
1. 客户端发送：
{
    "type": 2001,
    "data": {
        "from": "北京",
        "to": "上海",
        "date": "2024-01-01"
    }
}

2. handleMessage() 执行：
   - 提取 type = 2001
   - switch(2001) → case MSG_SEARCH_TICKETS
   - 调用 handleSearchTickets(client, data)

3. handleSearchTickets() 处理：
   - 查询数据库
   - 返回票务列表
```

## 📋 消息类型对照表

| 消息类型 | 值 | 处理函数 | 说明 |
|---------|-----|---------|------|
| MSG_LOGIN | 1001 | handleLogin() | 登录请求 |
| MSG_REGISTER | 1003 | handleRegister() | 注册请求 |
| MSG_SEARCH_TICKETS | 2001 | handleSearchTickets() | 查询票务 |
| MSG_CREATE_ORDER | 3001 | handleCreateOrder() | 创建订单 |
| MSG_GET_ORDERS | 3003 | handleGetOrders() | 获取订单列表 |
| MSG_CANCEL_ORDER | 3005 | handleCancelOrder() | 取消订单 |
| MSG_ADD_FAVORITE | 4001 | handleAddFavorite() | 添加收藏 |
| MSG_GET_FAVORITES | 4003 | handleGetFavorites() | 获取收藏列表 |
| MSG_DELETE_FAVORITE | 4005 | handleDeleteFavorite() | 删除收藏 |

## 🎯 为什么需要 handleMessage？

### 问题：如果没有 handleMessage

```cpp
// ❌ 不好的做法：在 readClientData() 中直接判断类型
void Server::readClientData()
{
    // ... 读取数据 ...
    
    QJsonObject json = doc.object();
    int msgType = json["type"].toInt();
    
    if (msgType == MSG_LOGIN) {
        // 处理登录
    } else if (msgType == MSG_REGISTER) {
        // 处理注册
    } else if (msgType == MSG_SEARCH_TICKETS) {
        // 处理查询
    }
    // ... 很多 if-else ...
    
    // 问题：
    // 1. readClientData() 函数会变得很长
    // 2. 业务逻辑和数据接收混在一起
    // 3. 难以维护
}
```

### 解决方案：使用 handleMessage

```cpp
// ✅ 好的做法：分离关注点
void Server::readClientData()
{
    // 只负责：读取和解析数据
    // ... 读取数据 ...
    handleMessage(client, json);  // 分发到处理函数
}

void Server::handleMessage(...)
{
    // 只负责：根据类型分发消息
    switch (msgType) {
        case MSG_LOGIN: handleLogin(...); break;
        // ...
    }
}

void Server::handleLogin(...)
{
    // 只负责：处理登录业务逻辑
    // ...
}
```

**优点**：
- ✅ 职责分离：每个函数只做一件事
- ✅ 易于维护：添加新消息类型只需添加一个case
- ✅ 代码清晰：结构清晰，易于理解

## 🔧 如何添加新的消息类型

### 步骤1：在 protocol.h 中添加类型

```cpp
enum MessageType {
    // ... 现有类型 ...
    MSG_NEW_TYPE = 5001,  // 新消息类型
};
```

### 步骤2：在 handleMessage 中添加 case

```cpp
void Server::handleMessage(QTcpSocket *client, const QJsonObject &json)
{
    // ... 现有代码 ...
    
    switch (msgType) {
        // ... 现有case ...
        case MSG_NEW_TYPE:
            handleNewType(client, data);  // 调用新的处理函数
            break;
        // ...
    }
}
```

### 步骤3：实现处理函数

```cpp
void Server::handleNewType(QTcpSocket *client, const QJsonObject &data)
{
    // 处理新类型的业务逻辑
    // ...
    sendResponse(client, MSG_NEW_TYPE_RESPONSE, true, "处理成功", responseData);
}
```

### 步骤4：在 server.h 中声明

```cpp
class Server : public QTcpServer
{
    // ...
private:
    void handleNewType(QTcpSocket *client, const QJsonObject &data);
};
```

## 💡 总结

### handleMessage 的核心作用

1. **接收**：接收客户端发送的JSON消息
2. **识别**：根据 `type` 字段识别消息类型
3. **分发**：将消息分发到对应的处理函数
4. **统一**：提供一个统一的入口，便于管理

### 设计模式

这个函数使用了**策略模式（Strategy Pattern）**的思想：
- 不同的消息类型 = 不同的策略
- 根据类型选择对应的策略（处理函数）

