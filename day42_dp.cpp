/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given a list of integers S and a target number k, write a function that returns a subset of S that adds up to k. If such a subset cannot be made, then return null.

Integers can appear more than once in the list. You may assume all numbers in the list are positive.

For example, given S = [12, 1, 61, 5, 9, 2] and k = 24, return [12, 9, 2, 1] since it sums up to 24.
*/

#include <gtest/gtest.h>
#include <numeric>

using namespace std;

/**
 * Idea: We can perform hierholzer to see if the path exists.
 * Using a priority queue to always get the min string
 */
vector<int> sum_to_k(vector<int> &nums, int k)
{
    vector<bool> dp(k + 1, false);
    vector<int> last(k + 1, -1);
    dp.shrink_to_fit();
    const auto size = dp.size();
    sort(nums.rbegin(), nums.rend());
    for (const auto &n : nums)
    {
        if (n < size)
        {
            dp[n] = true;
            last[n] = n;
        }
    }

    for (const auto &n : nums)
    {
        for (int i = k; i - n > n; --i)
        {
            if (dp[i - n])
            {
                if (!dp[i])
                    last[i] = n;
                dp[i] = true;
            }
        }
    }

    if (!dp[k])
        return {};

    vector<int> result;
    for (int sum = k; sum > 0;)
    {
        if (last[sum] == -1)
            break;
        result.push_back(last[sum]);
        sum -= last[sum];
    }

    return result;
}

TEST(SUM_TO_K, sum_to_k)
{
    vector<int> nums{12, 1, 61, 5, 9, 2};
    vector<int> v = sum_to_k(nums, 24);
    vector<int> v2 = sum_to_k(nums, 4);

    EXPECT_EQ(accumulate(v.begin(), v.end(), 0), 24);
    EXPECT_EQ(v2.size(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
