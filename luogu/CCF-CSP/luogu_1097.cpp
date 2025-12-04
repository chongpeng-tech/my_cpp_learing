#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    map<unsigned int, unsigned int> mp;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int tempNum;
        cin >> tempNum;
        mp[tempNum]++;
    }
    for(const auto& pair :mp){
        cout << pair.first << " " << pair.second << '\n';
    }

    return 0;
}