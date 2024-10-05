/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Uber.

Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].

Follow-up: what if you can't use division?
*/

#include <gtest/gtest.h>

using namespace std;

void mult(vector<int> &array)
{
    /*
        Idea: With division
        Get the total product and then iterate over each elements of the array and devide the total product by the element

        Idea: Without division
        I couldn't find a solution with a constant space complexity, since there is no indication I don't know
        if it's the expected solution but assuming we want to optimise the execution using multiplications
        instead of division, I guess that allocating an array of size N looses all the benefits of the approach.
        No implementation but the idea is that the element i of the solution is equal to
        proudct(array[:i]) * product(array[i+1:])
    */
    int product{1};
    size_t zero_count = 0;
    for (auto it = array.begin(); it < array.end(); it++)
    {
        if (*it == 0)
            zero_count++;
        else
            product *= *it;
    }
    if (zero_count > 0)
    {
        product = (zero_count == 1) * product; // 0 if more than 1 zero
        for (auto it = array.begin(); it < array.end(); it++)
            *it = *it == 0 ? product : 0;
    }
    else
    {
        for (auto it = array.begin(); it < array.end(); it++)
            *it = product / *it;
    }
}

TEST(MULT, Case1)
{
    vector<int> array{2, 4, 3, 1, 3};
    vector<int> array2{2, 4, 3, 1, 3, 0};
    vector<int> array3{0, 2, 4, 3, 1, 3, 0};

    mult(array);
    mult(array2);
    mult(array3);

    EXPECT_EQ(array[0], 36);
    EXPECT_EQ(array[1], 18);
    EXPECT_EQ(array2[0], 0);
    EXPECT_EQ(array2[5], 72);
    EXPECT_EQ(array2[0], 0);
    EXPECT_EQ(array2[1], 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
