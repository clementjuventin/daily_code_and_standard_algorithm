/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

Given an array of numbers, find the maximum sum of any contiguous subarray of the array.

For example, given the array [34, -50, 42, 14, -5, 86], the maximum sum would be 137, since we would take elements 42, 14, -5, and 86.

Given the array [-5, -1, -8, -9], the maximum sum would be 0, since we would not take any elements.

Do this in O(N) time.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: We need two pointers (i,j), each time we go under 0 summing array[i:j] we set i to j because
 * if sum(array[i:j]) < 0 then sum(array[i:k]) < max(0, sum(array(j:k))) with j <= k
 */
int sum_subarray(vector<int> array)
{
    size_t left{0}, right{0};
    const size_t size{array.size()};
    int max_sum{0}, sum{0};

    while (right != size)
    {
        sum += array[right];
        max_sum = (sum <= max_sum) * max_sum + (sum > max_sum) * sum;
        right++;
        if (sum < 0)
        {
            left = right;
            sum = 0;
        }
    }
    return max_sum;
}

TEST(SUM_SUBARRAY, sum_subarray)
{
    vector<int> array{34, -50, 42, 14, -5, 86};
    vector<int> array2{-5, -1, -8, -9};
    vector<int> array3;

    EXPECT_EQ(sum_subarray(array), 137);
    EXPECT_EQ(sum_subarray(array2), 0);
    EXPECT_EQ(sum_subarray(array3), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
