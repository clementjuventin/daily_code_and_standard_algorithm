/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

An XOR linked list is a more memory efficient doubly linked list. Instead of each node holding next and prev fields, it holds a field named both, which is an XOR of the next node and the previous node. Implement an XOR linked list; it has an add(element) which adds the element to the end, and a get(index) which returns the node at index.

If using a language that has no pointers (such as Python), you can assume you have access to get_pointer and dereference_pointer functions that converts between nodes and memory addresses.x
*/

#include <gtest/gtest.h>
#include <stdexcept>

using namespace std;

template <class T>
class XORLinkedListNode
{
public:
    XORLinkedListNode<T> *both;
    T value;
};

template <class T>
class XORLinkedList
{
private:
    XORLinkedListNode<T> *head = nullptr;
    XORLinkedListNode<T> *tail = nullptr;

    T get(XORLinkedListNode<T> *previous, XORLinkedListNode<T> *current, int index)
    {
        if (index == 0)
            return current->value;

        if (current == this->tail)
            throw out_of_range("Index out of range");

        XORLinkedListNode<T> *next = this->XOR(current->both, previous);
        return this->get(current, next, index - 1);
    }

    XORLinkedListNode<T> *XOR(XORLinkedListNode<T> *a, XORLinkedListNode<T> *b)
    {
        uintptr_t a_uintptr = reinterpret_cast<uintptr_t>(a);
        uintptr_t b_uintptr = reinterpret_cast<uintptr_t>(b);
        uintptr_t a_xor_b_uintptr = a_uintptr ^ b_uintptr;
        XORLinkedListNode<T> *result = reinterpret_cast<XORLinkedListNode<T> *>(a_xor_b_uintptr);
        return result;
    }

public:
    void add(T element)
    {
        XORLinkedListNode<T> *node = new XORLinkedListNode<T>();
        node->value = element;

        if (this->head == nullptr)
        {
            this->head = node;
            this->tail = node;
            node->both = nullptr;
        }
        else
        {
            this->tail->both = this->XOR(this->tail->both, node);
            node->both = this->tail;
            this->tail = node;
        }
    }

    T get(int index)
    {
        if (head == nullptr)
            throw out_of_range("No element in the list");
        if (index == 0)
            return this->head->value;
        else
            return this->get(this->head, this->head->both, index - 1);
    }
};

TEST(XOR_LINKED_LIST, XORLinkedList)
{
    XORLinkedList<int> *linked_list = new XORLinkedList<int>();

    EXPECT_THROW(linked_list->get(0), out_of_range);

    linked_list->add(1);
    linked_list->add(2);

    EXPECT_EQ(linked_list->get(0), 1);
    EXPECT_EQ(linked_list->get(1), 2);
    EXPECT_THROW(linked_list->get(2), out_of_range);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
