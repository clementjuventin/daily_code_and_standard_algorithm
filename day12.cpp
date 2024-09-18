/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

There exists a staircase with N steps, and you can climb up either 1 or 2 steps at a time. Given N, write a function that returns the number of unique ways you can climb the staircase. The order of the steps matters.

For example, if N is 4, then there are 5 unique ways:

    1, 1, 1, 1
    2, 1, 1
    1, 2, 1
    1, 1, 2
    2, 2

What if, instead of being able to climb 1 or 2 steps at a time, you could climb any number from a set of positive integers X? For example, if X = {1, 3, 5}, you could climb 1, 3, or 5 steps at a time.
*/


#include <gtest/gtest.h>
#include <string>

using namespace std;

int stairs_simple(int count)
{
    /*
    Idea: I started to writte the amount of unique ways for 1, 2, .. 4 and realized it was a
    fibonnaci suit. I had also the intuition that we could use dynamic programming to solve
    this problem using the n-2 and n-1 results but I was not sure that it would work.
    With these two elements I think we can generalize the solution. Let's try
    */
    // Note: We can do this in a constant space
    vector<int> dp;

    dp.push_back(1);
    dp.push_back(2);

    for (int i = 2; i < count; i++)
        dp.push_back(dp[i - 2] + dp[i - 1]);

    return dp[count - 1];
}

int stairs_complex(int count, set<int> climbs)
{
    // We consider it's always possible to climb 1 step at the time (at least)
    vector<int> dp;
    dp.push_back(1);

    for (int i = 1; i <= count; ++i)
    {
        int sum = 0;
        for (auto it = climbs.begin(); it != climbs.end(); ++it)
        {
            if (*it <= i)
                sum += dp[i - *it];
        }
        dp.push_back(sum);
    }

    return dp[count];
}

TEST(STAIRS, stairs_simple)
{
    int res1 = stairs_simple(1);
    int res2 = stairs_simple(2);
    int res3 = stairs_simple(3);
    int res4 = stairs_simple(4);
    int res5 = stairs_simple(5);

    EXPECT_EQ(res1, 1);
    EXPECT_EQ(res2, 2);
    EXPECT_EQ(res3, 3);
    EXPECT_EQ(res4, 5);
    EXPECT_EQ(res5, 8);
}

TEST(STAIRS, stairs_complex)
{
    int res2 = stairs_complex(1, set{1});
    int res3 = stairs_complex(10, set{1});
    int res4 = stairs_complex(4, set{1, 3, 5});
    int res5 = stairs_complex(5, set{1, 2});

    EXPECT_EQ(res2, 1);
    EXPECT_EQ(res3, 1);
    EXPECT_EQ(res4, 3);
    EXPECT_EQ(res5, 8);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
