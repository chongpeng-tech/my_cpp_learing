#ifndef USER_H
#define USER_H

#include<string>
#include<vector>

class Server;

class User {
public:
    //构造函数
    User(std::string username, std::string private_key, Server* server);

    //Getter
    std::string get_username() const;

    //发消息
    bool send_text_message(std::string text, std::string receiver);
    bool send_voice_message(std::string receiver);

private:
    std::string username;
    std::string private_key;
    Server* const server;

};