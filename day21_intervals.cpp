/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Snapchat.

Given an array of time intervals (start, end) for classroom lectures (possibly overlapping), find the minimum number of rooms required.

For example, given [(30, 75), (0, 50), (60, 150)], you should return 2.
*/

#include <gtest/gtest.h>
#include <deque>

using namespace std;

/**
 * Idea: I already had this one during an interview and unfortunatly I was not able to solve it :(
 * It's very simple once you understood you can represent the input as openning and closing intervals.
 * We need two lists with openning and closing intervals and we also need to sort them
 * Each time we pick the next closing/opening value and we increase or decrease by one a counter.
 * We assume, for this problem, that there is no need to have two rooms if a class ends at the same time another one starts
 * TC: O(nlog(n)) SC: O(n)
 */

int intervals(vector<tuple<int, int>> *time_intervals)
{
    deque<int> open;
    deque<int> close;

    for (auto &in : *time_intervals)
    {
        open.push_back(get<0>(in));
        close.push_back(get<1>(in));
    }

    sort(open.begin(), open.end());
    sort(close.begin(), close.end());

    uint count = 0;
    uint max = 0;
    for (size_t i = 0, len = time_intervals->size() * 2; i < len; i++)
    {
        if (open.front() < close.front())
        {
            open.pop_front();
            count += 1;
        }
        else
        {
            close.pop_front();
            count -= 1;
        }
        if (count > max)
            max = count;
    }
    return count;
}

TEST(INTERVALS, intervals)
{
    vector<tuple<int, int>> inter{{30, 75}, {0, 50}, {60, 150}};

    int res = intervals(&inter);

    EXPECT_EQ(res, 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
