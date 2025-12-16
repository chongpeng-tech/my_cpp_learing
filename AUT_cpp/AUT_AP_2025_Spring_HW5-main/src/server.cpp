#include"server.h"
#include"crypto.h"
#include<stdexcept> //抛出异常
#include<algorithm>
#include<iterator>



Server::Server() {}

// 初始化后写Getter 
std::vector<User> Server::get_users() {
    return users;
}

//获取公钥映射
std::map<std::string, std::string> Server::get_public_keys() {
    return public_keys;
}

//获取所有消息
std::vector<Message*> Server::get_messages() {
    return messages;
}

//=====================
//创建用户
//=====================

User Server::create_user(std::string username) {
    for(const auto& user: users) {
        if(user.get_username() == username){
            throw std::logic_error("Username already exists");
        }
    }

    //生成RSA密钥对
    std::string public_key, private_key;
    crypto::generate_key(public_key, private_key);

    //将公钥等信息存入服务器
    public_keys[username] = public_key;

    //创建新用户
    User new_user(username, private_key, this);
    users.push_back(new_user);

    return new_user;
}

//==========================
//创建消息
//==========================

bool Server::create_message(Message* msg, std::string signature) {
    //获取sender发送人信息
    std::string sender = msg->get_sender();

    //在已经存好的map里查找有没有发送者的公钥
    auto it = public_keys.find(sender);
    if(it == public_keys.end()){
        return false;
    }

    //验证签名
    bool authentic = crypto::verifySignature(it->second, sender, signature);
    if(authentic){
        messages.push_back(msg);
        return true;
    }else{
        return false;
    }
}

// ==========================
// STL 算法实现部分
// ==========================

std::vector<Message*> Server::get_all_messages_from(std::string username) {
    std::vector<Message*> result;
    // copy_if(起点, 终点, 目标插入位置, 筛选条件)
    std::copy_if(messages.begin(), messages.end(), std::back_inserter(result),
        [&username](Message* m) { // Lambda捕获username
            return m->get_sender() == username;
        });
    return result;
}

std::vector<Message*> Server::get_all_messages_to(std::string username) {
    std::vector<Message*> result;
    std::copy_if(messages.begin(), messages.end(), std::back_inserter(result),
        [&username](Message* m) {
            return m->get_receiver() == username;
        });
    return result;
}

std::vector<Message*> Server::get_chat(std::string user1, std::string user2) {
    std::vector<Message*> result;
    std::copy_if(messages.begin(), messages.end(), std::back_inserter(result),
        [&user1, &user2](Message* m) {
            // 逻辑：(发送者是u1且接收者是u2) 或者 (发送者是u2且接收者是u1)
            return (m->get_sender() == user1 && m->get_receiver() == user2) ||
                   (m->get_sender() == user2 && m->get_receiver() == user1);
        });
    return result;
}

void Server::sort_msgs(std::vector<Message*> msgs) {
    // sort(起点, 终点, 比较规则)
    std::sort(msgs.begin(), msgs.end(),
        [](Message* m1, Message* m2) {
            // 按时间字符串比较（虽然字符串比较不是最完美的日期比较，但作业中通常只能这样）
            return m1->get_time() < m2->get_time();
        });
}
