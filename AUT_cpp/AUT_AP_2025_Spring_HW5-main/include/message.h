#ifndef MESSAGE_H
#define MESSAGE_H

#include<string>
#include<vector>
#include<iostream>

class Message {
public:
    Message(std::string type, std::string sender, std::string receiver);
    Message(); //默认的构造函数，暂时不知道怎么用

    //Getter函数
    std::string get_type() const;
    std::string get_sender() const;
    std::string get_receiver() const;
    std::string get_time() const;
    
    //多态
    virtual void print(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const Message& c);
//类内部
private:
    std::string type;
    std::string sender;
    std::string receiver;
    std::string time;
};
//派生类1，文本信息
class TextMessage : public Message {
public:
    TextMessage(std::string text, std::string sender, std::string receiver);
    void print(std::ostream& os) const override;
    //重写？？这是什么？
    std::string get_text() const;


private:
    std::string text;
};
//派生类2，语音信息
class VoiceMessage : public Message {
public:
    VoiceMessage(std::string sender, std::string receiver);
    
    void print(std::ostream& os) const override;

    std::vector<unsigned char> get_voice() const;

private:
    std::vector<unsigned char> voice;


};

#endif //MESSAGE_H