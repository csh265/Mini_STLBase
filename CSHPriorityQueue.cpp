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

int main() {
    // 使用 std::vector 作为底层容器
    CSHPriorityQueue<int, std::vector<int>> CSHPriorityQueue;
    
    int N;
    std::cin >> N;
    getchar();
    
    std::string line;
    for (int i = 0; i < N; i++) {
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        
        int element;
        
        if (command == "push") {
            iss >> element;
            CSHPriorityQueue.push(element);
        }
        
        if (command == "pop") {
            try {
                CSHPriorityQueue.pop();
            } catch(const std::runtime_error& e) {
                // 不做任何处理
                continue;
            }
        }
        
        if (command == "top") {
            try {
                std::cout << CSHPriorityQueue.top() << std::endl;
            } catch(const std::runtime_error& e) {
                std::cout << "null" << std::endl;
            }   
        }
        
        if (command == "size") {
            std::cout << CSHPriorityQueue.size() << std::endl;
        }
        
        if (command == "empty") {
            std::cout << (CSHPriorityQueue.empty() ? "true" : "false") << std::endl;
        }
    }
    return 0;
}
