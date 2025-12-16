#include <gtest/gtest.h>

#include <iostream>

#include "message.h"
#include "server.h"
#include "user.h"

int main(int argc, char **argv) {
	if (false)	// Set to false to run unit-tests
	{
		    std::cout << "========= 启动聊天服务器 =========" << std::endl;

    // 1. 创建服务器
    Server my_server;

    // 2. 创建用户
    std::cout << "正在创建用户..." << std::endl;
    User david = my_server.create_user("david");
    User jenifer = my_server.create_user("jenifer");

    // 3. 发送消息
    std::cout << "正在发送消息..." << std::endl;
    david.send_text_message("Hello Jenifer!", "jenifer");
    jenifer.send_text_message("Hi David! How are you?", "david");
    david.send_voice_message("jenifer"); // 发送语音

    // 4. 查看聊天记录
    std::cout << "========= 查看聊天记录 =========" << std::endl;
    std::vector<Message*> chat = my_server.get_chat("david", "jenifer");

    for(auto msg : chat) {
        std::cout << *msg << std::endl; 
    }
    std::cout << "================================" << std::endl;
		// Debug section: Place your debugging code here
	} else {
		::testing::InitGoogleTest(&argc, argv);
		std::cout << "RUNNING TESTS ..." << std::endl;
		int ret{RUN_ALL_TESTS()};
		if (!ret)
			std::cout << "<<<SUCCESS>>>" << std::endl;
		else
			std::cout << "FAILED" << std::endl;
	}
	return 0;
}