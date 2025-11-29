#include<bits/stdc++.h>
using namespace std;

int main(){
    string s;
    getline(cin, s);
    stack<int> nums_store;
    int s_size = s.size();
    //int caculator;
    int tempNum = 0;
    for(int i = 0; i < s_size - 1; i++){
        //int tempNum = 0;
        if(s[i] >= '0' && s[i] <= '9'){
            //tempNum = 10 * tempNum + (int)s[i];
            //char字符强转int会变成ascii码，而不是对应的数字
            tempNum = 10 * tempNum + s[i] - '0';
        }else if(s[i]== '.' ){
            nums_store.push(tempNum);
            tempNum = 0;
        }else{
            int tempNum_1 = nums_store.top();
            nums_store.pop();
            int tempNum_2 = nums_store.top();
            nums_store.pop();
            //tempNum = tempNum_2 s[i] tempNum_1;
            //s[i]== '+' || s[i] == '-' || s[i] == '*' || s[i] == '/'
            switch(s[i]){
                case '+' : nums_store.push(tempNum_2 + tempNum_1);break;
                case '-' : nums_store.push(tempNum_2 - tempNum_1);break;
                case '*' : nums_store.push(tempNum_2 * tempNum_1);break;
                case '/' : nums_store.push(tempNum_2 / tempNum_1);break;
            }
        }
             
    }
    cout << nums_store.top();  
    return 0;
}