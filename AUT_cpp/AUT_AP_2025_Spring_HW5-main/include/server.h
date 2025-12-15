#ifndef SERVER_H
#define SERVER_H

#include<vector>
#include<string>
#include<map>

#include"user.h"
#include"message.h"

class Server {
public:
    Server(); //创建一个Server似乎什么参数都不需要

    //Getter  晕晕的，以后先写private里面的内容
    std::vector<User> get_users();
    std::map<std::string, std::string> get_public_key();
    std::vector<Message*> get_messages();

    //核心功能，创建用户和创建消息
    User create_user(std::string user_name);
    bool create_message(Message* msg, std::string signature);

    //查询功能
    std::vector<Message*> get_all_messages_from(std::string user_name);
    std::vector<Message*> get_all_messages_to(std::string user_name);
    std::vector<Message*> get_chat(std::string user1, std::string user2);

    //排序
    void sort_msgs(std::vector<Message*> msgs);

private:
    std::vector<User> users;
    std::map<std::string, std::string> public_keys; //公钥
    std::vector<Message*> messages; //存储消息指针

};

#endif //SERVER_H