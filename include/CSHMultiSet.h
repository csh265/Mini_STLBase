#include <cstddef>
#include <iostream>
#include <sstream>
#include <string>
#include "CSHRedBlackTree.h"

template <typename Key> class CSHMultiSet {
    CSHRedBlackTree<Key, size_t> cshrbTree;
    size_t sz;
    
public:
    CSHMultiSet() : sz(0) {} // 构造函数
    ~CSHMultiSet() {}        // 析构函数
    
    // 插入元素
    void insert(const Key &key) {
        auto count = cshrbTree.at(key);
        if (count != nullptr) {
            (*count)++;
            sz++;
            return;
        }
        cshrbTree.insert(key, 1);
        sz++;
    }
    
    // 移除所有键为 key 的 value
    void erase(const Key &key) {
        auto count = cshrbTree.at(key);
        if (count == nullptr) {
            return;
        }
        sz -= (*count);
        cshrbTree.remove(key);
    }
    
    // 返回容器中元素的数量
    size_t size() const { return sz; }
    
    // 判断容器是否为空
    bool empty() const { return sz == 0; }
    
    // 返回在 CSHMultiSet 中等于给定值的元素的数量
    size_t count(const Key &key) {
        auto num = cshrbTree.at(key);
        if (num != nullptr) {
            return *num;
        }
        
        return 0;
    }
    
    void clear() {
        sz = 0;
        cshrbTree.clear();
    }
};

