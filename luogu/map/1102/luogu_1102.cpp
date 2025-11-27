#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, c;
    long long temp;
    long long ans = 0;
    cin >> n >> c;
    vector<int> store(n);
    map<long long, int> mp;
    for(int i = 0; i < n; i++){
        cin >> temp;
        mp[temp]++;
        store[i] = temp;
    }
    for(int i = 0; i < n; i++){
        ans = ans + mp[store[i] - c];
    }
    cout << ans;


    return 0;
}