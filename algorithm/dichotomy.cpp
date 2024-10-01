#include <gtest/gtest.h>

using namespace std;

size_t dichotomy(vector<int> &sorted_array, int element)
{
    size_t left{0}, right{sorted_array.size() - 1};

    while (left <= right)
    {
        size_t mid = left + (right - left) / 2;
        if (sorted_array[mid] == element)
            return mid;
        else if (sorted_array[mid] < element)
            left = mid + 1;
        else
        {
            if (mid == 0)
                return 0;
            right = mid - 1;
        }
    }
    return left;
}

TEST(DICHO, dichotomy)
{
    vector<int> array{2, 3, 4, 7, 8, 9};
    EXPECT_EQ(dichotomy(array, 1), 0);
    EXPECT_EQ(dichotomy(array, 2), 0);
    EXPECT_EQ(dichotomy(array, 4), 2);
    EXPECT_EQ(dichotomy(array, 9), 5);
    EXPECT_EQ(dichotomy(array, 10), 6);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
