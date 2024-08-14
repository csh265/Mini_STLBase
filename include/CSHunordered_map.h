#include <cstddef>
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>
#include "CSHHashTable.h"

template <typename Key, typename Value> class Unordered_map {
private:
    CSHHashTable<Key, Value> CSHhashtable;
    
public:
    Unordered_map() : CSHhashtable(){};
    
    ~Unordered_map() {}
    
    bool empty() const noexcept { return CSHhashtable.size() == 0; }
    
    size_t size() const noexcept { return CSHhashtable.size(); }
    
    void clear() noexcept { CSHhashtable.clear(); }
    
    void insert(const Key &key, const Value &value) {
        CSHhashtable.insert(key, value);
    }
    
    void erase(const Key &key) { CSHhashtable.erase(key); }
    
    bool find(const Key &key) { return CSHhashtable.find(key) != nullptr; }
    
    Value &operator[](const Key &key) {
        Value *ans = CSHhashtable.find(key);
        if (ans != nullptr) {
            return *ans;
        }
        CSHhashtable.insertKey(key);
        ans = CSHhashtable.find(key);
        return *ans;
    }
};
/*
int main() {
    Unordered_map<int, int> map;
    
    int N;
    std::cin >> N;
    getchar();
    
    std::string line;
    
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        
        int key;
        int value;
        
        if (command == "insert") {
            iss >> key >> value;
            map.insert(key, value);
        }
        
        if (command == "erase") {
            iss >> key;
            map.erase(key);
        }
        
        if (command == "find") {
            iss >> key;
            if (map.find(key)) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        }
        
        // size 命令
        if (command == "size") {
            std::cout << map.size() << std::endl;
        }
        
        // empty 命令
        if (command == "empty") {
            if (map.empty()) {
                std::cout << "true" << std::endl;
            } else {
                std::cout << "false" << std::endl;
            }
        }
    }
    return 0;
}
*/
