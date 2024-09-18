/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

You are given an array of non-negative integers that represents a two-dimensional elevation map where each element is unit-width wall and the integer is the height. Suppose it will rain and all spots between two walls get filled up.

Compute how many units of water remain trapped on the map in O(N) time and O(1) space.

For example, given the input [2, 1, 2], we can hold 1 unit of water in the middle.

Given the input [3, 0, 1, 3, 0, 5], we can hold 3 units in the first index, 2 in the second, and 3 in the fourth index (we cannot hold 5 since it would run off to the left), so we can trap 8 units of water.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: Two pointers
 * TC: o(n)
 * SC: o(1)
 */

int rain(vector<int> vector)
{
    int left = 0;
    int max_left = left;
    int right = vector.size() - 1;
    int max_right = right;

    int count = 0;
    while (left < right)
    {
        if (vector.at(max_left) < vector.at(max_right))
        {
            if (vector.at(left) > vector.at(max_left))
                max_left = left;
            else
                count += vector.at(max_left) - vector.at(left);
            left++;
        }
        else
        {
            if (vector.at(right) > vector.at(max_right))
                max_left = right;
            else
                count += vector.at(max_right) - vector.at(right);
            right--;
        }
    }
    return count;
}

TEST(RAIN, rain)
{
    vector<int> r{3, 0, 1, 3, 0, 5};
    vector<int> r2{2, 1, 2};
    vector<int> r3{2, 0, 3, 1, 1, 0, 2};

    EXPECT_EQ(rain(r), 8);
    EXPECT_EQ(rain(r2), 1);
    EXPECT_EQ(rain(r3), 6);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
