/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

The edit distance between two strings refers to the minimum number of character insertions, deletions, and substitutions required to change one string to the other. For example, the edit distance between “kitten” and “sitting” is three: substitute the “k” for “s”, substitute the “e” for “i”, and append a “g”.

Given two strings, compute the edit distance between them.
*/

#include <gtest/gtest.h>
#include <string>

using namespace std;

/**
 * Idea: Classic dp issue
 * dp[j][i] =
 *
 * TC: o(n²)
 * SC: o(n²)
 */

int changes(string s1, string s2)
{
    int height = s1.size() + 1;
    int width = s2.size() + 1;

    vector<vector<int>> dp(height, vector<int>(width, 0));

    for (int i = 1; i < height; i++)
        dp.at(i).at(0) = i;
    for (int i = 1; i < width; i++)
        dp.at(0).at(i) = i;

    for (int j = 1; j < height; j++)
    {
        for (int i = 1; i < width; i++)
        {
            int minimum = 1 + min(min(dp.at(j).at(i - 1), dp.at(j - 1).at(i)), dp.at(j - 1).at(i - 1));
            if (s1.at(j - 1) == s2.at(i - 1))
            {
                minimum = min(minimum, dp.at(j - 1).at(i - 1));
            }
            dp.at(j).at(i) = minimum;
        }
    }
    return dp.back().back();
}

TEST(CHANGES, changes)
{
    string s1{"kitten"};
    string s2{"sitting"};

    EXPECT_EQ(changes(s2, s1), 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
