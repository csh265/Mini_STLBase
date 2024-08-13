
#include<iostream>
#include <stdexcept>
#include <sstream>
#include "cshList.h"
template<typename T>
class CSHList
{

  
private:
    struct Node
    {
        T val;
        Node *next;
        Node *prev;
        
        //构造函数
        Node(const T &value,Node *nextNode=nullptr,Node *prevNode=nullptr)
            :val(value),next(nextNode),prev(prevNode){}
    };
    Node *head;//头结点指针
    Node *tail;//尾结点指针
    size_t size;//链表中节点的数量
public:
    //template <typename L>//不要分号
    //friend std::ostream &operator<<(std::ostream &os,const CSHList<L> &pt);没必要存在，用不到这个重载
    //构造函数
    CSHList(): head(nullptr),tail(nullptr),size(0){}
    //析构函数
    ~CSHList(){clear();}
    
    //链表末尾增加元素
    void push_back(const T &value)
    {
        //创建新的节点
        Node *newNode=new Node(value,nullptr,tail);//前一个节点是尾结点，所以prevNode=tail
        if(tail)
        {
            //如果链表非空，将尾结点的next指针指向新的节点
            tail->next=newNode;
        }
        else
        {
            //如果链表为空，意味着头结点也是空，新节点即为新的头结点
            head=newNode;
        }
        //末尾加入新节点后，需更新尾结点和链表大小
        tail = newNode;
        size++;
    }
    
    //在链表开头加入新元素
    void push_front(const T &value)
    {
        Node *newNode=new Node(value,head,nullptr);//下一个节点是头结点，所以nextNode=tail
        if(head)
        {
            //newNode->next=head;
            head->prev=newNode;
        }
        else
        {

            tail=newNode;
        }
        head=newNode;
        size++;
        
    }
    
    //获取链表中节点的数量
    size_t getSize() const
    {
        return size;
    }
    /*
    //访问链表中的元素
    T &operator[](size_t index)
    {
        Node *current=head;
        if(index>=size) throw std::out_of_range("Index out of range");//如果index超出链表长度
        while(index>=0)
        {
            current=current->next;
            index--;
        }
        return current->val;
    }*/
    
    //访问链表中的元素
    const T &operator[](size_t index) const//操作符[]的重载
    {
        Node *current=head;
        if(index>=size) throw std::out_of_range("Index out of range");//如果index超出链表长度
        while(index>0)
        {
            current=current->next;
            index--;
        }
        return current->val;
    }
    
    //删除链表末尾的元素
    void pop_back()
    {
        if(tail)
        {
            Node *newtail=tail->prev;
            delete tail;//这个地方不是删除了吗，后面为何还能tail复制，这一步不用也可吧
            tail=newtail;//这个地方不需要删除newtail吗、
            //如果只有一个节点，删除后，头结点为空
            if(tail)
            {
                tail->next=nullptr;
            }
            else
            {
                head=nullptr;//这个地方置空的话，head会成为野指针，仍然指向已经释放的内存
            }
            size--;
        }
        
    }
    
    //删除链表开头的元素
    void pop_front()
    {
        if(head)
        {
            Node *newhead=head->next;
            delete head;
            head=newhead;
            if(head)
            {
                head->prev=nullptr;
            }
            else
            {
                tail=nullptr;
            }
            size--;
        }
    }
    
    //获取指定值的节点
    Node *getNode(T &value)//Node *getNode(const T &val)感觉不需要const
    {
        Node *curret=head;
        while(curret!=nullptr&&curret->val!=value)
        {
            curret=curret->next;
        }
        return curret;
    }
    
    //删除指定值的节点
    void remove(T &value)
    {
        Node *current=head;
        while(current!=nullptr && current->val!=value)
        {
            current=current->next;
        }
        if(current == nullptr)
        {
            return;
        }
        else if(current != head && current != tail)
        {
            current->prev->next=current->next;
            current->next->prev=current->prev;

        }
        else if (current == head && current == tail)
        {
            // 既是头结点也是尾结点
            current = nullptr;
            current = nullptr;
        }
        else if (current == head)
        {
            // 是头结点
            current = current->next;
            current->prev = nullptr;
        }
        else
        {
            // 是尾结点
            tail = current->prev;
            tail->next = nullptr;
        }
        size--;
        delete current;
        current=nullptr;//避免野指针
    }
    //判断链表是否为空
    bool empty()
    {
        return size==0;
    }
    
    //清空链表
    void clear()
    {
        while(head)
        {
            Node *temp=head;
            head=head->next;
            delete temp;
        }
        //head不需要nullptr吗
        tail=nullptr;
        size=0;
    }
    
    //使用迭代器遍历链表的开始位置
    Node *begin()
    {
        return head;
    }
    
    // 使用迭代器遍历链表的结束位置
    Node *end()
    { 
        return nullptr;
    }
    
    //打印链表中的元素
    
    void print() const
    {
        Node *current=head;
        while(current!=nullptr)
        {
            std::cout<<current->val<<" ";
            current=current->next;
        }
        std::cout<<std::endl;
    }
};
/*
int main() {
    // 创建一个 List 对象
    CSHList<int> CSHlist;
    
    int N;
    std::cin >> N;


    for (int i = 0; i < N; i++) {
        std::string command;
        std::cin >> command;
        int value;
        
        if (command == "push_back") {
            std::cin >> value;
            CSHlist.push_back(value);
            CSHlist.print();
        }
        
        if (command == "push_front") {
            std::cin >> value;
            CSHlist.push_front(value);
            CSHlist.print();
        }
        
        if (command == "pop_back") {
            CSHlist.pop_back();
            CSHlist.print();
        }
        
        if (command == "pop_front") {
            CSHlist.pop_front();
            CSHlist.print();
        }
        
        if (command == "remove") {
            std::cin >> value;
            CSHlist.remove(value);
            CSHlist.print();
        }
        
        if (command == "clear") {
            CSHlist.clear();
            CSHlist.print();
        }
        
        if (command == "size") {
            std::cout << CSHlist.getSize() << std::endl;
        }
        
        if (command == "get") {
            std::cin >> value;
            std::cout << CSHlist[value] << std::endl;
        }
        
        if (command == "print") {
            if (CSHlist.getSize() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                CSHlist.print();
            }
        }
    }
    return 0;
}
*/
