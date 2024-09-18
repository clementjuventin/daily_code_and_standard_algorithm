/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a string of round, curly, and square open and closing brackets, return whether the brackets are balanced (well-formed).

For example, given the string "([])[]({})", you should return true.

Given the string "([)]" or "((()", you should return false.
*/

#include <gtest/gtest.h>
#include <deque>
#include <string>

using namespace std;

/**
 * TC: o(n)
 * SC: o(n)
 * 
 * The implementation is disgusting but at least I thing it's pretty optimized
 */

bool check(string s)
{
    vector<uint> counters(3, 0);
    deque<char> stack;

    for (char c : s)
    {
        if (c == '{')
        {
            counters.at(0) += 1;
            stack.push_back(c);
        }
        else if (c == '}')
        {
            counters.at(0) -= 1;
            if (stack.back() != '{')
                return false;
            stack.pop_back();
        }
        else if (c == '[')
        {
            counters.at(1) += 1;
            stack.push_back(c);
        }
        else if (c == ']')
        {
            counters.at(1) -= 1;
            if (stack.back() != '[')
                return false;
            stack.pop_back();
        }
        else if (c == '(')
        {
            counters.at(2) += 1;
            stack.push_back(c);
        }
        else if (c == ')')
        {
            counters.at(2) -= 1;
            if (stack.back() != '(')
                return false;
            stack.pop_back();
        }
    }

    return counters.at(0) == 0 && counters.at(1) == 0 && counters.at(2) == 0;
}

TEST(CHECK_PARENTHESIS, check)
{
    string s1{"([])[]({})"};
    string s2{"([)]"};
    string s3{"((()"};

    EXPECT_EQ(check(s1), true);
    EXPECT_EQ(check(s2), false);
    EXPECT_EQ(check(s3), false);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
