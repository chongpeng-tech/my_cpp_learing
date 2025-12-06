#ifndef Q1_VARIADIC_TEMPLATE_SUM_H
#define Q1_VARIADIC_TEMPLATE_SUM_H

#include <iostream>
#include <vector>
#include <string>
#include <type_traits> // 必须包含这个

// 翻译官函数
template <typename T>
double normalize(const T& arg) {
    // 【关键修改】获取“退化”后的类型
    // 作用：把 char[4] 这种数组类型，统统退化成 const char* 指针类型
    using DecayedT = std::decay_t<T>;

    // 1. 检查是不是 std::string
    if constexpr (std::is_same_v<DecayedT, std::string>) {
        return std::stod(arg);
    } 
    // 2. 检查是不是原生字符串 (数组或指针统统算在这里)
    else if constexpr (std::is_same_v<DecayedT, const char*> || std::is_same_v<DecayedT, char*>) {
        return std::stod(std::string(arg));
    } 
    // 3. 数字
    else {
        return static_cast<double>(arg);
    }
}

// sum 函数保持不变
template <typename... Arg>
double sum(const Arg&... args) {
    return (normalize(args) + ...);
}

#endif
