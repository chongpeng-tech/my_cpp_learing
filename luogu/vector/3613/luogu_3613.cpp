#include<bits/stdc++.h>
using namespace std;
//pc测试
int main(){
    //ios::sync_with_stdio(0);
    //cin.tie(0);
    int n,q,temp,num,tempNums,tempItem;
    //int ans = 0;
    cin >> n >> q;
    struct box{
        int nums; //编号
        int item; //物品
    };
    vector<vector<box>> Box(n + 1);
    for(int i = 0; i < q; i++){
        cin >> temp;
        //cout << "debug: temp is " << temp << endl; // 测试用
        if(temp == 1){
            cin >> num >> tempNums >> tempItem;
            Box[num].push_back({tempNums,tempItem});
        }
        if(temp == 2){
            int ans = 0;
            cin >> num >> tempNums;
            //又该怎么完成查询操作呢？
            for(int j = Box[num].size() - 1; j >= 0 ; j--){
                if(tempNums == Box[num][j].nums){
                    ans = Box[num][j].item;
                    break;
                }
            }
            cout << ans << "\n";
        }
    }



    return 0;
}