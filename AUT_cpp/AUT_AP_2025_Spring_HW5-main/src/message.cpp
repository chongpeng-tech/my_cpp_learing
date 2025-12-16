#include "message.h"
#include <ctime>
#include <cstdlib>
#include <iomanip>

Message::Message(std::string type, std::string sender, std::string receiver)
    :type(type), sender(sender), receiver(receiver) { 
        std::time_t now = std::time(nullptr);
        std::tm* gmt_time = std::gmtime(&now);
        char buffer[80];
        std::strftime(buffer, sizeof(buffer), "%a %b %d %H:%M:%S %Y", gmt_time);
        this->time = std::string(buffer);
}
Message::Message() :Message("", "", "") {} // 建议初始化为空字符串而不是空格

std::string Message::get_type() const {return type; }
std::string Message::get_sender() const {return sender; }
std::string Message::get_receiver() const {return receiver; }
std::string Message::get_time() const {return time; }

void Message::print(std::ostream& os) const {
    os << "*************************" << std::endl;
    // ⚠️ 修正1：必须换行，不要写在注释后面
    os << sender << " -> " << receiver << std::endl;
    
    // ⚠️ 修正2：改成小写 message
    os << "message type: " << type << std::endl;
    os << "message time: " << time << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
    msg.print(os);
    return os;
}

// TextMessage Implementation
TextMessage::TextMessage(std::string text, std::string sender, std::string receiver)
    :Message("text", sender, receiver), text(text)
{
}

void TextMessage::print(std::ostream& os) const {
    Message::print(os);
    os << "text: " << text << std::endl;
    os << "*************************" << std::endl; 
}

std::string TextMessage::get_text() const {return text; }

// VoiceMessage Implementation
VoiceMessage::VoiceMessage(std::string sender, std::string receiver)
    :Message("voice", sender, receiver){
        for(int i = 0; i < 5; ++i){
            voice.push_back(static_cast<unsigned char>(rand() % 256));
        }
}

void VoiceMessage::print(std::ostream& os) const {
    Message::print(os);
    os << "voice: ";
    for(size_t i = 0; i < voice.size(); ++i){
        os << static_cast<int>(voice[i]) <<  (i == voice.size() - 1 ? "" : " ");
    }
    // ⚠️ 修正3：打印完数字后必须先换行，再打印星星！
    os << std::endl; 
    os << "*************************" << std::endl; 
}

std::vector<unsigned char> VoiceMessage::get_voice() const {return voice; }
