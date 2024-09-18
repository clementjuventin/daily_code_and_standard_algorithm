/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Implement regular expression matching with the following special characters:

    . (period) which matches any single character
    * (asterisk) which matches zero or more of the preceding element

That is, implement a function that takes in a string and a valid regular expression and returns whether or not the string matches the regular expression.

For example, given the regular expression "ra." and the string "ray", your function should return true. The same regular expression on the string "raymond" should return false.

Given the regular expression ".*at" and the string "chat", your function should return true. The same regular expression on the string "chats" should return false.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: 2 Solutions, recursive backtracking or DP
 *
 * DP: Using a two dimentional array
 * casual letter compared to casual letter: t[i] = l1 == l2
 * period compared to casual letter: t[i] = t[j-1][i-1] because we can add any letter
 * asterix compared to casual letter: t[i] = l_before_asterix == l2 || t[j][i-2] because we have the choice between
 * considering or not the asterix
 * TC: o(n*m)
 * SC: o(n*m)
 */
bool solve(string word, string regex)
{
    int height = word.size() + 1; // +1 because we start from the empty string
    int width = regex.size() + 1;

    vector<vector<bool>> dp(height, vector(width, false));

    for (int j = 1; j < height; j++)
    {
        for (int i = 1; i < width; i++)
        {
            char w_char = word.at(j-1);
            char r_char = regex.at(i-1);

            if (w_char == r_char)
                dp.at(j).at(i) = true;
            else if (r_char == '.')
                dp.at(j).at(i) = dp.at(j - 1).at(i - 1);
            else if (r_char == '*')
            {
                char previous_r_char = regex.at(i - 1);
                if (w_char == previous_r_char || dp.at(j).at(i - 2))
                    dp.at(j).at(i) = true;
            }
        }
    }
    return dp.at(height - 1).at(width - 1);
}

TEST(REGEX_SOLVE, regex)
{
    string str1 = "ray";
    string pattern1 = "ra.";

    string str2 = "raymond";
    string pattern2 = "ra.";

    string str3 = "chat";
    string pattern3 = ".*at";

    string str4 = "chats";
    string pattern4 = ".*at";

    EXPECT_EQ(solve(str1, pattern1), true);
    EXPECT_EQ(solve(str2, pattern2), false);
    EXPECT_EQ(solve(str3, pattern3), true);
    EXPECT_EQ(solve(str4, pattern4), false);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
