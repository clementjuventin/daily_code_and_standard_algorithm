/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a list of integers, return the largest product that can be made by multiplying any three integers.

For example, if the list is [-10, -10, 5, 2], we should return 500, since that's -10 * -10 * 5.

You can assume the list has at least three integers.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea:
 * We sort the array and we take the maximum between the product of the three greatest elements and the two smallest and the greatest (in case we can have a bigger product using two negative number)
 * 
 * TC: It can be achieved in O(n) but I just want to end this quickly so I will sort the array. The TC is o(nlogn)
 * SC: o(1)
 */

int max_product(vector<int> &array){
    sort(array.begin(), array.end());
    size_t s = array.size();
    return max(array[s-3]*array[s-2]*array[s-1],array[0]*array[1]*array[s-1]);
}

TEST(PRODUCT, product) {
    vector<int> a{-10, -10, 5, 2};
    vector<int> a2{6, 2, 1 , 2, 4};
    EXPECT_EQ(max_product(a2), 48);
    EXPECT_EQ(max_product(a), 500);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
