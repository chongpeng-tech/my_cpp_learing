#ifndef PERSON_H
#define PERSON_H

#include<compare>
#include<optional>
#include<string>
#include<stdexcept>

class Person{
    public:
    //公共的，暴露在外的
    Person(const std::string &name, size_t age, const std::string &gender,
const std::string &fingerprint, size_t risk_profile, bool is_insured);
    
        //定义只读接口
    std::string get_name() const;
    size_t get_age() const;
    std::string get_gender() const;
    size_t get_hashed_fingerprint() const;
    size_t get_risk_profile() const;
    bool get_is_insured() const;
        //设置可修改接口
    bool set_age(size_t age);
    bool set_risk_profile(size_t risk_profile);
    bool set_is_insured(bool is_insured);
    //比较风险的东西，没学过，不知道是什么
    std::strong_ordering operator<=>(const Person &other) const;

    //打印信息
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    const std::string name;
    size_t age;
    const std::string gender;
    const size_t hashed_fingerprint;
    size_t risk_profile;
    bool is_insured;


};
#endif //PERSON_H
    