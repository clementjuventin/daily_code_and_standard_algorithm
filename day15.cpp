/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a stream of elements too large to store in memory, pick a random element from the stream with uniform probability.
*/

#include <gtest/gtest.h>
#include <stdlib.h>

using namespace std;

int r_sample(const vector<int> *stream)
{
    /*
    Idea: The algo solution is called reservoir sampling (k=1)
    Let's represent the stream as a vector and not use it's size
    */
    int i = 1;
    auto it = stream->begin();
    int reservoir = *it;
    while (it != stream->end())
    {
        ++it;
        ++i;
        int index = rand() % i;
        if (index == 0)
            reservoir = *it;
    }
    return reservoir;
}

TEST(SAMPLE, r_sample)
{
    srand(1);

    const vector<int> s{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
    int sum = 0;

    for (int i = 0; i < 1000000; i++)
    {
        sum += r_sample(&s);
    }

    // It seems good
    cout << sum << endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
