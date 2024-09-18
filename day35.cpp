/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given an array of strictly the characters 'R', 'G', and 'B', segregate the values of the array so that all the Rs come first, the Gs come second, and the Bs come last. You can only swap elements of the array.

Do this in linear time and in-place.

For example, given the array ['G', 'B', 'R', 'R', 'B', 'R', 'G'], it should become ['R', 'R', 'R', 'G', 'G', 'B', 'B'].
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: For me we need to cound the number of R, G and B and then iterate again over the array, placing each character
 * at the right place
 *
 * TC: o(n)
 * SC: o(1)
 */

void rgb_order(string *rgb_string)
{
    uint r_count{0}, g_count{0}, b_count{0};
    for (char c : *rgb_string)
    {
        if (c == 'R')
            r_count++;
        if (c == 'G')
            g_count++;
        if (c == 'B')
            b_count++;
    }

    uint current_r_count{0}, current_g_count{0}, current_b_count{0};
    for (auto it = rgb_string->begin(); it != rgb_string->end(); ++it)
    {
        // cout << *rgb_string << " " << *it << " " << current_r_count << " " << current_g_count << " " << current_b_count << endl;
        char c = *it;
        if (*it == 'R' && (it < rgb_string->begin() || rgb_string->begin() + current_r_count <= it))
        {
            auto dest = rgb_string->begin() + current_r_count;
            *it = *dest;
            *dest = 'R';
            current_r_count += 1;
        }
        else if (*it == 'G' && (it < rgb_string->begin() + r_count || rgb_string->begin() + r_count + current_g_count <= it))
        {
            auto dest = rgb_string->begin() + r_count + current_g_count;
            *it = *dest;
            *dest = 'G';
            current_g_count += 1;
        }
        else if (*it == 'B' && (it < rgb_string->begin() + r_count + g_count || rgb_string->begin() + r_count + g_count + current_b_count <= it))
        {
            auto dest = rgb_string->begin() + r_count + g_count + current_b_count;
            *it = *dest;
            *dest = 'B';
            current_b_count += 1;
        }
    }
}

TEST(RGB_ORDER, rgb_order)
{
    string rgb1 = "RGBRGBRGB";
    string rgb2 = "GBRRBRG";

    rgb_order(&rgb1);
    rgb_order(&rgb2);

    EXPECT_STREQ(rgb1.c_str(), "RRRGGGBBB");
    EXPECT_STREQ(rgb2.c_str(), "RRRGGBB");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
