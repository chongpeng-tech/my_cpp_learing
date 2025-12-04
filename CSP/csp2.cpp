#include<bits/stdc++.h>
using namespace std;
const int MAX = 105;
bool vis[MAX][MAX];
int dx[] = {1,1,2,2,-1,-1,-2,-2};
int dy[] = {2,-2,1,-1,2,-2,1,-1};

int main(){
    //这就是一个bfs，你可以的！
    int n, k, x, y;
    int count = 1;
    cin >> n >> k >> x >> y;
    queue<pair<int, int>> q;
    vis[x][y] = 1;
    q.push({x, y});
    for(int step = 0; step < k; step++){
        if(q.empty()){
            break;
        }else{
            int current_level_size = q.size();
            for(int level = 0; level < current_level_size; level++){
                pair<int, int> temp = q.front();
                //.加函数的形式全部要加括号！
                q.pop();
                //count++;
                for(int key = 0; key < 8; key++){
                    int temp_x = temp.first + dx[key];
                    int temp_y = temp.second + dy[key];
                    if(temp_x >= 1 && temp_x <= n && temp_y >= 1 && temp_y <= n && vis[temp_x][temp_y] != 1){
                        q.push({temp_x,temp_y});
                        count++;
                        vis[temp_x][temp_y] = 1;
                    }else{
                        continue;
                    }
                }
            }
        }
        //cout << count << '\n';
    }
        cout << count << '\n';

    return 0;
}