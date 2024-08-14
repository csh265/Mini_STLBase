#include <cstddef>
#include <iostream>
#include <list>
#include <random>
#include <unordered_set>
#include <sstream>
#include <string>
#include "CSHRedBlackTree.h"


template <typename Key, typename Value> class CSHMultiMap {
public:
    using ValueType = std::list<Value>; // 修改Value的类型为list
    
    CSHMultiMap() : CSHrbTree(), size(0) {}
    
    void insert(const Key &key, const Value &value) {
        // 查找当前键是否已经存在
        ValueType *existingValues = CSHrbTree.at(key);
        if (existingValues) {
            // 如果键已经存在，将值添加到对应的list中
            existingValues->push_back(value);
        } else {
            // 如果键不存在，创建一个新的list并添加值，然后插入到红黑树中
            ValueType values;
            values.push_back(value);
            CSHrbTree.insert(key, values);
        }
        size++;
    }
    
    void remove(const Key &key) {
        // 删除整个键，包括其所有的值
        ValueType *existingValues = CSHrbTree.at(key);
        if (existingValues) {
            size -= existingValues->size();
            CSHrbTree.remove(key);
        }
    }
    
    void remove(const Key &key, const Value &value) {
        // 查找当前键
        ValueType *existingValues = CSHrbTree.at(key);
        if (existingValues) {
            // 删除给定的值
            existingValues->remove(value);
            size--;
            // 如果删除值后list为空，也删除键
            if (existingValues->empty()) {
                CSHrbTree.remove(key);
            }
        }
    }
    
    ValueType *at(const Key &key) {
        // 获取键对应的所有值的列表
        return CSHrbTree.at(key);
    }
    
    int getSize() { return size; }
    
    bool empty() { return size == 0; }
    
private:
    CSHRedBlackTree<Key, ValueType> CSHrbTree; // 使用ValueType作为红黑树的值类型
    size_t size;
};

