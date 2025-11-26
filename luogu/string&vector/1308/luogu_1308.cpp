#include<bits/stdc++.h>
using namespace std;
//暂时没有AC😭
int main(){
    string find, text, temp;
    vector<string> store;
    int count = 0;
    int firstPos = -1;
    int currentPos = 0;
    //用vector存单词，但是该怎么切割单词呢
    getline(cin,find);
    getline(cin,text);
    for(int i = 0; i < find.size(); i++){
        if(find[i] >= 'A' && find[i] <= 'Z'){
            find[i] = tolower(find[i]);
        }
    }
    for(int i = 0; i < text.size(); i++){
        if(text[i] >= 'A' && text[i] <= 'Z'){
            text[i] = tolower(text[i]);
        }
    }
    stringstream ss(text);
    while(ss >> temp){
        store.push_back(temp);
    }
    int store_size = store.size();
    for(int i = 0; i < store_size; i++){
        if(find == store[i]){
            count++;
            if(firstPos == -1){
                firstPos =  currentPos;
            }
        }
        currentPos = currentPos + store[i].size() + 1;
    }
    if(firstPos == -1){
        cout << -1;
    }else{
        cout << count << " " << firstPos;
    }
    return 0;
}