/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given an array of integers where every integer occurs three times except for one integer, which only occurs once, find and return the non-duplicated integer.

For example, given [6, 1, 3, 3, 3, 6, 6], return 1. Given [13, 19, 13, 13], return 19.

Do this in O(N) time and O(1) space.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: Bitwise operations
 * The same problem with 2 instead of 3 is simple, we can use XOR
 */
int find_uniq(vector<int> ints)
{
    int twice{0};
    int once{0};
    int mask{0};
    for (int i : ints)
    {
        // Bits appeared twice % 3
        // A 1 bit at pos j in twice can't also be a 1 bit at pos j in i & once because it was cleared by the mask
        twice = twice | (i & once);

        // Bits appeared once % 3
        once = once ^ i;

        // Mask (bits that appeared 3 times % 3)
        mask = ~(twice & once);

        // Clear once, twice
        twice = twice & mask;
        once = once & mask;
    }
    return once;
}

TEST(FIND_UNIQ, find_uniq)
{
    EXPECT_EQ(find_uniq(vector{6, 1, 3, 3, 3, 6, 6}), 1);
    EXPECT_EQ(find_uniq(vector{13, 19, 13, 13}), 19);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
