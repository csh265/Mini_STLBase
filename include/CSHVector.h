#include<iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <stdexcept>

template <typename T>
class CSHvector
{
private:
    T *elements;//指向动态数组的指针
    size_t capacity;//数组的容量
    size_t size; //数组中元素的个数
    
    //扩容数组的数量
	void reserve(size_t newcapacity)
    {
        if(newcapacity>capacity)
        {
            T *newelements = new T[newcapacity];
            std::copy(elements,elements+size,newelements);
            delete[] elements;
            elements=newelements;
            capacity=newcapacity;
        }
    }
public:
	CSHvector(): elements(nullptr),capacity(0),size(0){}//构造函数
    
    //拷贝构造函数
    CSHvector(const CSHvector &other):capacity(other.capacity),size(other.size)
    {
        elements = new T[capacity];
        std::copy(other.elements,other.elements+size,elements);//这一步的作用
    }
    
    
    //拷贝赋值操作符，确保在赋值操作过程中不会对自身对象进行无效或不必要的操作
    CSHvector &operator=(const CSHvector& other)
    {
        if(this != &other)
        {
            delete[] elements;//为什么要先删除
            capacity=other.capacity;
            size=other.size;
            elements=new T[capacity];
            std::copy(other.elements,other,elements+size,elements);
            
        }
        return *this;
    }
    
    //添加元素到容器末尾
    void push_back(const T &element)
    {
        if(size==capacity)
        {
            //如果数组已满，则扩容，容器扩容一般为原数组的两倍
            reserve(capacity==0?1:2*capacity);
        }
        elements[size++]=element;//为何是size++,不应该直接size吗
    }
    
    //获取元素的大小
    size_t getSize() const
    {
        return size;
    }
    
    //获取容器的容量
    size_t getCapacity() const//为何需要const
    {
        return capacity;
    }
    /*
    //访问指定索引处的元素
    int getIndex(int index) const
    {
        if(index >=0 && index < size)
        {
            return data[index];
        }
        else
        {
            return -1;//未检测到索引
        }
    }
    */
    // 访问数组中的元素
    T &operator[](size_t index)
    {
        // 检查索引是否越界
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }
    /*
    //指定位置插入元素
    void insert(size_t index,size_t element)
    {
        if(index >= 0 && index <= size)//这里加入<=是因为末尾也可以加入元素
        {
            if(index == size)
            {
                push_back(element);//加入的元素直接在末尾。就用push()
            }
            else
            {
                push_back(elements[size-1]);//不在末尾的话，需要扩增，将末尾元素再扩一次
                for(size_t i=size-2;i>index;i--)
                {
                    elements[i]=elements[i-1];
                }
                elements[index]=element;
                
            }
            size++;
        }
        else
        {
            //std::cerr<<"Index out of range"<<std::endl;//索引超出范围，函数是void型，无返回值
            throw std::out_of_range("Index out of range");//这一步什么意思
        }
    }
    */
    void insert(size_t index, T element)
    {
        if(index >= 0 && index <= size) // 确保索引在有效范围内
        {
            if(size == capacity) // 容量不足时扩容
            {
                reserve(capacity == 0 ? 1 : 2 * capacity);
            }
            if(index == size) // 插入到末尾
            {
                elements[size++] = element;
            }
            else
            {
                // 将末尾元素移到末尾
                for(size_t i = size; i > index; --i)
                {
                    elements[i] = elements[i - 1];
                }
                elements[index] = element;
                size++;
            }
        }
        else
        {
            throw std::out_of_range("Index out of range"); // 索引超出范围
        }
    }
    
    
    //删除末尾元素
    void pop_back()
    {
        if(size>0)
        {
            size--;//这样只是索引减小，实际上数值还在，如何操作可以把数值也清空
        }
    }
    
    //删除指定索引的元素
    
    void popIndex(size_t index)
    {
        if(index>=0 && index <  size)
        {
            for(size_t i=index;i<size-1;i++)
            {
                elements[i]=elements[i+1];
            }
            size--;//删除指定元素的索引后，需要清除末尾元素
        }
        else
        {
            std::cerr<<"Index out of range"<<std::endl;
        }
    }
    
    //清空容器
    void clear()
    {
        //原容器实现
        //data.clear();
        /*if(size)
        {
            for(int i=0;i<size;i++)
            {
                pop_back();
            }
        }
        */
        size = 0;
    }
    
    //使用迭代器遍历数组的开始位置
    T *begin()
    {
        return elements;
    }
    
    //使用迭代器遍历数组的结束位置
    T *end()
    {
        return elements+size;
    }
    
    /*// 使用迭代器遍历数组的开始位置（const版本）
    const T *begin() const
{
    return elements;
    }
    
    // 使用迭代器遍历数组的结束位置（const版本）
    const T *end() const
{
    return elements + size;
    }*/
    //打印元素
    
    void print() const
    {
        for(size_t i=0;i<size;i++)
        {
            std::cout<<elements[i]<<" ";
        }
        std::cout<<std::endl;


    }
    
    //析构函数
    ~CSHvector()
    {
        delete[] elements;
    }
    
};

