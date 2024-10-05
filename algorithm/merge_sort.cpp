#include <gtest/gtest.h>
#include <vector>

using namespace std;

void merge_sort(vector<int> &array)
{
    if (array.size() <= 1)
        return;

    size_t mid = array.size() / 2;
    vector<int> left(array.begin(), array.begin() + mid);
    vector<int> right(array.begin() + mid, array.end());

    // Recursively sort the halves
    merge_sort(left);
    merge_sort(right);

    // Merge the sorted halves
    size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size())
    {
        if (left[i] < right[j])
        {
            array[k] = left[i];
            i++;
        }
        else
        {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    // Complete remaining elements in left array if any
    while (i < left.size())
    {
        array[k] = left[i];
        i++;
        k++;
    }

    // Complete remaining elements in right array if any
    while (j < right.size())
    {
        array[k] = right[j];
        j++;
        k++;
    }
}

TEST(MERGESORT, mergeSortTests)
{
    // Test 1: Already sorted array
    std::vector<int> array1{1, 2, 3, 4, 5};
    merge_sort(array1);
    EXPECT_EQ(array1, (std::vector<int>{1, 2, 3, 4, 5}));

    // Test 2: Reverse sorted array
    std::vector<int> array2{5, 4, 3, 2, 1};
    merge_sort(array2);
    EXPECT_EQ(array2, (std::vector<int>{1, 2, 3, 4, 5}));

    // Test 3: Unsorted array with random elements
    std::vector<int> array3{38, 27, 43, 3, 9, 82, 10};
    merge_sort(array3);
    EXPECT_EQ(array3, (std::vector<int>{3, 9, 10, 27, 38, 43, 82}));

    // Test 4: Array with duplicate elements
    std::vector<int> array4{4, 2, 4, 3, 2, 1, 4};
    merge_sort(array4);
    EXPECT_EQ(array4, (std::vector<int>{1, 2, 2, 3, 4, 4, 4}));

    // Test 5: Array with only one element
    std::vector<int> array5{42};
    merge_sort(array5);
    EXPECT_EQ(array5, (std::vector<int>{42}));

    // Test 6: Empty array
    std::vector<int> array6{};
    merge_sort(array6);
    EXPECT_EQ(array6, (std::vector<int>{}));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
