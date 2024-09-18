/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Quora.

Given a string, find the palindrome that can be made by inserting the fewest number of characters as possible anywhere in the word. If there is more than one palindrome of minimum length that can be made, return the lexicographically earliest one (the first one alphabetically).

For example, given the string "race", you should return "ecarace", since we can add three letters to it (which is the smallest amount to make a palindrome). There are seven other palindromes that can be made from "race" by adding three letters, but "ecarace" comes first alphabetically.

As another example, given the string "google", you should return "elgoogle".
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: We need to find the start index for the palindrome, it can be index 0 to n
 * If there is two similar character, we can also considere both as the starting point for an even palindrome
 * Keep the min solution (alpha order)
 *
 * TC: o(n²)
 * SC: o(n)
 *
 * Comment: I looked for solution to this problem, ChatGPT was proposing not working solutions and the other algo I found
 * was DP and I couldn't understand. This one seems good to me even if I'am not totally sure, but if it words it's way
 * easier to understand than the DP and has the same TC
 */

string check_pal(const string &word, int left, int right)
{
    while (left >= 0 && right < word.size() && word[left] == word[right])
    {
        left--;
        right++;
    }

    if (left < 0)
    {
        string left_s = word.substr(right);
        reverse(left_s.begin(), left_s.end());
        return left_s + word;
    }
    else if (right >= word.size())
    {
        string right_s = word.substr(0, left + 1);
        reverse(right_s.begin(), right_s.end());
        return word + right_s;
    }

    return "";
}

string smallest_pal(const string &word)
{
    string solution;

    for (int center = 0; center < word.size(); center++)
    {
        string s1 = check_pal(word, center, center);     // Odd-length palindrome
        string s2 = check_pal(word, center, center + 1); // Even-length palindrome

        if (solution.empty() || (!s1.empty() && (s1.size() < solution.size() || (s1.size() == solution.size() && s1 < solution))))
            solution = s1;
        if (solution.empty() || (!s2.empty() && (s2.size() < solution.size() || (s2.size() == solution.size() && s2 < solution))))
            solution = s2;
    }

    return solution;
}

TEST(PAL, pal)
{
    string google = "google";
    string race = "race";
    string kayak = "kayak";

    smallest_pal(google);
    smallest_pal(race);
    smallest_pal(kayak);

    EXPECT_STREQ(smallest_pal(google).c_str(), "elgoogle");
    EXPECT_STREQ(smallest_pal(race).c_str(), "ecarace");
    EXPECT_STREQ(smallest_pal(kayak).c_str(), "kayak");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
