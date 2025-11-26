#include<bits/stdc++.h>
using namespace std;
struct toy{
    bool toward;
    string name;
};
//此题成功AC，目前做到难度最大的一个！
int main(){
    int n, m;
    cin >> n >> m;
    vector<toy> Toy(n);
    int pos = 0;
    for(int i = 0; i < n; i++){
        cin >> Toy[i].toward;
        cin >> Toy[i].name;
    }
    for(int i = 0; i < m; i++){
        bool tempToward;
        int step_length;
        cin >> tempToward >> step_length;
        bool judge = tempToward ^ Toy[pos].toward;
        //异或为0说明你往逆时针方向走，为1说明往顺时针方向走
        if(judge == 1){
            pos = (pos + step_length) % n;
        }else{
            pos = (((pos - step_length) % n) + n)% n;
        }
    }
    cout << Toy[pos].name;
    return 0;
}