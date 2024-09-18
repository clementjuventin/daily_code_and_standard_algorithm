/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

Run-length encoding is a fast and simple method of encoding strings. The basic idea is to represent repeated successive characters as a single count and character. For example, the string "AAAABBBCCDAA" would be encoded as "4A3B2C1D2A".

Implement run-length encoding and decoding. You can assume the string to be encoded have no digits and consists solely of alphabetic characters. You can assume the string to be decoded is valid.
*/

#include <gtest/gtest.h>
#include <string>

using namespace std;

/**
 * encode/decode
 * TC: o(n)
 * SC: o(n)
 */

string encode(string s)
{
    string encoded;

    int counter = 0;
    char last_char = ' ';
    for (char c : s)
    {
        if (c == last_char)
        {
            counter += 1;
            continue;
        }
        if (counter > 0)
            encoded += to_string(counter) + last_char;
        last_char = c;
        counter = 1;
    }
    encoded += to_string(counter) + last_char;
    return encoded;
}

string decode(string s)
{
    string decoded;

    for (int i = 0; i < s.size(); i += 2)
    {
        int occurences = atoi(string{s.at(i)}.c_str());
        char c = s.at(i + 1);
        decoded += string(occurences, c);
    }
    return decoded;
}

TEST(ENCODE_DECODE, encode_decode)
{
    string deco{"AAAABBBCCDAA"};
    string enco{"4A3B2C1D2A"};

    EXPECT_STREQ(encode(deco).c_str(), enco.c_str());
    EXPECT_STREQ(decode(enco).c_str(), deco.c_str());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
