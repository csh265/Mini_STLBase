#include <iostream>
#include <random>
#include <unordered_set>
#include <sstream>
#include <string>
#include "CSHRedBlackTree.h"

template <typename Key> class CSHSet {
public:
    CSHSet() : CSHrbTree() {}
    
    void insert(const Key &key) { CSHrbTree.insert(key, key); }
    
    void erase(const Key &key) { CSHrbTree.remove(key); }
    
    size_t size() { return CSHrbTree.getSize(); }
    
    bool empty() { return CSHrbTree.empty(); }
    
    bool contains(const Key &key) { return CSHrbTree.at(key) != nullptr; }
    
private:
    CSHRedBlackTree<Key, Key> CSHrbTree;
};

