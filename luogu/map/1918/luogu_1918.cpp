#include<bits/stdc++.h>
using namespace std;
//洛谷1918题，保龄球
int main(){
    int n, q;
    cin >> n;
    map<unsigned int, unsigned int> mp;
    //前面是球数，后面存位置
    for(int i = 0; i < n; i++){
        int tempBalls;
        cin >> tempBalls;
        mp[tempBalls] = i + 1;
    }
    cin >> q;
    for(int i = 0; i < q; i++){
        int findBalls;
        cin >> findBalls;
        if(mp.find(findBalls) != mp.end()){
            cout << mp[findBalls] << '\n';
        }else{
            cout << 0 << '\n';
        }
    }
    return 0;
}