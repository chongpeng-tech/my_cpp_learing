#include<bits/stdc++.h>
using namespace std;

// 你的裁判规则
bool cmp(pair<int, int> a, pair<int, int> b){
    if (a.first != b.first) {
        return a.first > b.first; // 分数大的在前
    }
    return a.second < b.second;   // 分数一样，号小的在前
}

int main(){
    int n, m;
    cin >> n >> m;
    
    // 1. 改用 vector，方便排序和下标访问
    vector<pair<int, int>> v; 

    for(int i = 0; i < n; i++){
        int id, score;
        cin >> id >> score;
        // 2. vector 用 push_back 插入
        // 注意：这里我们按照 {成绩, 报名号} 的顺序存，配合 cmp 使用
        v.push_back({score, id}); 
    }

    // 3. 核心大招：调用 sort，把你的裁判 cmp 传进去
    sort(v.begin(), v.end(), cmp);

    // 测试一下：输出排好序后的第一个人，看看是不是分最高的
    // cout << v[0].first << " " << v[0].second << endl;

    // -----------
    // 接下来写题目的核心逻辑：
    // 算出面试分数线，并输出入选的人
    int limitedLine = m * 1.5;
    int limitedScore = v[limitedLine - 1].first;
    int count = 0;
    for(auto p: v){
        if(p.first >= limitedScore){
            count++;
        }else{
            break;
        }
    }
    int flag = 0;

    cout << limitedScore << " " << count << '\n';
    while(v[flag].first >= limitedScore){
        cout << v[flag].second << " " << v[flag].first << '\n';
        flag++;
    }
    // -----------

    return 0;
}
