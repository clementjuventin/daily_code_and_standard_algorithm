/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Two Sigma.

Using a function rand5() that returns an integer from 1 to 5 (inclusive) with uniform probability, implement a function rand7() that returns an integer from 1 to 7 (inclusive).
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: I suppose we can use the random function instead of making our own pseudo-random number generator
 */

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
