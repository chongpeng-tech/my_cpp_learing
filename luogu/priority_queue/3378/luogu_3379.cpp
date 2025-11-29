#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, op;
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>> q;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> op;
        if(op == 1){
            int tempNum;
            cin >> tempNum;
            q.push(tempNum);
        }else if(op == 2){
            cout << q.top() << '\n';
        }else{
            if(!q.empty()){
                q.pop();
            }
        }

    }

    return 0;
}