/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Airbnb.

Given a list of integers, write a function that returns the largest sum of non-adjacent numbers. Numbers can be 0 or negative.

For example, [2, 4, 6, 2, 5] should return 13, since we pick 2, 6, and 5. [5, 1, 1, 5] should return 10, since we pick 5 and 5.

Follow-up: Can you do this in O(N) time and constant space?
*/

#include <gtest/gtest.h>

using namespace std;

int max_list(vector<int> *array)
{
    /*
    Idea: For each element, we focus to get the maximum sum, we can either pick it or not, if we pick it
    the sum is equal to i-2+element, else it's equal to i-1. Just take the max of it and continue
    Time complexity: O(n)
    Space complexity: O(1)
    */

    if (array->size() <= 2)
    {
        return *max_element(array->begin(), array->end());
    }

    int max_sum_1 = array->at(0);
    int max_sum_2 = array->at(1);

    for (int i = 2; i < array->size(); i++)
    {
        int sum = array->at(i) + max_sum_1;
        max_sum_1 = max(max_sum_1, max_sum_2);
        if (sum > max_sum_2)
            max_sum_2 = sum;
    }
    return max(max_sum_1, max_sum_2);
}

TEST(MAX_LIST, max_list)
{
    vector<int> array1{2, 4, 6, 2, 5};
    vector<int> array2{5, 1, 1, 5};

    int res1 = max_list(&array1);
    int res2 = max_list(&array2);

    EXPECT_EQ(res1, 13);
    EXPECT_EQ(res2, 10);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
