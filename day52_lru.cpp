/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Implement an LRU (Least Recently Used) cache. It should be able to be initialized with a cache size n, and contain the following methods:

    set(key, value): sets key to value. If there are already n items in the cache and we are adding a new item, then it should also remove the least recently used item.
    get(key): gets the value at key. If no such key exists, return null.

Each operation should run in O(1) time.
*/

/**
 * Idea: Use a circular double ended queue for the n values and a pointer on the current element. Also
 * we have a hashmap mapping each value to an address (within the circular queue so we can remove easily)
 * Size of the data doesn't impact the performances (we suppose it's integers here)
 */

#include <gtest/gtest.h>

using namespace std;

template <class T, class U>
class Node
{
public:
    Node *prev;
    Node *next;
    U key;
    T val;
    Node(T v, U k) : val(v), key(k) {}
};

template <class T, class U>
class LRU
{
private:
    size_t capacity{0};
    size_t size{0};
    Node<T, U> *current{nullptr};
    unordered_map<U, Node<T, U> *> values;

public:
    LRU(size_t c) : capacity(c) {}
    ~LRU()
    {
        const size_t s = size - 1;
        for (size_t i = 0; i < s; ++i)
        {
            current = current->next;
            delete current->prev;
        }
        delete current;
    }
    void set(U key, T value)
    {
        if (values.find(key) != values.end())
        {
            values[key]->val = value;
            return;
        }
        if (size == capacity)
        {
            current = current->next;
            values.erase(current->key);
            current->val = value;
            current->key = key;
        }
        else
        {
            size++;
            Node<T, U> *n = new Node(key, value);
            if (current != nullptr)
            {
                n->next = current->next;
                n->prev = current;
                n->next->prev = n;
                current->next = n;
            }
            else
            {
                n->next = n;
                n->prev = n;
            }
            current = n;
        }
        values.insert({key, current});
    }
    T *get(U key)
    {
        if (size == 0 || values.find(key) == values.end())
            return nullptr;
        return &(values[key]->val);
    }
};

TEST(LRU, lru)
{
    LRU<int, int> lru{3};
    int e1{1}, e2{2}, e3{3}, e4{4};
    EXPECT_EQ(lru.get(e1), nullptr);
    lru.set(e1, e1);
    EXPECT_EQ(*lru.get(e1), e1);
    EXPECT_EQ(lru.get(e2), nullptr);
    lru.set(e2, e2);
    EXPECT_EQ(*lru.get(e1), e1);
    EXPECT_EQ(*lru.get(e2), e2);
    lru.set(e1, e2);
    EXPECT_EQ(*lru.get(e1), e2);
    lru.set(e3, e3);
    lru.set(e4, e4);
    EXPECT_EQ(lru.get(e1), nullptr);
    EXPECT_EQ(*lru.get(e3), e3);
    EXPECT_EQ(*lru.get(e4), e4);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
