#include<iostream>
using namespace std;

int main(){
    char ch = 'A';
    cout << "字符型变量占据字节数" << sizeof(ch) << endl;
    cout << ch << endl;

    //查看ASCII码
    cout << (int)ch << endl;
    return 0;
}