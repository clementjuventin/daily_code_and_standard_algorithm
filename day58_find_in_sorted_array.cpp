/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

An sorted array of integers was rotated an unknown number of times.

Given such an array, find the index of the element in the array in faster than linear time. If the element doesn't exist in the array, return null.

For example, given the array [13, 18, 25, 2, 8, 10] and the element 8, return 4 (the index of 8 in the array).

You can assume all the integers in the array are unique.
*/

/**
 * Idea: The array is sorted, if we are able to find the rotation offset, ie: the place where the previous element
 * is bigger than the next element, we will be able to find our searched element in log(n) using dichotomy.
 * To find the offset we can start at a position and see if the length/2 next element is greater than the current
 * element. If so, the offset is between 0 and length/2, else it's between length/2 and length. This is a log(n) operation
 */

#include <gtest/gtest.h>

using namespace std;

size_t find_element(vector<int> array, int e)
{
    size_t left{0}, right{array.size()}, mid;
    while (left < right)
    {
        mid = left + (right - left) / 2;
        if (array[mid] > array[left])
            left = mid;
        else
            right = mid;
    }
    if (e >= array.front())
    {
        auto pos = lower_bound(array.begin(), array.begin() + right + 1, e);
        return pos - array.begin();
    }
    else
    {
        auto pos = lower_bound(array.begin() + right + 1, array.end(), e);
        return pos - array.begin();
    }
}

TEST(FIND_ELEMENT, find_element)
{
    vector<int> array{7, 8, 9, 2, 3, 4};
    EXPECT_EQ(find_element(array, 2), 3);
    EXPECT_EQ(find_element(array, 4), 5);
    EXPECT_EQ(find_element(array, 9), 2);
    EXPECT_EQ(find_element(array, 7), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}