/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Uber.

Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].

Follow-up: what if you can't use division?
*/

#include <gtest/gtest.h>

using namespace std;

void mult(vector<int> *array)
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
    for (auto it = (*array).begin(); it < (*array).end(); it++)
        product *= *it;
    for (auto it = (*array).begin(); it < (*array).end(); it++)
        *it = product / *it;
}

TEST(MULT, Case1)
{
    vector<int> array{2, 4, 3, 1, 3};

    mult(&array);

    EXPECT_EQ(array[0], 36);
    EXPECT_EQ(array[1], 18);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
