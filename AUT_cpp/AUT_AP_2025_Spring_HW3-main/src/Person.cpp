#include"Person.h"
#include"utils.h"
#include<iostream>
#include<fstream> //也是没用过的库

Person::Person(const std::string &name, 
                size_t age, 
                const std::string &gender,
                const std::string &fingerprint, 
                size_t risk_profile, 
                bool is_insured)
//直接初始化
    :name(name),
    age(age),
    gender(gender),
    hashed_fingerprint(hash_string(fingerprint)),
    risk_profile(risk_profile),
    is_insured(is_insured)
{
    //参数合法性检查
    if(gender != "Male" && gender != "Female"){
        throw std::invalid_argument("Invalid gender");
    }
}
    //getter函数，自己写
    std::string Person::get_name() const{
        return name;
    }
    size_t Person::get_age() const{
        return age;
    }
    std::string Person::get_gender() const{
        return gender;
    }
    size_t Person::get_hashed_fingerprint() const{
        return hashed_fingerprint;
    }
    size_t Person::get_risk_profile() const{
        return risk_profile;
    }
    bool Person::get_is_insured() const{
        return is_insured;
    }
    //setter
    bool Person::set_age(size_t new_age){
        if(new_age > 150){
            return false;
        }else{
            age = new_age;
            return true;
        }
    }
    bool Person::set_risk_profile(size_t new_risk_profile){
        if(new_risk_profile < 1 || new_risk_profile > 10){
            return false;
        }else{
            risk_profile = new_risk_profile;
            return true;
        }
    }
    bool Person::set_is_insured(bool new_state){
        is_insured = new_state;
        return true;
    }
//飞船运算符咋用，何意味
std::strong_ordering Person::operator<=>(const Person &other) const{
    return risk_profile <=> other.risk_profile;
}

//打印信息
void Person::get_info(std::optional<std::string> file_name) const {
    std::string info = "Name: " + name + ", Age: " + std::to_string(age) + 
                       ", Gender: " + gender + ", Risk: " + std::to_string(risk_profile) + 
                       ", Insured: " + (is_insured ? "Yes" : "No");

    if (file_name.has_value()) {
        // 不知道怎么用，先照抄吧
        std::ofstream outfile(file_name.value(), std::ios::app); // append模式
        outfile << info << std::endl;
    } else {
        // 否则打印到屏幕
        std::cout << info << std::endl;
    }
}