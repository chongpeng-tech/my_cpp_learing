#ifndef INSURANCE_COMPANY_H
#define INSURANCE_COMPANY_H

#include<compare>
#include<map>
#include<vector>
#include<string>
#include<optional>

//提前声明刚刚写的两个类

class InsurancePolicy;
class Person;

class InsuranceCompany {
    public:
    // 构造函数
    InsuranceCompany(const std::string &company_name, const std::string &security_key);

    // 析构函数：公司倒闭时（对象销毁时）要清理垃圾
    ~InsuranceCompany();

    // 核心业务：买保险、退保、交钱、理赔
    // 注意：所有操作都需要验证指纹 (owner_fingerprint)
    InsurancePolicy* create_policy(Person &owner, const std::string &owner_fingerprint, const std::string &policy_type, double premium_amount, double coverage_amount);
    bool cancel_policy(InsurancePolicy &policy, const std::string &owner_fingerprint);
    bool process_premium(InsurancePolicy &policy, const std::string &owner_fingerprint, double amount);
    bool file_claim(InsurancePolicy &policy, const std::string &owner_fingerprint, double claim_amount);

    // Getters
    const std::string& get_company_name() const;
    size_t get_hashed_security_key() const;

    // 管理员功能：必须提供公司的“安全密钥”才能查看所有数据
    const std::vector<Person*>& get_customers(const std::string &security_key) const;
    const std::vector<InsurancePolicy*>& get_policies(const std::string &security_key) const;
    const std::map<InsurancePolicy*, Person*>& get_policy_to_customer_map(const std::string &security_key) const;
    const std::map<Person*, std::vector<InsurancePolicy*>>& get_customer_to_policy_map(const std::string &security_key) const;
    double get_total_premiums_collected(const std::string &security_key) const;
    double get_total_claims_paid(const std::string &security_key) const;

    // 管理员功能：强制修改保单状态
    bool set_policy_status(InsurancePolicy &policy, bool status, const std::string &security_key);

    // 飞船运算符：比较谁的客户更多
    std::strong_ordering operator<=>(const InsuranceCompany &other) const;

    // 打印信息
    void get_info(std::optional<std::string> file_name = std::nullopt) const;

private:
    const std::string company_name;
    const size_t hashed_security_key; // 公司的密码（存哈希值）
    
    // 数据存储中心
    std::vector<Person*> customers;          // 所有客户的名单
    std::vector<InsurancePolicy*> policies;  // 所有保单的名单
    
    // 关系映射
    // map<保单, 人>: 给你一张保单，查出它的主人是谁
    std::map<InsurancePolicy*, Person*> policy_to_customer; 
    
    // map<人, 保单列表>: 给你一个人，查出他名下的所有保单
    std::map<Person*, std::vector<InsurancePolicy*>> customer_to_policy; 
    
    double total_premiums_collected;
    double total_claims_paid;
};
#endif
