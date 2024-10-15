/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Implement an LFU (Least Frequently Used) cache. It should be able to be initialized with a cache size n, and contain the following methods:

    set(key, value): sets key to value. If there are already n items in the cache and we are adding a new item, then it should also remove the least frequently used item. If there is a tie, then the least recently used key should be removed.
    get(key): gets the value at key. If no such key exists, return null.

Each operation should run in O(1) time.
*/

#include <gtest/gtest.h>
#include <deque>
#include <memory>

using namespace std;

/**
 * Idea:
 * We use a hashmap to map between key and value, also, we store a value representing the access count.
 * We have a double linked list storing reference to a queue and two counter. One counter for the occurence, another counter for the access number.
 * Each element of the linked list is identified and ordered by their occurence counter.
 * The queue is used to store the access history by key. So we can pop the last element to get the oldest key. Each time
 * we access a value, the occurence change, we need to get the key out of the queue. To do this, we can use the last access
 * counter and the element access counter to know how much access was performed since the element insertion (and so, it's index in the list)
 * Finally, a hashmap is used to map the occurences with the linked list elements by occurence.
 *
 * Let's say key and value are ints
 */

template <class KeyType>
class DoubleLinkedNode
{
    size_t access_count{0};
    size_t last_access_count{0};
    deque<KeyType> history;

public:
    shared_ptr<DoubleLinkedNode<KeyType>> prev{nullptr};
    shared_ptr<DoubleLinkedNode<KeyType>> next{nullptr};

    size_t push(KeyType k)
    {
        size_t a_c = access_count;
        history.push_back(k);
        access_count++;
        return a_c;
    }
    KeyType pop()
    {
        KeyType k = history.back();
        history.pop_back();
        return k;
    }
};

template <class ValueType>
struct LFUVal
{
    ValueType v;
    size_t last_access_count{0};

    LFUVal(ValueType val, size_t l_a_c) : v(val), last_access_count(l_a_c) {}
};

template <class KeyType, class ValueType>
class LFU
{
private:
    unordered_map<KeyType, LFUVal<ValueType>> k_v;
    unordered_map<size_t, shared_ptr<DoubleLinkedNode<KeyType>>> occ_node;
    shared_ptr<DoubleLinkedNode<KeyType>> node_head;
    size_t max_size;

public:
    LFU(size_t s) : max_size(s) {}
    void set(KeyType k, ValueType v)
    {
        // If the key already exists, just change the value
        if (k_v.find(k) != k_v.end())
        {
            k_v[k].v = v;
            return;
        }

        auto pointer = occ_node.find(0);
        if (pointer == occ_node.end())
        {
            shared_ptr<DoubleLinkedNode<KeyType>> ptr = make_shared<DoubleLinkedNode<KeyType>>();
            occ_node[0] = ptr;
            if (node_head != nullptr)
            {
                node_head->prev = ptr;
                ptr->next = node_head;
            }
            node_head = ptr;
        }
        size_t a_c = pointer->push(k);
        k_v.insert({k, LFUVal<ValueType>(v, a_c)});

        // If we reached the max size, pop an element
        if (k_v.size() >= max_size)
        {
            KeyType k_to_del = node_head->pop();
        }
    }
    void get(KeyType k) {

    }
};

TEST(LFU, lfu)
{
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
