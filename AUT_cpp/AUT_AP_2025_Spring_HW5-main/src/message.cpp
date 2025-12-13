#include"message.h"
#include<ctime>
#include<cstdlib>
#include<iomanip>

Message::Message(std::string type, std::string sender, std::string receiver)
    :type(type), sender(sender), receiver(receiver) { 
        std::time_t now = std::time(nullptr);
        //获取当前系统时间
        std::tm* gmt_time = std::gmtime(&now);
        //将时间格式化
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", gmt_time);
        this->time = std::string(buffer);
}
Message::Message() :Message(" ", " ", " ") {}
//public的getter函数
std::string Message::get_type() const {return type; }
std::string Message::get_sender() const {return sender; }
std::string Message::get_receiver() const {return receiver; }
std::string Message::get_time() const {return time; }

void Message::print(std::ostream& os) const {
    os << "*****************" << std::endl;
    os << sender << " -> " << receiver << std::endl;
    os << "Message type: " << type << std::endl;
    os << "Message time: " << time << std::endl;
}

// << 运算符重载
std::ostream& operator<<(std::ostream& os, const std::string& msg) {
    msg.print(os);
    return os;
}