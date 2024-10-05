/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

Given a 2D matrix of characters and a target word, write a function that returns whether the word can be found in the matrix by going left-to-right, or up-to-down.

For example, given the following matrix:

[['F', 'A', 'C', 'I'],
 ['O', 'B', 'Q', 'P'],
 ['A', 'N', 'O', 'B'],
 ['M', 'A', 'S', 'S']]

and the target word 'FOAM', you should return true, since it's the leftmost column. Similarly, given the target word 'MASS', you should return true, since it's the last row.
*/

/**
 * Idea: This problem can be solved using the KMP search algo
 * Considere each line and column as a string and perform a pattern search in it
 * 
 * As it was noted "easy" I suppose that we should go for the naive approach here
 */

#include <gtest/gtest.h>

using namespace std;

TEST(KMP, kmp)
{
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}