/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given two singly linked lists that intersect at some point, find the intersecting node. The lists are non-cyclical.

For example, given A = 3 -> 7 -> 8 -> 10 and B = 99 -> 1 -> 8 -> 10, return the node with value 8.

In this example, assume nodes with the same value are the exact same node objects.

Do this in O(M + N) time (where M and N are the lengths of the lists) and constant space.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: What I did not understood at the first read was that intersecting means becoming the same list. Which
 * means that the last element has to be in common with the two lists for sure.
 * From this point we just have to get both list size and use the minimum length to align the longest list
 * with the shortest one. At this point we just need to compare object memory address
 */

TEST(LIST_LEN, list_len)
{
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
