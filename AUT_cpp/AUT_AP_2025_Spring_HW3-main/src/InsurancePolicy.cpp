#include"utils.h"
#include"InsurancePolicy.h"
#include"Person.h"
#include<iostream>
#include<stdexcept>
#include<fstream>

InsurancePolicy::InsurancePolicy(const Person* const owner, 
                                const InsuranceCompany* const company, 
                                const std::string &policy_type, 
                                double premium_amount, //价格
                                double coverage_amount)//最高赔付金额

          :owner(owner),
            company(company),
            //用之前的随机生成器生成单号
            policy_number(generate_policy_number()),
            policy_type(policy_type),
            premium_amount(premium_amount),
            coverage_amount(coverage_amount),
            policy_status(true),
            payment_counter(0){
    if(policy_type != "Life" && policy_type != "Health" && 
        policy_type != "Automobile" && policy_type != "Property"){
            throw std::invalid_argument("invalid policy type");
        }
}
// 2. 简单的 Getters (直接复制)
const Person* InsurancePolicy::get_owner() const { return owner; }
std::string InsurancePolicy::get_policy_number() const { return policy_number; }
std::string InsurancePolicy::get_policy_type() const { return policy_type; }
double InsurancePolicy::get_premium_amount() const { return premium_amount; }
double InsurancePolicy::get_coverage_amount() const { return coverage_amount; }
bool InsurancePolicy::get_policy_status() const { return policy_status; }

//有人来获取信息了，先检验身份
std::string InsurancePolicy::get_policy_details(const std::string
 &owner_fingerprint) const {
    size_t input_hash = hash_string(owner_fingerprint);
    if(owner -> get_hashed_fingerprint() != input_hash){
        throw std::invalid_argument("Authentication failed : wrong fingerprint.");
    }else{
        return "Policy Number: " + policy_number + ", Type: " + policy_type;
    }
 }

 //验证权限之后的修改器
 bool InsurancePolicy::set_policy_type(const std::string &new_policy_type,
 const std::string &owner_fingerprint){
     size_t input_hash = hash_string(owner_fingerprint);
    if(owner -> get_hashed_fingerprint() != input_hash){
        return false;
    }else{
        if(new_policy_type != "Life" && new_policy_type != "Health" && 
        new_policy_type != "Automobile" && new_policy_type != "Property"){
            return false;
        }else{
            policy_type = new_policy_type;
            return true;
        }
    }
 }

 //鉴权之后修改金额
 bool InsurancePolicy::set_premium_amount(double new_premium_amount, 
 const std::string &owner_fingerprint){
     size_t input_hash = hash_string(owner_fingerprint);
      if(owner -> get_hashed_fingerprint() != input_hash){
        return false;
    }else{
      premium_amount = new_premium_amount;
      return true;       
    }
 }

 std::strong_ordering InsurancePolicy::operator<=>(const InsurancePolicy &other) const {
    return policy_number <=> other.policy_number;
 } 
 
// 6. 打印信息 (get_info)
void InsurancePolicy::get_info(std::optional<std::string> file_name) const {

    std::string info = "Policy #" + policy_number + " (" + policy_type + ")";
    
    if (file_name.has_value()) {
         std::ofstream outfile(file_name.value(), std::ios::app);
         outfile << info << std::endl;
    } else {
         std::cout << info << std::endl;
    }
}

