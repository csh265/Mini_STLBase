#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <list>
#include <utility>
#include <vector>
#include <sstream>
#include <string>

template <typename Key, typename Value, typename Hash = std::hash<Key>>
class CSHHashTable
{
    class HashNode {
    public:
        Key key;
        Value value;
        // 从Key构造节点，Value使用默认构造,前面explicit的用处
        explicit HashNode(const Key &key):key(key),value(){}
        
        //为何里面还需const Key &key，不是已经key(key)了吗
        HashNode(const Key &key,const Value &value):key(key),value(value){}
        
        //比较符重载，只按照key进行比较
        bool operator==(const HashNode &other) const {return key==other.key;}
        bool operator!=(const HashNode &other) const {return key!=other.key;}
        bool operator<(const HashNode &other) const {return key<other.key;}
        bool operator>(const HashNode &other) const {return key>other.key;}
        
        bool operator==(const Key &key_) const { return key == key_; }//有两次重载
        
        void print() const
        {
            std::cout<<key<<" "<<value<<" ";
        }  
    };
private:
    using Bucket = std::list<HashNode>; // 定义桶的类型为存储键的链表,这个的用法
    std::vector<Bucket> buckets;        // 存储所有桶的动态数组
    Hash hashFunction;                  // 哈希函数对象
    size_t tableSize;                   // 哈希表的大小，即桶的数量
    size_t numElements;                 // 哈希表中元素的数量
    
    float maxLoadFactor = 0.75; // 默认的最大负载因子
    
    // 计算键的哈希值，并将其映射到桶的索引
    size_t hash(const Key &key) const {return hashFunction(key) % tableSize;}
    
    
   //***************** 
    // 当元素数量超过最大负载因子定义的容量时，增加桶的数量并重新分配所有键
    void rehash(size_t newSize)
    {
        std::vector<Bucket>newBuckets(newSize);//创建新的桶数组
        for(auto &bucket:buckets)//遍历旧桶
        {
            for(HashNode &hashNode:bucket)//遍历桶中的每个键
            {
                size_t newIndex = hashFunction(hashNode.key) % newSize; // 为键计算新的索引
                newBuckets[newIndex].push_back(hashNode); // 将键添加到新桶中
            }
        }
        buckets=std::move(newBuckets);//使用move语义更新数组。move语义的用法
        tableSize=newSize;
        
    }
public:
    // 构造函数初始化哈希表.....为什么是这几个变量
    CSHHashTable(size_t size = 10, const Hash &hashFunc = Hash()): buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {}
    
    //插入键到哈希表中
    void insert(const Key &key,const Value &value)
    {
        if(numElements+1>maxLoadFactor*tableSize)//检查是否需要重哈希
        {
            //处理clear后再次插入元素使，tablesize=0的情况
            if(tableSize==0)tableSize=1;
            rehash((tableSize*2));//重哈希，桶数量翻倍
        }
        
        size_t index = hash(key);//计算键的索引
        std::list<HashNode>&bucket = buckets[index];//获取对应的桶
        
        //如果键不在桶中，则添加到桶中
        if(std::find(bucket.begin(), bucket.end(),key)== bucket.end())
        {
            bucket.push_back(HashNode(key,value));
            ++numElements;//增加元素的数量
        }
    }
    
    //这一步干什么的
    void insertKey(const Key &key)
    {
        insert(key,Value{});//为何Value{}
    }
    
    //从哈希表中移除键
    void erase(const Key &key)
    {
        size_t index = hash(key);//计算键的索引
        Bucket &bucket=buckets[index];//获取对应的桶
        auto it = std::find(bucket.begin(),bucket.end(),key);//查找键//it不是hashNode,想想是什么类型
        if(it!=bucket.end())
        {
            bucket.erase(it);//从桶中删除
            numElements--;//j减少元素数量
        }
    }
    
    //查找键是否存在于哈希表中// find前为何要加*号，是表示迭代器吗
    Value *find(const Key &key)
    {
        size_t index=hash(key);
        auto &bucket=buckets[index];
        auto it=std::find(bucket.begin(),bucket.end(),key);//这个std::find用的哪个库的
        if(it!=bucket.end())
        {
            return &it->value;//可以it->value吗
        }
        return nullptr;//未找到则返回空
    }
    
    //获取哈希表中元素的数量
    size_t size()const//这个加const是为了防止num改变吗
    {
        return numElements;
    }
    
    //打印哈希表中的所有元素
    void print()const
    {
        for(size_t i=0;i<buckets.size();i++)
        {
            for(const HashNode &element:buckets[i])\
            {
                element.print();
            }
        }
        std::cout<<std::endl;
    }
    
    //和案例不一样，没加this
    void clear()
    {
        buckets.clear();
        numElements=0;
        tableSize=0;
    }
};

int main() {
    // 创建一个哈希表实例
    CSHHashTable<int, int> hashTable;
    
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
            hashTable.insert(key, value);
        }
        
        if (command == "erase") {
            if (hashTable.size() == 0) {
                continue;
            }
            iss >> key;
            hashTable.erase(key);
        }
        
        if (command == "find") {
            if (hashTable.size() == 0) {
                std::cout << "not exist" << std::endl;
                continue;
            }
            iss >> key;
            int* res = hashTable.find(key);
            if (res != nullptr) {
                std::cout << *res << std::endl;
            } else {
                std::cout << "not exist" << std::endl;
            }
        }
        
        if (command == "print") {
            if (hashTable.size() == 0) {
                std::cout << "empty" << std::endl;
            } else {
                hashTable.print();
            }
        }
        
        if (command == "size") {
            std::cout << hashTable.size() << std::endl;
        }
        
        if (command == "clear") {
            hashTable.clear();
        }
    }
    return 0;
}
