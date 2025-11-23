#include<iostream>
using namespace std;

int main(){
    short num1 = 10;
    int num2 = 10;
    long num3 = 10;
    long long num4 = 10;

    cout << "short整型占用字节数" << sizeof(num1) << endl;
    cout << "int整型占用字节数" << sizeof(num2) << endl;
    cout << "long整型占用字节数" << sizeof(num3) << endl;
    cout << "longlong整型占用字节数" << sizeof(num4) << endl;
    return 0;
}