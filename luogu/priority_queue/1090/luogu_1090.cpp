#include<bits/stdc++.h>
using namespace std;

int main(){
    priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int>> q;
    int n, temp;
    int ans = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> temp;
        q.push(temp);
    }
    while(q.size() > 1){
        int op_1 = q.top();
        q.pop();
        int op_2 = q.top();
        q.pop();
        int tempSum = op_1 + op_2;
        ans = ans + tempSum;
        q.push(tempSum);
    }
    cout << ans;

    return 0;
}