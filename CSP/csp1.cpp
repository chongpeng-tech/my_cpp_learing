#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k = 0;
    int mu = 0;
    int sigma = 0;
    int n = 0;
    int val = 0;
    cin >> k;
    for(int a = 0; a < k; a++){
        cin >> mu;
        cin >> sigma;
        cin >> n;
        val = (100 * n - 100 * mu) / sigma;
        int j = val % 10 + 1;
        int i = val / 10 + 1;
        cout << i << " " << j << endl;
    }


    return 0;
}
     