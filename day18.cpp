/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given an array of integers and a number k, where 1 <= k <= length of the array, compute the maximum values of each subarray of length k.

For example, given array = [10, 5, 2, 7, 8, 7] and k = 3, we should get: [10, 7, 8, 8], since:

    10 = max(10, 5, 2)
    7 = max(5, 2, 7)
    8 = max(2, 7, 8)
    8 = max(7, 8, 7)

Do this in O(n) time and O(k) space. You can modify the input array in-place and you do not need to store the results. You can simply print them out as you compute them.
*/

#include <gtest/gtest.h>
#include <deque>

using namespace std;

/**
 * Idea: Sliding windows
 */
vector<int> find_max(vector<int> *array, int k)
{
    deque<int> queue;
    vector<int> results;

    for (int i = 0; i < array->size(); i++)
    {
        while (!queue.empty() && queue.front() < i - k + 1)
            queue.pop_front();
        while (!queue.empty() && array->at(queue.back()) <= array->at(i))
            queue.pop_back();
        queue.push_back(i);
        if (i - k + 1 >= 0)
            results.push_back(array->at(queue.front()));
    }
    return results;
}

TEST(FIND_MAX, find_max)
{
    vector<int> array{10, 5, 2, 7, 8, 7};
    std::vector<int> expected = {10, 7, 8, 8};

    vector<int> res = find_max(&array, 3);

    EXPECT_EQ(res, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
