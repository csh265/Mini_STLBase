#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <string>

template<typename T>

class CSHDeque {
private:
    T* elements;//一个循环一维数组
    size_t capacity;//数组的总容量
    size_t frontIndex;  // deque的前端索引
    size_t backIndex;  // deque的后端索引
    size_t size;  // 数组的元素个数
    
    //********************************//
    // 扩展数组容量
    void resize() {
        // 计算新的容量
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        
        // 创建新的数组
        T* newElements = new T[newCapacity];
        
        // 复制元素到新数组
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[index];
            index = (index + 1) % capacity;
        }
        
        // 释放旧数组的内存
        delete[] elements;
        
        // 更新成员变量
        elements = newElements;
        capacity = newCapacity;
        frontIndex = 0;
        backIndex = size;
    }
public:
    CSHDeque():elements(nullptr),capacity(0),frontIndex(0),backIndex(0),size(0) {}
    
    //队列前段插入元素
    void push_front(const T& value)
    {
        //需要先检查是否要扩容
        if(size==capacity)
        {
            resize();
        }
        //计算新的前端索引
        
        //当 frontIndex - 1 计算结果为负数时，+ capacity 确保了这个结果变为正数
        //然后对 capacity 取模可以得到正确的循环索引,确保 frontIndex 始终在 [0, capacity - 1] 范围内。
        frontIndex = (frontIndex - 1 + capacity) % capacity;
        // 在新的前端位置插入元素
        elements[frontIndex] = value;
        // 增加deque的元素数量
        size++;
    }
    
    // 在队列的后端插入元素
    void push_back(const T& value) 
    {
        if (size == capacity) 
        {
            resize();
        }
        
        // 在当前后端位置插入元素
        elements[backIndex] = value;
        
        // 计算新的后端索引
        //当前 backIndex 是 4，队列的下一个插入位置是 (4 + 1) % 5 = 0。
        //%capacity这个操作确保 backIndex 回绕到数组的开头。
        backIndex = (backIndex + 1) % capacity;
        
        // 增加deque的元素数量
        size++;
    }
    
    // 从队列的前端移除元素
    void pop_front() 
    {
        // 检查队列是否为空
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        
        // 删除元素不需要显式地删除, 以后新追加元素会自动覆盖，但是会占用内存，可能导致内存泄漏
        // 计算新的前端索引
        frontIndex = (frontIndex + 1) % capacity;
        size--;
    }
    
    // 从队列的后端移除元素
    void pop_back() 
    {
        if (size == 0) {
            throw std::out_of_range("Deque is empty");
        }
        backIndex = (backIndex - 1 + capacity) % capacity;
        size--;
    }
    
    //*****************************//
    T& operator[](int index)
    {
        if(index<0 || index >= size)
        {
            throw std::out_of_range("index out of range");
        }
        return elements[(frontIndex+index)%capacity];//这个地方[]是正常的运算符，不是类的重载，因为elements不是类
    }
    
    //获取队列大小
    size_t getSize() const
    {
        return size;
    }
    
    // 清空队列
    void clear() 
    {
        frontIndex = 0;
        backIndex = 0;
        size = 0;
    }
    
    // 打印队列中的元素
    void print() const 
    {
        if (size == 0) {
            std::cout << "empty" << std::endl;
            return;
        }
        /*
        size_t index = frontIndex;
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[index] << " ";
            index = (index + 1) % capacity;
        }
        std::cout << std::endl;
        */
        //前段索引可能不为0
        for (size_t i = 0; i < size; ++i) {
            std::cout << elements[(frontIndex + i) % capacity] << " ";
        }
        std::cout << std::endl;
        
    }
    
    ~CSHDeque() 
    {
 
        delete[] elements;
    }

};
/*
int main() 
{
    CSHDeque<int> CSHdeque;
    
    int N;
    std::cin >> N;

    for (int i = 0; i < N; i++) {
        std::string command;
        std::cin >> command;
        int value;
        
        if (command == "push_back") {
            std::cin >> value;
            CSHdeque.push_back(value);
            CSHdeque.print();
        }
        
        if (command == "push_front") {
            std::cin >> value;
            CSHdeque.push_front(value);
        }
        
        if (command == "pop_back") {
            if (CSHdeque.getSize() == 0) {
                continue;
            }
            CSHdeque.pop_back();
        }
        
        if (command == "pop_front") {
            if (CSHdeque.getSize() == 0) {
                continue;
            }
            CSHdeque.pop_front();
        }
        
        if (command == "clear") {
            CSHdeque.clear();
        }
        
        if (command == "size") {
            std::cout << CSHdeque.getSize() << std::endl;
        }
        
        if (command == "get") {
            std::cin >> value;
            std::cout << CSHdeque[value] << std::endl;
        }
        
        if (command == "print") {
            if (CSHdeque.getSize() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                CSHdeque.print();
            }
        }
    }
    return 0;
}
*/