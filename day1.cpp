/**
Good morning! Here's your coding interview problem for today.

This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
 */

#include <gtest/gtest.h>

using namespace std;

bool sum_2(vector<int> array, int k)
{
    /*
        Idea: Right/Left pointer
        - We sort the array
        - Start from index 0 to -1
        TC: o(nlog(n))
        SC: o(1)

        We could do it in TC: o(n) and SC: o(n) using a hash table and looking for the other element to add
    */
    auto left = array.begin(), right = array.end();
    sort(left, right); // o(nlog(n))

    while (left < right) // o(n)
    {
        int sum = *left + *right;

        if (sum == k)
            return true;
        else if (sum > k)
            --right;
        else
            ++left;
    }

    return false;
}

TEST(SUM2, Case1)
{
    vector<int> array{2, 4, 3, 1, 1, 3};
    EXPECT_EQ(sum_2(array, 6), true);
    EXPECT_EQ(sum_2(array, 7), true);
    EXPECT_EQ(sum_2(array, 8), false);
    EXPECT_EQ(sum_2(array, 1), false);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
