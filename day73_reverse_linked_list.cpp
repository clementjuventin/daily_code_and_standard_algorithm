/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given the head of a singly linked list, reverse it in-place.
*/

#include <gtest/gtest.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Idea:
 */
ListNode *reverseList(ListNode *head)
{
    ListNode *prev = nullptr;
    ListNode *current = head;
    ListNode *next = nullptr;

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

TEST(REVERSE_LINKED_LIST, reverse_linked_list)
{
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
