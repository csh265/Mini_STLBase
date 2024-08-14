#pragma once
#include <cstddef>
#include"CSHHashTable.h"


template <typename Key> class CSHUnordered_set {
public:
    CSHUnordered_set() : cshhashtable() {};

    ~CSHUnordered_set() {}

    bool empty() const noexcept { return cshhashtable.size() == 0; }

    size_t size() const noexcept { return cshhashtable.size(); }

    void clear() noexcept { cshhashtable.clear(); }

    void insert(Key key) { cshhashtable.insertKey(key); }

    void erase(Key key) { cshhashtable.erase(key); }

    bool find(const Key& key) { return cshhashtable.find(key) != nullptr; }

private:
    CSHHashTable<Key, Key> cshhashtable;
};

/*

*/
