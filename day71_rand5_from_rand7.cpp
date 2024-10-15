/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Two Sigma.

Using a function rand7() that returns an integer from 1 to 7 (inclusive) with uniform probability, implement a function rand5() that returns an integer from 1 to 5 (inclusive).
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea:
 * Just reroll if bigger than 5
 * We can also improve this idea to provide solutions for numbers bigger that 7 using multiplications
 * Think about generating a random 100 number using one 10 dice.
 * ex: For 7 it's (rand7() - 1) * 7 + rand7(); and then we check if it's under the first 5 multiple inferior
 * to the max result (45 <= 49) and perform a modulo. 
 */

int rand7()
{
    return 1 + (rand() % 7);
}

int rand5()
{
    int x;
    while ((x = rand7()) > 5)
    {
    }
    return x;
}

TEST(RAND5, rand5)
{
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
