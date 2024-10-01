#include <gtest/gtest.h>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

/*
Counting sort is a non-comparison-based sorting algorithm. It's efficient when the range of input
values is small compared to the number of elements to be sorted.

TC: O(n + m) with n = array length and m = range of elements
SC: O(m)
*/

vector<int> counting_sort(const vector<int> &array)
{
    if (array.empty())
        return {};

    // Find the min and max values
    int mi = *min_element(array.begin(), array.end());
    int ma = *max_element(array.begin(), array.end());
    size_t range = ma - mi + 1;

    // Count occurrences
    vector<size_t> count(range, 0);
    for (const auto &e : array)
        count[e - mi]++;

    // Build the sorted output
    vector<int> sorted;
    sorted.reserve(array.size());
    for (size_t i = 0; i < range; ++i)
    {
        while (count[i] > 0)
        {
            sorted.push_back(i + mi);
            count[i]--;
        }
    }
    return sorted;
}

TEST(COUNTING_SORT, counting_sort)
{
    vector<int> arr{2, 3, 2, 2, 3, 4, 2, 3, 2, 5, 6, 6, 6, 7};

    vector<int> result = counting_sort(arr);

    vector<int> expected{2, 2, 2, 2, 2, 3, 3, 3, 4, 5, 6, 6, 6, 7};

    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
