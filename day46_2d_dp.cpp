/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

Given a string, find the longest palindromic contiguous substring. If there are more than one with the maximum length, return any one.

For example, the longest palindromic substring of "aabcdcb" is "bcdcb". The longest palindromic substring of "bananas" is "anana".
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: 2d DP considering substring from i to j and dp[i][j] is true if s[i:j] is a pal
 * if (s[i] == s[j])
 *  dp[i][j] = i-j == 2 ? true : dp[i+1][j-1]       -> ex: "zabcz" = is "abc" a pal?
 * 
 * TC: o(n²)
 * SC: o(n)
 */
string max_pal(string &s)
{
    const size_t length = s.size();
    if (length == 0)
        return s;
    vector<vector<bool>> dp(length, vector<bool>(length, false));

    size_t max_length{1};
    size_t max_string{0};
    for (size_t i = 0; i < length; ++i)
        dp[i][i] = true;

    size_t i = length - 1;
    while (true)
    {
        for (size_t j = i + 1; j < length; ++j)
        {
            if (s.at(i) == s.at(j))
            {
                dp[i][j] = j - i == 2 ? true : dp[i + 1][j - 1];
                if (dp[i][j] && j - i > max_length)
                {
                    max_length = j - i + 1;
                    max_string = i;
                }
            }
        }
        if (i == 0)
            break;
        i--;
    }
    return s.substr(max_string, max_length);
}

TEST(MAX_PAL, max_pal)
{
    string s1{"bananas"};
    string s2{"aabcdcb"};
    string s3{""};
    string s4{"a"};

    EXPECT_STREQ(max_pal(s1).c_str(), "anana");
    EXPECT_STREQ(max_pal(s2).c_str(), "bcdcb");
    EXPECT_STREQ(max_pal(s3).c_str(), "");
    EXPECT_STREQ(max_pal(s4).c_str(), "a");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
