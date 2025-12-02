#include<bits/stdc++.h>
using namespace std;
bool cmp(pair<int, int> a, pair<int, int> b){
    return a.first > b.first;
}
//自己的错误代码
int main(){
    int n, m;
    cin >> n >> m;
    set<pair<int , int>> st;
    for(int i = 0; i < n; i++){
        int id, score;
        cin >> id >> score;
        st.insert({score,id});
    }



    return 0;
}