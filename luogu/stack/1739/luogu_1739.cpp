#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    getline(cin, s);
    stack<char> st;
    bool flag = true;
    for(int i = 0; i < s.size() - 1; i++){
        if(s[i] == '(' ){
            st.push(s[i]);
        }
        if(s[i] == ')'){
            if(!st.empty()){
                st.pop();
            }else{
                flag = false;
                break;
            }
        }
    }
    if(flag == true && st.empty()){
        cout << "YES" << '\n';
    }else{
        cout << "NO" << '\n';
    }

    return 0;
}