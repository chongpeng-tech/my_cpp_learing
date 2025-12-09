#include"utils.h"
#include"Person.h"
#include"InsurancePolicy.h"
#include"InsuranceCompany.h"
#include<iostream>
#include<stdexcept>
#include<fstream>
#include<algorithm>
//构造.h里面的函数
InsuranceCompany::InsuranceCompany(const std::string &company_name,
const std::string &security_key)
    :company_name(company_name),
    hashed_security_key(hash_string(security_key)),
    total_premiums_collected(0.0),
    total_claims_paid(0.0)
{
    //暂时没有需要检查的
}

//公司倒闭的时候要做的事

InsuranceCompany::~InsuranceCompany(){
    for(InsurancePolicy* policy: policies){
        delete policy;
    }
    policies.clear();
    customers.clear();
}

const std::string& InsuranceCompany::get_company_name() const{
    return company_name;
}
size_t InsuranceCompany::get_hashed_security_key() const{
    return hashed_security_key;
}

InsurancePolicy* InsuranceCompany::create_policy(Person &owner, 
    const std::string &owner_fingerprint, 
    const std::string &policy_type, 
    double premium_amount, 
    double coverage_amount){
        if(owner.get_hashed_fingerprint() != hash_string(owner_fingerprint)){
            throw std::invalid_argument("Authentication failed: Wrong fingerprint.");
        }
        bool customer_exists = false;
        for(Person* p: customers){
            if(p == &owner){
                customer_exists = true;
                break;
            }
        }
        if(!customer_exists){
            customers.push_back(&owner);
        }

        InsurancePolicy* new_policy = new InsurancePolicy(&owner, this,
        policy_type, premium_amount, coverage_amount);
        //创建完新保单，存保单了

        policies.push_back(new_policy);
        policy_to_customer[new_policy] = &owner;
        customer_to_policy[&owner].push_back(new_policy);

        owner.set_is_insured(true);
        return new_policy;
}

//退保业务

bool InsuranceCompany::cancel_policy(InsurancePolicy &policy, 
const std::string &owner_fingerprint){
    //还是先检查是否为本人
    if(policy.get_owner()->get_hashed_fingerprint() != hash_string(owner_fingerprint)){
        return false;
    }

    policy.policy_status = false;

    Person* owner = policy_to_customer[&policy];
    std::vector<InsurancePolicy*> his_policies = customer_to_policy[owner];

    bool has_active_policy = false;
    for(InsurancePolicy* p : his_policies){
        if(p -> get_policy_status() == true){
            has_active_policy = true;
            break;
        }
    }
    if(!has_active_policy){
        owner -> set_is_insured(false);
    }
    return true;
}

//交保费

bool InsuranceCompany::process_premium(InsurancePolicy &policy, 
const std::string &owner_fingerprint, double amount){
    if(policy.get_owner() -> get_hashed_fingerprint() != hash_string(owner_fingerprint)){
        return false;
    }
    //公司把钱入账
    total_premiums_collected += amount;
        policy.payment_counter++; // 计数器 +1 (因为是 friend 类，可以直接访问私有变量)

    if (policy.payment_counter % 3 == 0) { // 如果是 3 的倍数 (3, 6, 9...)
        Person* owner = const_cast<Person*>(policy.get_owner());
        if (owner->get_risk_profile() > 1) { // 只有大于 1 才能减
            owner->set_risk_profile(owner->get_risk_profile() - 1);
        }
        // 这里可以选择重置 counter = 0，或者继续累加用 % 取模。
        // 为了符合"连续"的定义，如果题目没说重置，模运算最稳妥。
    }
    return true;
}

//赔付
bool InsuranceCompany::file_claim(InsurancePolicy &policy, 
const std::string &owner_fingerprint, double claim_amount){
    if(policy.get_owner() -> get_hashed_fingerprint() != hash_string(owner_fingerprint)){
        throw std::invalid_argument("Authentication failed: Wrong fingerprint.");
    }

    //赔钱审核，看能不能赔得起
    if(claim_amount > policy.get_coverage_amount()){
        return false; //不在范围内，不理赔
    }
    total_claims_paid += claim_amount;

    //下调用户评级
    policy.payment_counter = 0;
    Person* owner = const_cast<Person*>(policy.get_owner());

    if(owner -> get_risk_profile() < 10){
        owner->set_risk_profile(owner->get_risk_profile() + 1);
    }
    return true;
}

// 补充：飞船运算符 (比较公司规模)
std::strong_ordering InsuranceCompany::operator<=>(const InsuranceCompany &other) const {
    // 比较谁的客户数量多 (customers.size())
    return customers.size() <=> other.customers.size();
}

// 补充：打印信息
void InsuranceCompany::get_info(std::optional<std::string> file_name) const {
    // 简单打印一下公司业绩
    std::string info = "Company: " + company_name + 
                       ", Customers: " + std::to_string(customers.size()) + 
                       ", Policies: " + std::to_string(policies.size()) +
                       ", Balance: " + std::to_string(total_premiums_collected - total_claims_paid);

    if (file_name.has_value()) {
         std::ofstream outfile(file_name.value(), std::ios::app);
         outfile << info << std::endl;
    } else {
         std::cout << info << std::endl;
    }
}

// ==========================================
// 补全：管理员/后台查询接口 (需要验证 security_key)
// ==========================================

// 1. 获取所有客户名单
const std::vector<Person*>& InsuranceCompany::get_customers(const std::string &security_key) const {
    if (hash_string(security_key) != hashed_security_key) {
        throw std::invalid_argument("Invalid security key");
    }
    return customers;
}

// 2. 获取所有保单名单
const std::vector<InsurancePolicy*>& InsuranceCompany::get_policies(const std::string &security_key) const {
    if (hash_string(security_key) != hashed_security_key) {
        throw std::invalid_argument("Invalid security key");
    }
    return policies;
}

// 3. 获取保单->人的映射
const std::map<InsurancePolicy*, Person*>& InsuranceCompany::get_policy_to_customer_map(const std::string &security_key) const {
    if (hash_string(security_key) != hashed_security_key) {
        throw std::invalid_argument("Invalid security key");
    }
    return policy_to_customer;
}

// 4. 获取人->保单列表的映射
const std::map<Person*, std::vector<InsurancePolicy*>>& InsuranceCompany::get_customer_to_policy_map(const std::string &security_key) const {
    if (hash_string(security_key) != hashed_security_key) {
        throw std::invalid_argument("Invalid security key");
    }
    return customer_to_policy;
}

// 5. 获取总收保费
double InsuranceCompany::get_total_premiums_collected(const std::string &security_key) const {
    if (hash_string(security_key) != hashed_security_key) {
        throw std::invalid_argument("Invalid security key");
    }
    return total_premiums_collected;
}

// 6. 获取总赔付额
double InsuranceCompany::get_total_claims_paid(const std::string &security_key) const {
    if (hash_string(security_key) != hashed_security_key) {
        throw std::invalid_argument("Invalid security key");
    }
    return total_claims_paid;
}

// 7. 管理员强制修改保单状态
bool InsuranceCompany::set_policy_status(InsurancePolicy &policy, bool status, const std::string &security_key) {
    if (hash_string(security_key) != hashed_security_key) {
        // 验证失败返回 false (或者抛异常也可以，这里为了安全返回false)
        return false;
    }
    policy.policy_status = status;
    return true;
}
