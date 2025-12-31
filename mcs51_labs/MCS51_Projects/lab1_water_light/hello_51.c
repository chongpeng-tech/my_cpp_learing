#include <8051.h>

void main() {
    // 让 P1 口输出 0xAA (10101010)，这是单片机最经典的测试信号
    P1 = 0xAA;
    while(1);
}

