/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given an unordered list of flights taken by someone, each represented as (origin, destination) pairs, and a starting airport, compute the person's itinerary. If no such itinerary exists, return null. If there are multiple possible itineraries, return the lexicographically smallest one. All flights must be used in the itinerary.

For example, given the list of flights [('SFO', 'HKO'), ('YYZ', 'SFO'), ('YUL', 'YYZ'), ('HKO', 'ORD')] and starting airport 'YUL', you should return the list ['YUL', 'YYZ', 'SFO', 'HKO', 'ORD'].

Given the list of flights [('SFO', 'COM'), ('COM', 'YYZ')] and starting airport 'COM', you should return null.

Given the list of flights [('A', 'B'), ('A', 'C'), ('B', 'C'), ('C', 'A')] and starting airport 'A', you should return the list ['A', 'B', 'C', 'A', 'C'] even though ['A', 'C', 'A', 'B', 'C'] is also a valid itinerary. However, the first one is lexicographically smaller.
*/

#include <gtest/gtest.h>
#include <queue>
#include <stack>

using namespace std;

/**
 * Idea: We can perform hierholzer to see if the path exists.
 * Using a priority queue to always get the min stirng
 */
vector<string> *hierholzer(vector<pair<string, string>> &flights, string &&start)
{
    unordered_map<string, priority_queue<string, vector<string>, greater<string>>> flight_map;
    for (const auto &flight : flights)
        flight_map[flight.first].push(flight.second);

    vector<string> *result = new vector<string>();
    stack<string> stk;
    stk.push(start);

    while (!stk.empty())
    {
        string curr = stk.top();
        if (!flight_map[curr].empty())
        {
            stk.push(flight_map[curr].top());
            flight_map[curr].pop();
        }
        else
        {
            result->push_back(curr);
            stk.pop();
        }
    }

    if (result->size() != flights.size() + 1)
        return nullptr;

    reverse(result->begin(), result->end());
    return result;
}

TEST(HIERHOLZER, hierholzer)
{
    vector<pair<string, string>> flights{
        pair<string, string>({"A", "B"}),
        pair<string, string>({"A", "C"}),
        pair<string, string>({"B", "C"}),
        pair<string, string>({"C", "A"}),
    };

    vector<pair<string, string>> flights2{
        pair<string, string>({"B", "A"}),
        pair<string, string>({"A", "C"}),
    };

    vector<pair<string, string>> flights3{
        pair<string, string>({"Z", "A"}),
        pair<string, string>({"A", "D"}),
        pair<string, string>({"D", "C"}),
        pair<string, string>({"C", "A"}),
        pair<string, string>({"A", "B"}),
    };

    auto res = hierholzer(flights, string{"A"});
    auto res2 = hierholzer(flights2, string{"A"});
    auto res3 = hierholzer(flights3, string{"Z"});

    EXPECT_EQ(res->size(), 5);
    EXPECT_STREQ(res->at(0).c_str(), "A");
    EXPECT_STREQ(res->at(1).c_str(), "B");
    EXPECT_STREQ(res->at(2).c_str(), "C");
    EXPECT_STREQ(res->at(3).c_str(), "A");
    EXPECT_STREQ(res->at(4).c_str(), "C");
    EXPECT_EQ(res2, nullptr);
    EXPECT_EQ(res3->size(), 6);
    EXPECT_STREQ(res3->at(0).c_str(), "Z");
    EXPECT_STREQ(res3->at(1).c_str(), "A");
    EXPECT_STREQ(res3->at(2).c_str(), "D");
    EXPECT_STREQ(res3->at(3).c_str(), "C");
    EXPECT_STREQ(res3->at(4).c_str(), "A");
    EXPECT_STREQ(res3->at(5).c_str(), "B");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
