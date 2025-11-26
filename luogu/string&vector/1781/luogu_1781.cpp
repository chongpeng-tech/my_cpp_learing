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
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    struct person{
        int id; //第几候选人
        string vote; //该候选人票数；
    };
    int n;
    cin >> n;
    vector<person> store(n);
    for(int i = 0; i < n; i++){
        string tempVote; //转化为string方便记录
        cin >> tempVote;
        store[i] = {i+1, tempVote}; 
    }
    //已记录完所有数据，下一步处理数据
    struct personVoteSize{
        int id;
        int size; //票数位数
    };
    vector<personVoteSize> store_size(n);
    for(int i = 0; i < n; i++){
        int tempsize = store[i].vote.size();
        store_size[i] = {i+1,tempsize};
    }

    return 0;
}