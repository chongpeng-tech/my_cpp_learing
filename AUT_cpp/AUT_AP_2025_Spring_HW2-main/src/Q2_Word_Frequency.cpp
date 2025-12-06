#include"Q2_Word_Frequency.h"
#include <map>
#include <sstream> // 对应 stringstream
#include <cctype> 
std::map<std::string, int> countWords(const std::string& text){
    std::map<std::string, int> words_map;
    std::string clean_text;
    for(char ch: text){
        if(std::isalnum(ch)){
            clean_text += std::tolower(ch);
        }else{
            clean_text += ' ';
        }
    }
    std::stringstream ss(clean_text);
    std::string word;
    while(ss >> word){
        words_map[word]++;
    }
    return words_map;
}