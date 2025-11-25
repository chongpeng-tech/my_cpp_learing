#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int q,operation;
    string s;
    cin >> q;
    cin >> s;
    for(int i = 0; i < q; i++){
        cin >> operation;
        if(operation == 1){
            string tempstr;
            cin >> tempstr;
            s = s + tempstr;
            cout << s << '\n';
        }
        else if(operation == 2){
            int a,b;
            cin >> a >> b;
            string sub = s.substr(a,b);
            s = sub;
            cout << s << '\n';
        }
        else if(operation == 3){
            int a;
            cin >> a;
            string tempstr;
            //getline(cin,tempstr);
            cin >> tempstr;
            s.insert(a,tempstr);
            cout << s << '\n';
        }
        else{
            string tempstr;
            //getline(cin,tempstr);
            cin >> tempstr;
            int pos = s.find(tempstr);
            cout << pos << '\n';
        }
    }


    return 0;
}