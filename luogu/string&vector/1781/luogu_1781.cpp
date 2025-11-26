#include<bits/stdc++.h>
using namespace std;
/*
5
98765
12365
87954
1022356
985678
输入样例
*/
//尝试一下git的版本回溯
//以后跨终端必须先pull！！！！！
struct person{
    int id; //第几候选人
    string vote; //该候选人票数；
};
bool cmp(person a, person b){
    if(a.vote.size() != b.vote.size()){
        return b.vote.size() < a.vote.size();
    }else{
        return a.vote > b.vote;
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
  /*  struct person{
        int id; //第几候选人
        string vote; //该候选人票数；
    };
    */
    int n;
    cin >> n;
    vector<person> store(n);
    for(int i = 0; i < n; i++){
        string tempVote; //转化为string方便记录
        cin >> tempVote;
        store[i] = {i+1, tempVote}; 
    }
    //已记录完所有数据，下一步处理数据
    sort(store.begin(),store.end(),cmp);
    cout << store[0].id << '\n';
    cout << store[0].vote;

    return 0;
}