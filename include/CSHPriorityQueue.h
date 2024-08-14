#include <iostream>
#include <vector>
#include <deque>
#include <stdexcept>
#include <sstream>
#include <string>

template <typename T, typename Container = std::vector<T>>
class CSHPriorityQueue {
private:
    Container data;
    
    // 辅助函数：向上调整元素以维护堆性质
    void heapifyUp() {
        int index = data.size() - 1;
        while (index > 0) {
            int parentIndex = (index - 1) / 2;
            if (data[index] > data[parentIndex]) {
                std::swap(data[index], data[parentIndex]);
                index = parentIndex;
            } else {
                break;
            }
        }
    }
    
    // 辅助函数：向下调整元素以维护堆性质
    void heapifyDown() {
        int index = 0;
        int size = data.size();
        while (true) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;
            
            if (leftChild < size && data[leftChild] > data[largest]) {
                largest = leftChild;
            }
            
            if (rightChild < size && data[rightChild] > data[largest]) {
                largest = rightChild;
            }
            
            if (largest != index) {
                std::swap(data[index], data[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }
    
public:
    CSHPriorityQueue() {}
    
    CSHPriorityQueue(const Container& c) : data(c) {
        // 将底层容器转化为堆
        int size = data.size();
        for (int i = (size / 2) - 1; i >= 0; --i) {
            heapifyDown();
        }
    }
    
    void push(const T& value) {
        data.push_back(value);
        heapifyUp();
    }
    
    void pop() {
        if (!empty()) {
            std::swap(data[0], data[data.size() - 1]);
            data.pop_back();
            heapifyDown();
        } else {
            throw std::runtime_error("Priority queue is empty.");
        }
    }
    
    T& top() {
        if (!empty()) {
            return data[0];
        } else {
            throw std::runtime_error("Priority queue is empty.");
        }
    }
    
    bool empty() const {
        return data.empty();
    }
    
    size_t size() const {
        return data.size();
    }
};

