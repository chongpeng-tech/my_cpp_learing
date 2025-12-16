#include"user.h"
#include"message.h"
#include"server.h"
#include"crypto.h"

User::User(std::string username, std::string private_key, Server* server)
    :username(username), private_key(private_key), server(server)
{
    //初始化用户
}

//Getter函数
std::string User::get_username() const {
    return username;
}


// 发送文本消息
bool User::send_text_message(std::string text, std::string receiver) {
    //创建一个新文本消息
    TextMessage* msg = new TextMessage(text, username, receiver);

    //用写好的代码框架对私钥和用户名进行签名处理
    std::string signature = crypto::signMessage(private_key, username);

    //将消息和签名传给服务器，看是否接收

    bool success = server->create_message(msg, signature);

    return success;
}

// 发送语音消息
bool User::send_voice_message(std::string receiver) {
    VoiceMessage* msg = new VoiceMessage(username, receiver);

    std::string signature = crypto::signMessage(private_key, username);

    bool success = server->create_message(msg, signature);
    
    return success;
}