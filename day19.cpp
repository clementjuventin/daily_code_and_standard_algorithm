/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

A builder is looking to build a row of N houses that can be of K different colors. He has a goal of minimizing cost while ensuring that no two neighboring houses are of the same color.

Given an N by K matrix where the nth row and kth column represents the cost to build the nth house with kth color, return the minimum cost which achieves this goal.
*/

#include <gtest/gtest.h>
#include <deque>

using namespace std;

/**
 * Idea: Take another matrix and initialize the costs for the first house to the same value as matrix costs
 * To move on the next house for a specific color, we pick the minimum previous cost (expect if it's the one with the
 * same color) until we reach the end
 * Time complexity: This also is n*k*k but it could be n*k if we better calculate the max for a row (ex: calculate indices of
 * max1 and max2 and each time pick one of these two instead of recalculating the max)
 * Space complexity: We just need the previous row to build the next one so k
 */
int best_cost(vector<vector<int>> *costs)
{
    size_t colors = costs->at(0).size();
    size_t houses = costs->size();

    vector<int> prices = costs->at(0);
    for (int i = 1; i < houses; i++)
    {
        vector<int> next_prices = costs->at(i);
        for (int j = 0; j < colors; j++)
        {
            if (j == 0)
                next_prices.at(0) = next_prices.at(0) + *min(prices.begin() + 1, prices.end());
            else if (j + 1 == colors)
                next_prices.at(j) = next_prices.at(j) + *min(prices.begin(), prices.end() - 1);
            else
                next_prices.at(j) = next_prices.at(j) + min(*min(prices.begin(), prices.begin() + j - 1), *min(prices.begin() + j + 1, prices.end()));
        }
        prices = next_prices;
    }
    return *min(prices.begin(), prices.end());
}

TEST(COSTS, best_cost)
{
    vector<int> house_1{5, 1, 3};
    vector<int> house_2{4, 2, 4};
    vector<int> house_3{3, 8, 2};
    vector<vector<int>> costs{house_1, house_2, house_3};

    int res = best_cost(&costs);

    EXPECT_EQ(res, 8);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
