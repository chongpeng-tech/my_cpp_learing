#include<iostream>
using namespace std;

int main(){
    float num1 = 3.14f;
    double num2 = 3.1415926;
    //一般来说只显示五位小数
    cout << num1 << endl;
    cout << num2 << endl;

    cout << "float型占字节数为" << sizeof(num1) << endl;
    cout << "double型占字节数为" << sizeof(num2) << endl;
    //科学计数法
    float num3 = 3e2;
    float num4 = 3e-2;
    cout << num3 << endl;
    cout << num4 << endl;
    //cout << Day;
    return 0;
}