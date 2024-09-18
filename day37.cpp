/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

The power set of a set is the set of all its subsets. Write a function that, given a set, generates its power set.

For example, given the set {1, 2, 3}, it should return {{}, {1}, {2}, {3}, {1, 2}, {1, 3}, {2, 3}, {1, 2, 3}}.

You may also use a list or array to represent a set.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: Backtracking solution since we need to return every subsets
 *
 * TC: o(2^n)
 * SC: o(1)
 */

void subsets(vector<int> *s, set<int> *res, int i, vector<set<int>> *solutions)
{
    if (i >= s->size())
    {
        solutions->push_back(set(*res));
        return;
    }

    subsets(s, res, i + 1, solutions);
    res->insert(s->at(i));
    subsets(s, res, i + 1, solutions);
    res->erase(s->at(i));
}

TEST(SUBSETS, subsets)
{
    vector<int> s{1, 2, 3};
    set<int> res;
    vector<set<int>> solutions;

    subsets(&s, &res, 0, &solutions);

    EXPECT_EQ(solutions.size(), 8);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
