/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Twitter.

You run an e-commerce website and want to record the last N order ids in a log. Implement a data structure to accomplish this, with the following API:

    record(order_id): adds the order_id to the log
    get_last(i): gets the ith last element from the log. i is guaranteed to be smaller than or equal to N.

You should be as efficient with time and space as possible.
*/

#include <gtest/gtest.h>
#include <deque>

using namespace std;

class Log
{
private:
    deque<uint> q;
    size_t capacity = 5;

public:
    void record(uint order_id)
    {
        if (q.size() == this->capacity)
        {
            q.pop_back();
        }
        q.push_front(order_id);
    }
    tuple<std::_Deque_iterator<uint, uint &, uint *>, std::_Deque_iterator<uint, uint &, uint *>> get_last(size_t i)
    {
        return {this->q.begin(), this->q.begin() + i};
    }
};

TEST(Log, log)
{
    Log logs;

    for (int i = 0; i<10; i++) {
        logs.record(i);
    }

    auto [begin, end] = logs.get_last(3);
    int i = 9;
    for (auto it = begin; it < end; it++) {
        EXPECT_EQ(*it, i);
        i--;
    }
EXPECT_EQ(i, 6);

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
