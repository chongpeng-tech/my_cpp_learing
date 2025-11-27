#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, temp;
    cin >> n;
    map<string, unsigned int> mp;
    for(int i = 0; i < n; i++){
        cin >> temp;
        if(temp == 1){
            string tempName;
            int tempScore;
            cin >> tempName;
            cin >> tempScore;
            mp[tempName] = tempScore;
            cout << "OK" << '\n';
        }else if(temp == 2){
            string findName;
            cin >> findName;
            if(mp.find(findName) == mp.end()){
                cout << "Not found" << '\n';
            }else{
                cout << mp[findName] << '\n';
            }
        }else if(temp == 3){
            string deleteName;
            cin >> deleteName;
            if(mp.find(deleteName) == mp.end()){
                cout << "Not found" << '\n';
            }else{
                mp.erase(deleteName);
                cout << "Deleted successfully" << '\n';
            }
        }else{
            cout << mp.size() << '\n';
        }
    }



    return 0;
}