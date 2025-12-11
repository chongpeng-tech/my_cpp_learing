#include "Trie.h"
#include<iostream>
#include<cctype>
#include<queue>
#include<stack>
#include <vector> 
//创建树根
// Trie::Node::Node(char data, bool is_finished)
//     :data(data),
//     is_finished(is_finished),
//     parent(nullptr)
// {
//     children.fill(nullptr);
// }
Trie::Node::Node(char data, bool is_finished)
    : parent(nullptr),        // 1. 先初始化老大 parent
      data(data),             // 2. 再初始化 data
      is_finished(is_finished)// 3. 最后是 is_finished
{
    children.fill(nullptr);
}

//删节点
Trie::Node::~Node(){
    for(auto* child: children){
        if(child != nullptr){
            delete child;
        }
    }
}

//创建树
Trie::Trie() {
    root = new Node();
}

//删除树
Trie::~Trie() {
    delete root;
}

//往树里加单词
void Trie::insert(const std::string& str) {
    Node* current = root;
    for(char ch: str){
        if(!std::isalpha(ch)){
            //throw std::invalid_argument("invalid input");
            continue;
        }
        char lower_ch = std::tolower(ch);

        int index = lower_ch - 'a';

        if(current->children[index] == nullptr){
            current->children[index] = new Node(lower_ch);
            current->children[index]->parent = current;
        }
        current = current->children[index];
    }
    current->is_finished = true;

}
//查找单词
bool Trie::search(const std::string& str) const {
    Node* current = root;
    for(char ch: str){
        if(!std::isalpha(ch)){
            //throw std::invalid_argument("invalid input");
            continue;
        }
        char lower_ch = std::tolower(ch);

        int index = lower_ch - 'a';

        if(current->children[index] == nullptr){
          return false;
        }
        current = current->children[index];
    }
    return current->is_finished;
}

//查找是否有以prefix为前缀的单词存在
bool Trie::startsWith(const std::string& prefix) const {
       Node* current = root;
    for(char ch: prefix){
        if(!std::isalpha(ch)){
            //throw std::invalid_argument("invalid input");
            continue;
        }
        char lower_ch = std::tolower(ch);

        int index = lower_ch - 'a';

        if(current->children[index] == nullptr){
          return false;
        }
        current = current->children[index];
    }
    return true;

}

void Trie::bfs(std::function<void(Node*&)> func) {
    std::queue<Node*> q;

    q.push(root);

    while(!q.empty()) {
        Node* current = q.front();
        q.pop();

        func(current);
        for(auto* child: current->children){
            if(child != nullptr){
                q.push(child);
            }
        }
    }

}

void Trie::dfs(std::function<void(Node*&)> func) {
    std::stack<Node*> st;

    st.push(root);
    while(!st.empty()){
        Node* current = st.top();
        st.pop();
        func(current);
        for(auto* child: current->children){
            if(child != nullptr){
                st.push(child);
            }
    }
    }
}

void Trie::remove(const std::string& str){
    Node* current = root;
    for(char ch: str){
        if(!std::isalpha(ch)){
            //throw std::invalid_argument("invalid input");
            continue;
        }
        char lower_ch = std::tolower(ch);

        int index = lower_ch - 'a';

        if(current->children[index] == nullptr){
        //根本没这个单词
          return;
        }
        current = current->children[index];
    }
    if(!current->is_finished){
        //有这条路但是没这个单词
        return;
    }
    current->is_finished = false;//先把这个单词删了，再收拾残局

    auto hasChildren = [](Node* node) {
        for(auto* child: node->children){
            if(child != nullptr){
                return true;
            }
        }
        return false;
    };
    //开始删节点
    while(current != root && !hasChildren(current) && !current->is_finished){
        Node* parent = current->parent;

        int index = current->data - 'a';
        parent->children[index] = nullptr;
        delete current;
        current = parent;
    }
    
}

//克隆一颗树
// Trie::Node* clone(Node* src) {
//     if(src == nullptr){
//         return nullptr;
//     }
//     Trie::Node* new_node = new Trie::Node(src->data, src-> is_finished);
//     for(int i = 0; i < 26; i++){
//         if(src->children[i] != nullptr){
//         new_node->children[i] = clone(src->children[i]);
//         new_node->children[i]->parent = new_node;
//         }
//     }
//     return new_node;
// }
// 改名：叫 cloneHelper，避免和系统函数打架
// 修正类型：参数里的 Node* 改成 Trie::Node*
Trie::Node* cloneHelper(Trie::Node* src) {
    if (src == nullptr) {
        return nullptr;
    }
    Trie::Node* new_node = new Trie::Node(src->data, src->is_finished);
    for (int i = 0; i < 26; i++) {
        if (src->children[i] != nullptr) {
            // 注意：这里递归调用也要改名
            new_node->children[i] = cloneHelper(src->children[i]);
            new_node->children[i]->parent = new_node;
        }
    }
    return new_node;
}


// ==================== 6. 拷贝构造 (影分身) ====================
Trie::Trie(const Trie& other) {
    // 调用刚才写的秘密武器，把别人的根节点完全克隆一份给我
    root = cloneHelper(other.root);
}

// ==================== 7. 移动构造 (瞬间移动) ====================
Trie::Trie(Trie&& other) {
    // 1. 直接抢走它的根节点
    root = other.root;
    // 2. 告诉它：你没有家了 (防止它析构时把树炸了)
    other.root = nullptr;
}

// ==================== 8. 列表初始化 (方便造树) ====================
// 允许你这样写：Trie t{"hello", "world"};
Trie::Trie(std::initializer_list<std::string> list) {
    root = new Node(); // 先造个根
    for (const std::string& word : list) {
        insert(word); // 把列表里的词一个个存进去
    }
}

// ==================== 9. 赋值运算符 (Copy Assignment) ====================
// 处理 tree1 = tree2
Trie& Trie::operator=(const Trie& other) {
    if (this == &other) return *this; // 防止自己赋值给自己

    // 1. 先把自己原来的旧树拆了
    delete root; 
    
    // 2. 再克隆一份新的
    root = cloneHelper(other.root);
    
    return *this;
}

// ==================== 10. 移动赋值 (Move Assignment) ====================
// 处理 tree1 = std::move(tree2)
Trie& Trie::operator=(Trie&& other) {
    if (this == &other) return *this;

    // 1. 先拆自己的旧家
    delete root;

    // 2. 抢别人的房子
    root = other.root;

    // 3. 让别人流浪
    other.root = nullptr;

    return *this;
}
// ==================== 11. 快捷查找 (Function Object) ====================
bool Trie::operator()(const std::string& query) const {
    return search(query); // 偷懒，直接调用写好的 search
}

// ==================== 12. 输入操作符 (>>) ====================
// 允许: cin >> myTrie;
// std::istream& operator>>(std::istream& is, Trie& trie) {
//     std::string word;
//     // 从输入流里读一个单词
//     if (is >> word) {
//         trie.insert(word); // 塞进树里
//     }
//     return is;
// }

// ==================== 修正后的 Trie 输入操作符 ====================
std::istream& operator>>(std::istream& is, Trie& trie) {
    std::string word;
    // 修正：用 while 循环，贪婪地读完所有单词
    while (is >> word) {
        trie.insert(word); 
    }
    return is;
}


// ==================== 13. 输出操作符 (<<) 辅助函数 ====================
// 这是一个递归函数：带着当前的拼图碎片 (str)，在树里到处跑，看到红旗就打印
void printHelper(Trie::Node* node, std::string str, std::ostream& os) {
    if (node == nullptr) return;

    // 如果当前节点有红旗，说明拼出了一个完整的词，打印出来！
    if (node->is_finished) {
        os << str << " "; 
    }

    // 继续往下找孩子，拼图越来越长
    for (int i = 0; i < 26; ++i) {
        if (node->children[i] != nullptr) {
            // str + char(...) 是把下一个字母拼上去
            // 'a' + i 就是算出那个字母是啥
            printHelper(node->children[i], str + char('a' + i), os);
        }
    }
}

// ==================== 14. 输出操作符 (<<) 主函数 ====================
// 允许: cout << myTrie;
std::ostream& operator<<(std::ostream& os, const Trie& trie) {
    // 调用辅助函数，从根节点开始，初始字符串是空的 ""
    printHelper(trie.root, "", os);
    return os;
}
// ========== 秘密辅助函数：收集树里所有的单词 ==========
// 它的逻辑和 printHelper 几乎一样，只是把打印改成了存进 vector
// 记得确认头文件里有没有 vector

void getAllWords(Trie::Node* node, std::string current_str, std::vector<std::string>& words) {
    if (node == nullptr) return;

    if (node->is_finished) {
        words.push_back(current_str); // 找到一个词，存起来
    }

    for (int i = 0; i < 26; ++i) {
        if (node->children[i] != nullptr) {
            getAllWords(node->children[i], current_str + char('a' + i), words);
        }
    }
}

// ========== 秘密辅助函数：比较两棵树是否完全一样 ==========
bool compareNodes(Trie::Node* n1, Trie::Node* n2) {
    // 1. 如果两个都空，那是一样的
    if (n1 == nullptr && n2 == nullptr) return true;
    
    // 2. 如果一个空一个不空，那肯定不一样
    if (n1 == nullptr || n2 == nullptr) return false;

    // 3. 如果标记不一样（一个是单词结尾，一个不是），那也不一样
    if (n1->is_finished != n2->is_finished) return false;

    // 4. 递归检查 26 个孩子
    for (int i = 0; i < 26; ++i) {
        if (!compareNodes(n1->children[i], n2->children[i])) {
            return false; // 只要有一个孩子不一样，整棵树就不一样
        }
    }
    return true; // 完美的克隆体
}
// ==================== 15. 加法赋值 (+=) ====================
// 逻辑：把 other 里的词全部 insert 进我自己
Trie& Trie::operator+=(const Trie& other) {
    std::vector<std::string> words;
    getAllWords(other.root, "", words); // 1. 让间谍去偷 other 的单词表
    
    for (const std::string& word : words) {
        insert(word); // 2. 把偷来的单词一个个存进我自己这里
    }
    return *this;
}

// ==================== 16. 加法 (+) ====================
// 逻辑：创建一个新的，包含我们俩的所有单词
Trie Trie::operator+(const Trie& other) const {
    Trie result = *this; // 1. 先复印一份我自己 (调用拷贝构造)
    result += other;     // 2. 把 other 加进去 (调用刚才写的 +=)
    return result;
}

// ==================== 17. 减法赋值 (-=) ====================
// 逻辑：如果 other 里有某个词，我就把它删掉
Trie& Trie::operator-=(const Trie& other) {
    std::vector<std::string> words;
    getAllWords(other.root, "", words); // 1. 偷单词表
    
    for (const std::string& word : words) {
        remove(word); // 2. 只要它有，我就删 (如果没有 remove 会自动忽略)
    }
    return *this;
}

// ==================== 18. 减法 (-) ====================
Trie Trie::operator-(const Trie& other) const {
    Trie result = *this; // 1. 复印我自己
    result -= other;     // 2. 删掉 other 里的词
    return result;
}

// ==================== 19. 判断相等 (==) ====================
bool Trie::operator==(const Trie& other) const {
    return compareNodes(root, other.root); // 调用那个递归比较的辅助函数
}

// ==================== 20. 判断不等 (!=) ====================
bool Trie::operator!=(const Trie& other) const {
    return !(*this == other); // 只要不是相等，就是不等
}
