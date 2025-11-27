#include<bits/stdc++.h>
using namespace std;

int main(){
    int m, n, temp;
    int count = 0;
    cin >> m >> n;
    vector<bool> memory_store(1005, false);
    queue<int> q;
    for(int i = 0; i < n; i++){
        cin >> temp;
        if(memory_store[temp] == false){
            count++;
            if(q.size() < m){
                q.push(temp);
                memory_store[temp] = true;
            }else{
                int tempReceive = q.front();
                q.pop();
                q.push(temp);
                memory_store[tempReceive] = false;
                memory_store[temp] = true;
            }
        }

    }
    cout << count;
    return 0;
}