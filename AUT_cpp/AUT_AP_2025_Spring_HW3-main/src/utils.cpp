#include"utils.h"

size_t hash_string(const std::string& input){

    std::hash<std::string> hasher;
    return hasher(input);
}