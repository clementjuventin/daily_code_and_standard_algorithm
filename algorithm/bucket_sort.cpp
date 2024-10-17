#include <gtest/gtest.h>
#include <limits>
#include <vector>
#include <iostream>

using namespace std;

/*
The bucket sort allows to split elements into differents buckets and apply a sorting algorithm on this buckets.
This algo can be useful when you only need to sort a portion of the array. e.g: find the k smallest element in an
usorted array

TC: O(n²)
SC: O(n+k)
*/

void bucketSort(vector<int> &arr)
{
    int n = arr.size();
    if (n <= 0)
        return;

    int maxValue = *max_element(arr.begin(), arr.end());

    vector<vector<int>> buckets(n);

    // Distribute the array elements into different buckets
    for (int i = 0; i < n; i++)
    {
        int bucketIndex = (n * arr[i]) / (maxValue + 1); // Normalize into bucket index
        buckets[bucketIndex].push_back(arr[i]);
    }

    for (int i = 0; i < n; i++)
        sort(buckets[i].begin(), buckets[i].end());

    // Concatenate all sorted buckets back into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < buckets[i].size(); j++)
            arr[index++] = buckets[i][j];
    }
}

TEST(COUNTING_SORT, counting_sort)
{
    vector<int> arr{2, 3, 2, 2, 3, 4, 2, 3, 2, 5, 6, 6, 6, 7};

    bucketSort(arr);

    vector<int> expected{2, 2, 2, 2, 2, 3, 3, 3, 4, 5, 6, 6, 6, 7};

    EXPECT_EQ(arr, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
