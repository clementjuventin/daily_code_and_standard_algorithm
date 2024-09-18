/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

Given an integer k and a string s, find the length of the longest substring that contains at most k distinct characters.

For example, given s = "abcba" and k = 2, the longest substring with k distinct characters is "bcb".
*/

#include <gtest/gtest.h>
#include <string>
#include <queue>

using namespace std;

int find_substring(string word, int k)
{
    /*
    Idea: At first at was thinking about a dynamic programming solution but couldn't find it,
    then I decided to start by finding the obvious solution which was a backtracking solution.
    My also will do useless work since for the word abbbc adn k=2 it will compute abbb, bbbc, bbc, bc, c
    so there is probably a better solution

    I will create a reccursive function taking of not taking the letter. I will stop the reccursion
    and return the longest substring found when I reach the end of the word or there is a letter
    that makes the number of different letters > to k

    Ok I found another idea before implementing the backtracking solution:
    I take create a queue where I put the letters one by one. I will keep the maximum length
    of the queue as the solution. When I want to add a new letter and this letters makes the amount
    of different letters > k, I pop elements until one letter has no more occurence, for this
    I have a dictionnary counting the number of occurence for each letter

    Time complexity: O(n)
    Space Complexity: O(n)

    Correction: Instead of using a queue we can use pointers to elements of the string 
    */
    queue<char> q;
    unordered_map<char, int> occurencies;
    size_t max_len = 0;

    for (auto it = word.begin(); it != word.end(); ++it)
    {
        char next_letter = *it;
        q.push(next_letter);
        auto occ_it = occurencies.find(next_letter);
        // Letter not found (ie: new letter)
        if (occ_it == occurencies.end())
        {
            // Add a new letter
            occurencies.insert({next_letter, 1});
            k -= 1;
            // Remove letters until k is valid
            while (k < 0)
            {
                char poped = q.front();
                q.pop();

                auto poped_it = occurencies.find(poped);
                poped_it->second -= 1;
                if (poped_it->second == 0)
                {
                    occurencies.erase(poped);
                    k += 1;
                }
            }
        }
        else
        {
            occ_it->second += 1;
        }
        max_len = max(max_len, q.size());
    }

    return int(max_len);
}

TEST(FIND_SUBSTRING, find_substring)
{
    string s1 {"abbbac"};
    string s2 {"abcba"};

    int res1 = find_substring(s1, 1);
    int res2 = find_substring(s1, 2);
    int res3 = find_substring(s1, 4);
    int res4 = find_substring(s2, 1);
    int res5 = find_substring(s2, 2);

    EXPECT_EQ(res1, 3);
    EXPECT_EQ(res2, 5);
    EXPECT_EQ(res3, 6);
    EXPECT_EQ(res4, 1);
    EXPECT_EQ(res5, 3);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
