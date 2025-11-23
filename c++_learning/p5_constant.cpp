#include<iostream>
using namespace std;

#define Day  7
int main(){
    cout << "一周一共有：" << Day << "天" <<endl;
    //const在函数内定义？
    //尽量用const更加安全
    const int Month = 12;

    cout << "一年一共" << Month << "个月";
    return 0;
}