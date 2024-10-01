/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given a singly linked list and an integer k, remove the kth last element from the list. k is guaranteed to be smaller than the length of the list.

The list is very long, so making more than one pass is prohibitively expensive.

Do this in constant space and in one pass.
*/

#include <gtest/gtest.h>

using namespace std;

template <class T>
class LinkedNode
{
public:
    LinkedNode<T> *next = nullptr;
    T value = 0;
};

/**
 * Idea: I did a similar challenge on leetcode yesturday. In my opinion here the best solution is to iterate until we
 * reach the kth element of the list while always keeping the previous one. Then remove the kth element
 * TC: o(n)
 * SC: o(1)
 */
LinkedNode<int> * remove_from_list(LinkedNode<int> *head, uint k)
{
    if (head == nullptr)
        return nullptr;
    // Handle the cas where k = 0
    if (k == 0)
    {
        head = head->next;
        return head;
    }
    LinkedNode<int> *previous = head;
    LinkedNode<int> *current = head->next;
    uint cpt = 1;
    while (current != nullptr)
    {
        if (k == cpt)
        {
            previous->next = current->next;
            return head;
        }
        previous = current;
        current = current->next;
        cpt += 1;
    }
    return head;
}

TEST(REMOVE_FROM_LIST, remove_from_list)
{
    LinkedNode<int> node1;
    LinkedNode<int> node2;
    LinkedNode<int> node3;
    node1.next = &node2;
    node2.next = &node3;

    LinkedNode<int> *head = &node1;
    head = remove_from_list(head, 1);
    EXPECT_EQ(head->next, &node3);
    head = remove_from_list(head, 0);
    EXPECT_EQ(head, &node3);
    head = remove_from_list(head, 0);
    EXPECT_EQ(head, nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
