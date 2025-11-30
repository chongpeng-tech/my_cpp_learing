#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    set<string> st;
    string temp;
    for(int i = 0; i < n; i++){
        cin >> temp;
        st.insert(temp);
    }
    cout << st.size();
    return 0;
}