/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Stripe.

Given an array of integers, find the first missing positive integer in linear time and constant space. In other words, find the lowest positive integer that does not exist in the array. The array can contain duplicates and negative numbers as well.

For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.

You can modify the input array in-place.
*/

#include <gtest/gtest.h>

using namespace std;

void place_element(vector<int> *array, int element)
{
    if (element < 1)
        return;
    int index = element - 1;
    if (index >= array->size())
        return;

    int replaced_element = array->at(index);
    array->at(index) = element;

    if (replaced_element != element)
        place_element(array, replaced_element);
}

int find_missing_positive_integer(vector<int> *array)
{
    /*
        Idea: The size of the array is greater or equal than the first missing positive number
        We can place element of the array to an index corresponding to it's position (ex: 1 -> index 0, 2 -> index 3)
        And iterate over the array to find with index is missing
        Space complexity: constant except for the input array
        Time complexity: place_element can be at worse n but only once because it will place all element.
        So complexity is O(n)
    */
    for (int i = 0; i < array->size(); i++)
        place_element(array, array->at(i));
    for (int i = 0; i < array->size(); i++)
    {
        if (array->at(i) != i + 1)
            return i + 1;
    }
    return array->size();
}

TEST(FIND_MISSING_POSITIVE_INTEGER, find_missing_positive_integer)
{
    vector<int> array1{3, 4, -1, 1};
    vector<int> array2{1, 2, 0};

    int result1 = find_missing_positive_integer(&array1);
    int result2 = find_missing_positive_integer(&array2);

    EXPECT_EQ(result1, 2);
    EXPECT_EQ(result2, 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
