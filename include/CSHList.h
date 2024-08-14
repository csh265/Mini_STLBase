#pragma once // 防止头文件重复包含
#include <iostream>
#include <stdexcept>

template<typename T>
class CSHList
{
private:
    struct Node
    {
        T val;
        Node* next;
        Node* prev;

        Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
            : val(value), next(nextNode), prev(prevNode) {}
    };
    Node* head;
    Node* tail;
    size_t size;
public:
    CSHList(): head(nullptr), tail(nullptr), size(0) {}
    ~CSHList();

    void push_back(const T& value);
    void push_front(const T& value);
    size_t getSize() const;
    const T& operator[](size_t index) const;
    void pop_back();
    void pop_front();
    Node* getNode(const T& value);
    void remove(const T& value);
    bool empty() const;
    void clear();
    Node* begin();
    Node* end();
    void print() const;
};


