#pragma once
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
        // ��Key����ڵ㣬Valueʹ��Ĭ�Ϲ���
        //explicitȷ����������캯�����ᱻ������ʽ����ת��
        explicit HashNode(const Key& key) :key(key), value() {}

        //Ϊ�����滹��const Key &key�������Ѿ�key(key)����
        //key(key) ��ʾʹ�ù��캯���Ĳ��� key ����ʼ����Ա���� key��
        HashNode(const Key& key, const Value& value) :key(key), value(value) {}

        //�ȽϷ����أ�ֻ����key���бȽ�
        bool operator==(const HashNode& other) const { return key == other.key; }
        bool operator!=(const HashNode& other) const { return key != other.key; }
        bool operator<(const HashNode& other) const { return key < other.key; }
        bool operator>(const HashNode& other) const { return key > other.key; }

        bool operator==(const Key& key_) const { return key == key_; }//����������

        void print() const
        {
            std::cout << key << " " << value << " ";
        }
    };
private:
    using Bucket = std::list<HashNode>; // ����Ͱ������Ϊ�洢��������
    std::vector<Bucket> buckets;        // �洢����Ͱ�Ķ�̬����
    Hash hashFunction;                  // ��ϣ��������
    size_t tableSize;                   // ��ϣ��Ĵ�С����Ͱ������
    size_t numElements;                 // ��ϣ����Ԫ�ص�����

    float maxLoadFactor = 0.75; // Ĭ�ϵ����������

    // ������Ĺ�ϣֵ��������ӳ�䵽Ͱ������
    size_t hash(const Key& key) const { return hashFunction(key) % tableSize; }


    //***************** 
     // ��Ԫ������������������Ӷ��������ʱ������Ͱ�����������·������м�
    void rehash(size_t newSize)
    {
        std::vector<Bucket>newBuckets(newSize);//�����µ�Ͱ����
        for (auto& bucket : buckets)//������Ͱ
        {
            for (HashNode& hashNode : bucket)//����Ͱ�е�ÿ����
            {
                size_t newIndex = hashFunction(hashNode.key) % newSize; // Ϊ�������µ�����
                newBuckets[newIndex].push_back(hashNode); // ������ӵ���Ͱ��
            }
        }
        buckets = std::move(newBuckets);//ʹ��move����������顣move������÷�
        tableSize = newSize;

    }
public:
    // ���캯����ʼ����ϣ��
    CSHHashTable(size_t size = 10, const Hash& hashFunc = Hash()) : buckets(size), hashFunction(hashFunc), tableSize(size), numElements(0) {}

    //���������ϣ����
    void insert(const Key& key, const Value& value)
    {
        if (numElements + 1 > maxLoadFactor * tableSize)//����Ƿ���Ҫ�ع�ϣ
        {
            //����clear���ٴβ���Ԫ��ʹ��tablesize=0�����
            if (tableSize == 0)tableSize = 1;
            rehash((tableSize * 2));//�ع�ϣ��Ͱ��������
        }

        size_t index = hash(key);//�����������
        std::list<HashNode>& bucket = buckets[index];//��ȡ��Ӧ��Ͱ

        //���������Ͱ�У�����ӵ�Ͱ��
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end())
        {
            bucket.push_back(HashNode(key, value));
            ++numElements;//����Ԫ�ص�����
        }
    }

    //��һ�������뵽��ϣ����
    void insertKey(const Key& key)
    {
        insert(key, Value{});//Value{},Ĭ�ϳ�ʼ��
    }

    //�ӹ�ϣ�����Ƴ���
    void erase(const Key& key)
    {
        size_t index = hash(key);//�����������
        Bucket& bucket = buckets[index];//��ȡ��Ӧ��Ͱ
        auto it = std::find(bucket.begin(), bucket.end(), key);//���Ҽ�//it����hashNode,������ʲô����
        if (it != bucket.end())
        {
            bucket.erase(it);//��Ͱ��ɾ��
            numElements--;//j����Ԫ������
        }
    }

    //���Ҽ��Ƿ�����ڹ�ϣ����// findǰΪ��Ҫ��*�ţ��Ǳ�ʾ��������
    Value* find(const Key& key)
    {
        size_t index = hash(key);
        auto& bucket = buckets[index];
        auto it = std::find(bucket.begin(), bucket.end(), key);//���std::find�õ��ĸ����
        if (it != bucket.end())
        {
            return &it->value;//����it->value��
            //it->value �ǺϷ��ģ����ڷ��ʵ�����ָ��� HashNode ����� value ��Ա��
        }
        return nullptr;//δ�ҵ��򷵻ؿ�
    }

    //��ȡ��ϣ����Ԫ�ص�����
    size_t size()const//const��ֹnum�ı�
    {
        return numElements;
    }

    //��ӡ��ϣ���е�����Ԫ��
    void print()const
    {
        for (size_t i = 0; i < buckets.size(); i++)
        {
            for (const HashNode& element : buckets[i])\
            {
                element.print();
            }
        }
        std::cout << std::endl;
    }

    //�Ͱ�����һ����û��this
    void clear()
    {
        buckets.clear();
        numElements = 0;
        tableSize = 0;
    }
};