/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given the mapping a = 1, b = 2, ... z = 26, and an encoded message, count the number of ways it can be decoded.

For example, the message '111' would give 3, since it could be decoded as 'aaa', 'ka', and 'ak'.

You can assume that the messages are decodable. For example, '001' is not allowed.
*/

#include <gtest/gtest.h>

using namespace std;

int decode_possibilities(vector<int> *message)
{
    /*
    Idea: For the current element of the message:
    if it means something (ie !=0), we have at least the possibility to write the every previous possibilities + element
    if the current element associated with the previous one means something, we can considere it as a single element
    and add the amount of possibilities we had when we added the single previous element
    
    Time complexity: O(n)
    Space complexity: O(n)
    */
    const int sup_born = 26;
    if (message->size() == 0 || message->at(0) == 0)
        return 0;

    vector<int> dp;
    dp.push_back(1);
    dp.push_back(1);

    for (int i = 1; i < message->size(); i++)
    {
        int possibilities = 0;
        int e1 = message->at(i - 1);
        int e2 = message->at(i);
        int merge = e1 * 10 + e2;
        if (e2 != 0)
            possibilities += dp[i];
        if (merge >= 10 && merge <= 26)
            possibilities += dp[i - 1];

        dp.push_back(possibilities);
    }
    return dp.at(dp.size() - 1);
}

TEST(DECODE, decode)
{
    vector<int> array0{1, 9};
    vector<int> array1{1, 1, 1};
    vector<int> array2{1, 1, 1, 9, 9};
    vector<int> array3{2, 1, 0, 1};

    int result0 = decode_possibilities(&array0);
    int result1 = decode_possibilities(&array1);
    int result2 = decode_possibilities(&array2);
    int result3 = decode_possibilities(&array3);

    EXPECT_EQ(result0, 2);
    EXPECT_EQ(result1, 3);
    EXPECT_EQ(result2, 5);
    EXPECT_EQ(result3, 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
