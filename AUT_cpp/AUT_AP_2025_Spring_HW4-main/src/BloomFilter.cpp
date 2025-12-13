#include "BloomFilter.h"
#include<random>
#include<fstream>
template<std::size_t N>
BloomFilter<N>::BloomFilter(unsigned int num_hashes)
    : num_hashes(num_hashes)
{
    server = new CDNServer();
//不能用真随机，何意味
    //std::random_device rd;
    std::mt19937 gen(24);


    //循环num_hashes次，不知道是在干什么
    for(unsigned int i = 0; i < num_hashes; i++){
        std::size_t random_num = gen();
        seeds.push_back(random_num);
    }
}

//还要删掉，不知道是为什么
template<std::size_t N>
BloomFilter<N>::~BloomFilter(){
    delete server;
}

//存东西
template<std::size_t N>
void BloomFilter<N>::add(const std::string &item){
    server->addWord(item);
    for(std::size_t i = 0; i < num_hashes; i++){
    
    std::size_t hash_val = hash(item, seeds[i]);
    std::size_t pos = hash_val % N;

    bits[pos] = 1;
    }
}
//查东西
template<std::size_t N>
bool BloomFilter<N>::possiblyContains(const std::string &item) const{
    for(std::size_t i = 0; i < num_hashes; i++){
        std::size_t hash_val = hash(item, seeds[i]);
        std::size_t pos = hash_val % N;

        if(bits[pos] == 0){
            return false;
        }
    }
    return true;
}

template<std::size_t N>
bool BloomFilter<N>::certainlyContains(const std::string &item) const {
    if(!possiblyContains(item)){
        return false;
    }

    return server-> checkWord(item);
}

template<std::size_t N>
void BloomFilter<N>::reset() {
    bits.reset();
}

template<std::size_t N>
BloomFilter<N>& BloomFilter<N>::operator&(const BloomFilter& other){
    bits &= other.bits;
    return *this;
}

template<std::size_t N>
BloomFilter<N>& BloomFilter<N>::operator|(const BloomFilter& other) {
    bits |= other.bits;
    return *this;
}

template<std::size_t N>
bool BloomFilter<N>::operator()(const std::string& item) const {
    return possiblyContains(item);
}
/*
template<std::size_t N>
BloomFilter<N>::BloomFilter(const BloomFilter& other) 
    :num_hashes(other.num_hashes),
    bits(other.bits),
    seeds(other.seeds)
{
    server = new CDNServer();
}

template<std::size_t N>
BloomFilter<N>::BloomFilter(BloomFilter&& other) noexcept
    :num_hashes(other.num_hashes),
    server(other.server),
    bits(other.bits),
    seeds(std::move(other.seeds))
{
    other.server = nullptr;
}
*/
// ==================== 修正后的拷贝构造函数 ====================
template<std::size_t N>
BloomFilter<N>::BloomFilter(const BloomFilter& other) 
    : bits(other.bits),             // 1. 先是 bits (必须排第一！)
      num_hashes(other.num_hashes), // 2. 接着是 num_hashes
      seeds(other.seeds)            // 3. 然后是 seeds
{
    server = new CDNServer();
}

// ==================== 修正后的移动构造函数 ====================
template<std::size_t N>
BloomFilter<N>::BloomFilter(BloomFilter&& other) noexcept
    : bits(other.bits),                  // 1. bits 第一
      num_hashes(other.num_hashes),      // 2. num_hashes 第二
      seeds(std::move(other.seeds)),     // 3. seeds 第三
      server(other.server)               // 4. server 第四
{
    other.server = nullptr;
}

template<std::size_t N>
bool BloomFilter<N>::possiblyContains(std::string&& item) const{
    return possiblyContains(item);
}

template<std::size_t N>
bool BloomFilter<N>::certainlyContains(std::string&& item) const {
    return certainlyContains(item);
}

// template<std::size_t N>
// void BloomFilter<N>::add(std::string&& file_name){
//     std::ifstream file(file_name);
//     if(!file.is_open()){
//         return;
//     }
//     std::string word;
//     while(file >> word){
//         add(word);
//     }
//     file.close();
// }

// ==================== 修正后的“智能”添加函数 ====================
template<std::size_t N>
void BloomFilter<N>::add(std::string&& item_or_file){
    // 1. 先尝试把它当文件名打开
    std::ifstream file(item_or_file);
    
    if(file.is_open()){
        // A. 打开成功！说明这是个文件
        std::string word;
        while(file >> word){
            if (!word.empty() && word.back() == ',') {
                word.pop_back();
            }
            add(word); // 递归调用基础 add 把文件里的词一个个存进去
        }
        file.close();
    } else {
        // B. 打开失败！说明这不是文件，而是个普通单词（比如 "test"）
        // 或者是文件路径不对，那就当单词处理，总比丢了好
        
        // 强制转换成 const string&，调用那个“存单词”的 add 函数
        const std::string& word_ref = item_or_file;
        add(word_ref); 
    }
}



// ==================== 12. BloomFilter 输出 (<<) ====================
// 格式：哈希数量 + 种子列表 + 位数组
template <std::size_t N>
std::ostream& operator<<(std::ostream& os, const BloomFilter<N>& bf) {
    os << bf.num_hashes << " "; // 先存参数
    for (std::size_t seed : bf.seeds) {
        os << seed << " ";      // 存所有种子
    }
    os << bf.bits;              // 存位数组 (bitset 自带 <<)
    return os;
}

// ==================== 13. BloomFilter 输入 (>>) ====================
template <std::size_t N>
std::istream& operator>>(std::istream& is, BloomFilter<N>& bf) {
    is >> bf.num_hashes; // 读参数
    
    // 重新调整种子数组的大小
    bf.seeds.resize(bf.num_hashes);
    for (unsigned int i = 0; i < bf.num_hashes; ++i) {
        is >> bf.seeds[i]; // 读回种子
    }
    
    is >> bf.bits;       // 读回位数组
    return is;
}

template class BloomFilter<81920>;
template class BloomFilter<1024>;