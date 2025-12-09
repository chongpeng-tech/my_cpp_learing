#ifndef UTILS_H
#define UTILS_H

#include<string>
#include<functional> //使用hash?没用过

//先定义函数

size_t hash_string(const std::string& input);
std::string generate_policy_number();
#endif