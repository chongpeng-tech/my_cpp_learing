#include<bits/stdc++.h>
using namespace std;
//洛谷5733题
int main(){
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    string s;
    getline(cin,s);
    for(int i = 0; i < s.size(); i++){
        if(s[i] >= 'a' && s[i] <= 'z'){
            s[i] = s[i] - 32;
            //s[i] =  toupper(s[i]);
        }
    }
    cout << s;
    return 0;
}