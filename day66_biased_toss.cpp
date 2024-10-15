/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Square.

Assume you have access to a function toss_biased() which returns 0 or 1 with a probability that's not 50-50 (but also not 0-100 or 100-0). You do not know the bias of the coin.

Write a function to simulate an unbiased coin toss.
*/

#include <gtest/gtest.h>

using namespace std;

bool toss_biased()
{
    return rand() % 10 < 6; // 0..5 = true, 6..9 = false (ie 6/10 true)
}

/**
 * Idea:
 * Let p be our function and pb the biased toss
 * p(1) = 1/2 = p(0)
 * Also, pb(1) = x and pb(0) = 1 - x
 *
 * pb(0, 0) = (1-x)²
 * pb(1, 0) = x(1-x)
 * pb(0, 1) = (1-x)x
 * pb(1, 1) = x²
 *
 * So pb(1, 0) and pb(0, 1) have the same probability of occuring.
 */

bool toss()
{
    while (true)
    {
        bool a = toss_biased();
        bool b = toss_biased();

        if (a ^ b)
            return a && !b;
    }
}

TEST(TOSS, toss)
{
    srand(1);
    int len = 10000;
    int c = 0;
    for (int i = 0; i < len; i++)
        c += toss();

    cout << "Result " << c * 1.0 / len << endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
