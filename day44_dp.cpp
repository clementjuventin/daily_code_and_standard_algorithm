/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

We can determine how "out of order" an array A is by counting the number of inversions it has. Two elements A[i] and A[j] form an inversion if A[i] > A[j] but i < j. That is, a smaller element appears after a larger element.

Given an array, count the number of inversions it has. Do this faster than O(N^2) time.

You may assume each element in the array is distinct.

For example, a sorted list has zero inversions. The array [2, 4, 1, 3, 5] has three inversions: (2, 1), (4, 1), and (4, 3). The array [5, 4, 3, 2, 1] has ten inversions: every distinct pair forms an inversion.
*/

#include <gtest/gtest.h>
#include <iterator>
#include <set>

using namespace std;

/**
 * Idea: We need a vector storing the amout of swap needed
 * dp[i] = dp[i-1] + amout_of_swap_needed_for_the_current_element
 * To get the amount of swap needed, we can build a sorted array nlog(n) TC and calculate
 * at each insertion how much elements before should have been bigger
 * We don't even need the full dp vector, just the last value
 * TC: nlog(n)
 * SC: n
 * 
 * See Fenwick tree
 */
int out_of_order(vector<int> &nums)
{
    int dp = 0;
    set<int> ordered_nums{nums[0]};
    for (auto it = nums.begin() + 1, end = nums.end(); it != end; ++it)
    {
        ordered_nums.insert(*it);
        int index = ordered_nums.size() - distance(ordered_nums.begin(), ordered_nums.find(*it)) - 1;
        dp += index;
    }
    return dp;
}

TEST(OUT_OF_ORDER, out_of_order)
{
    vector<int> nums{2, 4, 1, 3, 5};
    vector<int> nums2{5, 4, 3, 2, 1};

    EXPECT_EQ(out_of_order(nums), 3);
    EXPECT_EQ(out_of_order(nums2), 10);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
