#include<bits/stdc++.h>
using namespace std;

int main(){
     cout << "STARTING..." << endl; 
    int size,temp;
    int count = 0;
    vector<int> nums;
    vector<int> res;
    cin >> size;
    for(int i = 0; i < size; i++){
        cin >> temp;
        nums.push_back(temp);
    }
    sort(nums.begin(),nums.end());
    for(int i = 0; i < size - 1; i++){
        if(nums[i] != nums[i+1]){
            res.push_back(nums[i]);
        }
    }
    res.push_back(nums[nums.size() - 1]);
    cout << res.size() << endl;
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << " " ;
    }
    cout << endl;



    return 0;
}