/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

Compute the running median of a sequence of numbers. That is, given a stream of numbers, print out the median of the list so far on each new element.

Recall that the median of an even-numbered list is the average of the two middle numbers.

For example, given the sequence [2, 1, 5, 7, 2, 0, 5], your algorithm should print out:

2
1.5
2
3.5
2
2
2

*/

#include <gtest/gtest.h>
#include <queue>

using namespace std;

/**
 * Idea: For me it's clear that we have to store every elements in memory because for an elements i we can add a
 * such elements that it become the median.
 * We can have two data structures storing each side of the elements from the stream (heaps)
 *
 * TC: o(nlog(n))
 * SC: o(n)
 */

void median(vector<int> stream)
{
    priority_queue<int> low;                             // Max-heap
    priority_queue<int, vector<int>, greater<int>> high; // Min-heap

    for (int i : stream)
    {
        // Insert
        if (low.empty() || i <= low.top())
            low.push(i);
        else
            high.push(i);
        // Balance
        if (low.size() > high.size() + 1)
        {
            high.push(low.top());
            low.pop();
        }
        else if (high.size() > low.size())
        {
            low.push(high.top());
            high.pop();
        }
        // Median
        int size = low.size() + high.size();
        if (size % 2 == 0)
            cout << (low.top() + high.top()) / 2.0 << endl;
        else
            cout << low.top() << endl;
    }
}

TEST(MEDIAN, median)
{
    vector<int> stream {2, 1, 5, 7, 2, 0, 5};

    median(stream);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
