#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, m;
    //vector<bool> leaveStore(n+1, false);
    cin >> n >> m;
    queue<int> q;
    for(int i = 0; i < n; i++){
        q.push(i + 1);
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m - 1; j++){
            int temp = q.front();
            q.pop();
            q.push(temp);
        }
        cout << q.front() << " ";
        q.pop();
    }

    return 0;
}