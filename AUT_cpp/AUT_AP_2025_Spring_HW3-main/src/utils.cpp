#include"utils.h"
#include<random>
size_t hash_string(const std::string& input){

    std::hash<std::string> hasher;
    return hasher(input);

}
std::string generate_policy_number(){
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    //随机种子
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, characters.size() - 1);
    std::string policy_number;
    for(int i = 0; i < 16; i++){
        policy_number += characters[dis(gen)];
    }
    return policy_number;
}