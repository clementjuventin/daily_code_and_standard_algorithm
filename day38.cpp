/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

You have an N by N board. Write a function that, given N, returns the number of possible arrangements of the board where N queens can be placed on the board without threatening each other, i.e. no two queens share the same row, column, or diagonal.
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
