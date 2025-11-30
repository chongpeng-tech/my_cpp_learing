#include<bits/stdc++.h>
using namespace std;

int main(){
    int n, temp;
    cin >> n;
    set<int> st;
    for(int i = 0; i < n; i++){
        cin >> temp;
        st.insert(temp);
    }
    cout << st.size() << '\n';
    for(auto x: st){
        cout << x << " ";
    }

    return 0;
}