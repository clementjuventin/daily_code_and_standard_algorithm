/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a array of numbers representing the stock prices of a company in chronological order, write a function that calculates the maximum profit you could have made from buying and selling that stock once. You must buy before you can sell it.

For example, given [9, 11, 8, 5, 7, 10], you should return 5, since you could buy the stock at 5 dollars and sell it at 10 dollars.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea:
 */
int max_profit(vector<int> prices)
{
    if (prices.size() < 2)
        return 0;
    int min_price = prices[0];
    int max_profit = 0;
    for (auto it = prices.begin() + 1, end = prices.end(); it != end; ++it)
    {
        min_price = min(*it, min_price);
        max_profit = max(max_profit, *it - min_price);
    }
    return max_profit;
}

TEST(MAX_PROFIT, max_profit)
{
    vector<int> v{9, 11, 8, 5, 7, 10};

    EXPECT_EQ(max_profit(v), 5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
