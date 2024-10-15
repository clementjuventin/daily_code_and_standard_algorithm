/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

A number is considered perfect if its digits sum up to exactly 10.

Given a positive integer n, return the n-th perfect number.

For example, given 1, you should return 19. Given 2, you should return 28.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea:
 * Just iterate and count perfect numbers, we can do memoisation
 */

int perfect_number(int n){
    unordered_map<int, int> memo;

    int i = 1;
    int count = 0;
    while (count < n || i > 1111111111) {
        int number = i;
        int sum = 0;
        while (number > 0){
            if (memo[number]){
                sum += memo[number];
                break;
            }
            sum += number % 10;
            number = number / 10;
        }
        memo[i]=sum;
        if (sum == 10)
            count += 1;
        i++;
    }
    return i-1;
}

TEST(PERFECT_NUMBER, perferct_number) {
    EXPECT_EQ(perfect_number(1), 19);
    EXPECT_EQ(perfect_number(2), 28);
    EXPECT_EQ(perfect_number(3), 37);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
