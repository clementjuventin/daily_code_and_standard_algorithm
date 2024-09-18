#include <gtest/gtest.h>

using namespace std;

/*
KMP algo is used to find a certain pattern within a string.

TC: O(n+m) with n = string length and m = pattern length
SC: O(m)

The goal of precomputing lps is to spot suffixes also appearing as prefixes
Here are some examples:
    For the pattern “AAAA”, lps[] is [0, 1, 2, 3]
        -> A¹ is matching nothing, ie 0
        -> A² is matching the previous A, ie 1 (first element)
        -> A³ is matching the first element but also, A²A³ is matching A¹A², ie 2 (second element)
        -> A²A³A⁴ matching A¹A²A³, ie 3
    For the pattern “ABCDE”, lps[] is [0, 0, 0, 0, 0]
        -> No match
    For the pattern “AABAACAABAA”, lps[] is [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]
        -> A¹, 0
        -> A² match A¹, 1
        -> B³ match nothing, 0
        -> A⁴ match A¹, 1
        -> A⁴A⁵ match A¹1², 2
        -> ...
    For the pattern “AAACAAAAAC”, lps[] is [0, 1, 2, 0, 1, 2, 3, 3, 3, 4] 
    For the pattern “AAABAAA”, lps[] is [0, 1, 2, 0, 1, 2, 3]

*/

// Fills lps[] for given pattern pat
void compute_lps(string &pat, int M, vector<int> &lps)
{
    // Length of the previous longest prefix suffix
    int len = 0;

    // lps[0] is always 0
    lps[0] = 0;

    // loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M)
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // Decrease to see if the current element match a smaller prefix
            if (len != 0)
                len = lps[len - 1];
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of pat in txt
vector<int> kmp_search(string &pat, string &txt)
{
    int M = pat.length();
    int N = txt.length();

    // Create lps[] that will hold the longest prefix suffix
    // values for pattern
    vector<int> lps(M);
    vector<int> result;

    // Preprocess the pattern (calculate lps[] array)
    compute_lps(pat, M, lps);

    int i = 0; // index for txt
    int j = 0; // index for pat
    while ((N - i) >= (M - j))
    {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }

        if (j == M)
        {
            result.push_back(i - j + 1);
            j = lps[j - 1];
        }

        // Mismatch after j matches
        else if (i < N && pat[j] != txt[i])
        {
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    return result;
}

TEST(KMP, kmp)
{
    string txt = "abcabcdabcabcd";
    string pat = "abcd";
    vector<int> result = kmp_search(pat, txt);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result.at(0), 4);
    EXPECT_EQ(result.at(1), 11);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
