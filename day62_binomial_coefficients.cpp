/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

There is an N by M matrix of zeroes. Given N and M, write a function to count the number of ways of starting at the top-left corner and getting to the bottom-right corner. You can only move right or down.

For example, given a 2 by 2 matrix, you should return 2, since there are two ways to get to the bottom-right:

    Right, then down
    Down, then right

Given a 5 by 5 matrix, there are 70 ways to get to the bottom-right.
*/

/**
 * Idea: This looks like a dp problem. Starting from a cell i, j you can either go on the left or on the right.
 * So you can sum each possibilities starting from the last cell
 * 
 * For this kind of problem, I also think that there is a mathematical formula giving the size in o(1)
 * It was pretty easy to see the dp solution so I will give a try finding the formula
 * 
 * After finding myself the results for n=m=1 to n=m=5 I couldn't see. Typing the sequence on internet gave me this
 * http://www.nextnumber.com/show?A which is "The central binomial coefficients" the formula is
 * (2n)! / (n!)²
 * 
 * There is also a general formula for "general binomial coefficients" which is "n choose m"
 */

#include <gtest/gtest.h>

using namespace std;

TEST(BIN_COEF, bin_coef)
{
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}