/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

Implement a URL shortener with the following methods:

    shorten(url), which shortens the url into a six-character alphanumeric string, such as zLg6wl.
    restore(short), which expands the shortened string into the original url. If no such shortened string exists, return null.

Hint: What if we enter the same URL twice?
*/

/**
 * Idea: I can use a hashmap and an hashing function to generate keys.
 * It is not specified if we need to handle collisions. I suppose than we don't have to but if so, depending on the need,
 * we can either store a list of values (if we want to keep the data at all costs) or rehash the value until we reach a free cell
 */

#include <gtest/gtest.h>
#include <unordered_map>

using namespace std;

class UrlShortener
{
    unordered_map<string, string> urls;
    hash<string> hasher;

public:
    string shorten(string url)
    {
        // Is the modulo useful?
        size_t hash = hasher(url) % (1ULL << (6 * 8)); // 6 * 8 bits (1 byte = 1 char)
        char str[6];
        for (int i = 0; i < 6; ++i)
            str[i] = static_cast<char>((hash >> (i * 8)) & 0xFF);

        string short_url = string(str);
        urls.insert({short_url, url});
        return short_url;
    }
    string restore(string hash)
    {
        return urls[hash];
    }
};

TEST(URL_SHORTENER, url_shortener)
{
    UrlShortener us;

    string s = us.shorten("http://localhost:3000/health");
    string s1 = us.shorten("http://localhost:3000/health");
    string s2 = us.shorten("http://localhost:3000/user");

    EXPECT_STREQ(s.c_str(), "%\xA9\x9B'\x84\x93");
    EXPECT_STREQ(s1.c_str(), s.c_str());
    EXPECT_STREQ(s2.c_str(), "$\x5_b\x2S");
    EXPECT_STREQ(us.restore(s).c_str(), "http://localhost:3000/health");
    EXPECT_STREQ(us.restore(s2).c_str(), "http://localhost:3000/user");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}