/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a multiset of integers, return whether it can be partitioned into two subsets whose sums are the same.

For example, given the multiset {15, 5, 20, 10, 35, 15, 10}, it would return true, since we can split it up into {15, 5, 10, 15, 10} and {20, 35}, which both add up to 55.

Given the multiset {15, 5, 20, 10, 35}, it would return false, since we can't split it up into two subsets that add up to the same sum.
*/

/**
 * Idea: Everything get simple once you understood that you can sum the original array to get the target sum
 * From the target sum, you can easily implement a dp algo to see if we can sum elements from the array to
 * reach k. Here it's not needed but we could do backtracking if we needed to return both sets
 */

#include <gtest/gtest.h>
#include <numeric>

using namespace std;

bool k_sum(vector<int> &array, int sum)
{
    if (sum == 0)
        return true;
    vector<bool> dp(sum + 1, false);
    sort(array.begin(), array.end());

    dp[0] = true;
    for (auto &e : array)
    {
        if (e < dp.size())
            dp[e] = true;
    }

    for (size_t i = array.size() - 1;; i--)
    {
        int e = array[i];
        for (size_t j = e - 1;; j--)
        {
            if (dp[j] && dp.size() > j + e)
            {
                if (j + e == sum)
                    return true;
                dp[j + e] = true;
            }
            if (j == 0)
                break;
        }
        if (i == 0)
            break;
    }
    return dp[sum];
}

bool equal_multiset(vector<int> &set)
{
    if (set.size() == 0)
        return true;
    int sum = accumulate(set.begin(), set.end(), 0);
    if (sum / 2 != sum / 2.0)
        return false;
    return k_sum(set, sum / 2);
}

TEST(EQUAL_MULTISET, equal_multiset)
{
    vector<int> array{15, 5, 20, 10, 35, 15, 10};
    vector<int> array2{15, 5, 20, 10, 35};
    vector<int> array3{0};
    vector<int> array4{1};
    vector<int> array5{};
    EXPECT_EQ(equal_multiset(array), true);
    EXPECT_EQ(equal_multiset(array2), false);
    EXPECT_EQ(equal_multiset(array3), true);
    EXPECT_EQ(equal_multiset(array4), false);
    EXPECT_EQ(equal_multiset(array5), true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}