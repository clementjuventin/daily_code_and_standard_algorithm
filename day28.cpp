/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Palantir.

Write an algorithm to justify text. Given a sequence of words and an integer line length k, return a list of strings which represents each line, fully justified.

More specifically, you should have as many words as possible in each line. There should be at least one space between each word. Pad extra spaces when necessary so that each line has exactly length k. Spaces should be distributed as equally as possible, with the extra spaces, if any, distributed starting from the left.

If you can only fit one word on a line, then you should pad the right-hand side with spaces.

Each word is guaranteed not to be longer than k.

For example, given the list of words ["the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"] and k = 16, you should return the following:

["the  quick brown", # 1 extra space on the left
"fox  jumps  over", # 2 extra spaces distributed evenly
"the   lazy   dog"] # 4 extra spaces distributed evenly

*/

#include <gtest/gtest.h>
#include <string>
#include <cmath>
#include <deque>

using namespace std;

/**
 * Idea:
 * Step 1: How much word cna fit in a line
 * Step 2: White space distribution
 *
 * TC: o(n²)
 * SC: o(n)
 *
 * I did a mistake and the last word is not taken into account
 */

vector<string> justify(deque<string> words, uint k)
{
    vector<string> result;
    deque<string> line;
    uint line_word_count = 0;
    uint line_len = 0;

    // Mistake from I with the algo
    words.push_back(string{""});

    while (!words.empty())
    {
        string word = words.front();
        words.pop_front();

        // The line does not fit
        uint line_len_with_word = line_len + line_word_count + word.size();
        if (k < line_len_with_word || words.empty())
        {
            // Justify
            string justified_line;
            // 1 Word case
            if (line_word_count == 1)
            {
                justified_line = line.front() + string(k - line_len, ' ');
            }
            else
            {
                float remaining_whitespace_count = k - (line_len + line_word_count - 1);
                uint whitespaces_per_words = ceil(remaining_whitespace_count / (line_word_count - 1));
                while (line_word_count > 1)
                {
                    justified_line += line.front() + ' ';
                    if (remaining_whitespace_count >= whitespaces_per_words)
                    {
                        justified_line += string(whitespaces_per_words, ' ');
                        remaining_whitespace_count -= whitespaces_per_words;
                    }
                    line.pop_front();
                    line_word_count -= 1;
                }
                if (remaining_whitespace_count != 0)
                    justified_line += string(remaining_whitespace_count, ' ');
                justified_line += line.front();

                result.push_back(justified_line);
            }

            line.clear();
            line_word_count = 0;
            line_len = 0;
        }
        line.push_back(word);
        line_len += word.size();
        line_word_count++;
    }
    return result;
}

TEST(JUSTIFY, justify)
{
    deque<string> words{"the", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    vector<string> justified = justify(words, 16);

    EXPECT_STREQ(justified.at(0).c_str(), "the  quick brown");
    EXPECT_STREQ(justified.at(1).c_str(), "fox  jumps  over");
    EXPECT_STREQ(justified.at(2).c_str(), "the   lazy   dog");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
