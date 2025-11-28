#include<bits/stdc++.h>
using namespace std;

int main(){
    int temp;
    stack<int> s;
    while(1){
        cin >> temp;
        if(temp != 0){
            s.push(temp);
        }else{
            break;
        }
    }
    int s_size = s.size();
    /*
    for(int i = 0; i < s_size; i++){
        cout << s.top() << " ";
        s.pop();
    }
    */
    //有更c++的写法
    while(!s.empty()){
        cout << s.top() << " ";
        s.pop();
    }
    return 0;
}