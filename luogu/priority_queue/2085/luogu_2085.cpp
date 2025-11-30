#include<bits/stdc++.h>
using namespace std;
struct nodeVal{
    int val;
    int x;
    int id;
    bool operator< (const nodeVal &other) const{
        return this -> val > other.val; 
    }
};
int main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1), b(n + 1), c(n + 1);
    priority_queue<nodeVal> q;
    for(int i = 1; i <= n; i++){
        cin >> a[i] >> b[i] >> c[i];
        int val = a[i] + b[i] + c[i];
        q.push({val, 1, i});
    }
    for(int i = 1; i <= m; i++){
        nodeVal topnode = q.top();
        cout << topnode.val << " ";
        q.pop();
        int val = a[topnode.id] * (topnode.x + 1) * (topnode.x + 1) + b[topnode.id]*(topnode.x + 1) + c[topnode.id];
        q.push({val, topnode.x + 1, topnode.id});
    }


    return 0;
}