#ifndef PROTOCOL_H
#define PROTOCOL_H
enum MessageType {
    // 用户相关
    MSG_LOGIN = 1001,           // 登录请求
    MSG_LOGIN_RESPONSE = 1002,  // 登录响应
    MSG_REGISTER = 1003,         // 注册请求
    MSG_REGISTER_RESPONSE = 1004,// 注册响应
    MSG_GET_USER_INFO = 1005,   // 获取用户信息请求
    MSG_GET_USER_INFO_RESPONSE = 1006, // 获取用户信息响应
    MSG_UPDATE_USER_INFO = 1007, // 更新用户信息请求
    MSG_UPDATE_USER_INFO_RESPONSE = 1008, // 更新用户信息响应
    // 票务查询
    MSG_SEARCH_TICKETS = 2001,  // 查询票务
    MSG_SEARCH_RESPONSE = 2002, // 查询响应

    // 订单相关
    MSG_CREATE_ORDER = 3001,    // 创建订单
    MSG_CREATE_ORDER_RESPONSE = 3002, // 创建订单响应
    MSG_GET_ORDERS = 3003,      // 获取订单列表
    MSG_GET_ORDERS_RESPONSE = 3004, // 订单列表响应
    MSG_CANCEL_ORDER = 3005,    // 取消订单
    MSG_CANCEL_ORDER_RESPONSE = 3006, // 取消订单响应

    // 收藏相关
    MSG_ADD_FAVORITE = 4001,    // 添加收藏
    MSG_ADD_FAVORITE_RESPONSE = 4002,
    MSG_GET_FAVORITES = 4003,   // 获取收藏列表
    MSG_GET_FAVORITES_RESPONSE = 4004,
    MSG_DELETE_FAVORITE = 4005, // 删除收藏
    MSG_DELETE_FAVORITE_RESPONSE = 4006, // 删除收藏响应

    // 支付相关
    MSG_PAY = 5001,             // 支付请求
    MSG_PAY_RESPONSE = 5002     // 支付响应
};

#endif // PROTOCOL_H
