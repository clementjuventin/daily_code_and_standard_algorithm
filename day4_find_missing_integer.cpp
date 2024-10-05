/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Stripe.

Given an array of integers, find the first missing positive integer in linear time and constant space. In other words, find the lowest positive integer that does not exist in the array. The array can contain duplicates and negative numbers as well.

For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.

You can modify the input array in-place.
*/

#include <gtest/gtest.h>

using namespace std;

int find_missing_positive_integer(std::vector<int> &array)
{
    /*
        Idea: The size of the array is greater or equal than the first missing positive number
        We can place element of the array to an index corresponding to it's position (ex: 1 -> index 0, 2 -> index 3)
        And iterate over the array to find with index is missing
        Space complexity: constant except for the input array
        Time complexity: place_element can be at worse n but only once because it will place all element.
        So complexity is O(n)
    */
    const std::size_t len{array.size()};
    for (auto &e : array)
    {
        while (1 <= e && e <= len)
        {
            const std::size_t index{static_cast<size_t>(e) - 1};
            if (array[index] == e)
                break;
            std::swap(array[index], e);
        }
    }

    for (std::size_t i = 1; i < len; i++)
    {
        if (array[i - 1] != i)
            return i;
    }

    return len;
}

TEST(FIND_MISSING_POSITIVE_INTEGER, find_missing_positive_integer)
{
    vector<int> array1{3, 4, -1, 1};
    vector<int> array2{1, 2, 0};
    vector<int> array3{0, 0, 0, 0, 0};
    vector<int> array4{5};

    EXPECT_EQ(find_missing_positive_integer(array1), 2);
    EXPECT_EQ(find_missing_positive_integer(array2), 3);
    EXPECT_EQ(find_missing_positive_integer(array3), 1);
    EXPECT_EQ(find_missing_positive_integer(array4), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
