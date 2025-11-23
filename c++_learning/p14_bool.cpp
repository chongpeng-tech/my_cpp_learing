#include<iostream>

using namespace std;

int main(){
    bool flag = true;
    //尝试输出bool类型
    cout << flag << endl;

    flag = false;
    cout << flag << endl;

    cout << "bool类型变量占字节数为：" << sizeof(flag) << endl;

    return 0;
}