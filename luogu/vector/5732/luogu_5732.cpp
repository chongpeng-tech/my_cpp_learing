//此题已经AC

#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> triangle(n);
    for(int i = 0; i < n; i++){
        triangle[i].resize(i+1);
        triangle[i][0] = 1;
        triangle[i][i] = 1;
        for(int j = 1; j < i; j++){
            triangle[i][j] = triangle[i-1][j-1] + triangle[i-1][j];
        } 
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < triangle[i].size(); j++){
            cout << triangle[i][j];
            if(j != triangle[i].size() -1){
                cout << " ";
            }
        }
        cout << "\n";
    }



    return 0;
}