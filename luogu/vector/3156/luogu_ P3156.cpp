//已成功AC
#include<bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int m, n, temp;
    cin >> n >> m;
    vector<int> student;
    for(int i = 0; i < n; i++){
        cin >> temp;
        student.push_back(temp);
    }
    for(int i = 0; i < m; i++){
        cin >> temp;
        cout << student[temp - 1] << "\n";
        //endl换行比较慢，如果比赛超时可以换\n
    }

    return 0;
}