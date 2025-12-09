
#ifndef INSURANCE_POLICY_H
#define INSURANCE_POLICY_H

#include <compare>
#include <optional>
#include <string>

// 前向声明：告诉编译器“这两个东西以后会有的，别急着报错”
// 因为保单里要用到 Person 和 InsuranceCompany 的指针
class InsuranceCompany; 
class Person;           

class InsurancePolicy {
    // 允许 InsuranceCompany 随意访问我的私有数据（因为公司是管理者）
    friend class InsuranceCompany; 

public:
    // 构造函数：注意这里传入的是指针 (Person* owner)
    InsurancePolicy(const Person* const owner, const InsuranceCompany* const company, const std::string &policy_type, double premium_amount, double coverage_amount);

    // Getters
    const Person* get_owner() const;
    std::string get_policy_number() const;
    std::string get_policy_type() const;
    double get_premium_amount() const;
    double get_coverage_amount() const;
    bool get_policy_status() const; // true 是一切正常，false 是被取消了

    // 【核心难点】验证身份后才能看详细信息
    // 你需要检查传入的 fingerprint 是否和 owner 的指纹匹配
    std::string get_policy_details(const std::string &owner_fingerprint) const;

    // Setters (带身份验证)
    bool set_policy_type(const std::string &new_policy_type, const std::string &owner_fingerprint);
    bool set_premium_amount(double new_premium, const std::string &owner_fingerprint);

    // 飞船运算符：比较保单号
    std::strong_ordering operator<=>(const InsurancePolicy &other) const;

    // 打印信息
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    const Person* owner;            // 这里的星号 * 表示我们只存这个人的“地址”
    const InsuranceCompany* company;// 只存公司的“地址”
    const std::string policy_number;// 唯一的保单号（需要随机生成）
    std::string policy_type;
    double premium_amount;
    double coverage_amount;
    bool policy_status;
    int payment_counter;
};

#endif // INSURANCE_POLICY_H
