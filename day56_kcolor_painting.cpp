/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given an undirected graph represented as an adjacency matrix and an integer k, write a function to determine whether each vertex in the graph can be colored such that no two adjacent vertices share the same color using at most k colors.
*/

/**
 * Idea: Backtracking
 * 
 * KColor problem is known to be an np problem. There is more efficient heuristics approach
 */

#include <gtest/gtest.h>
#include <unordered_set>
#include <numeric>

using namespace std;

bool recursive_call(const vector<vector<bool>> &adjency_matrix, vector<int> &color_map, int vertice, int k)
{
    if (vertice >= adjency_matrix.size())
        return true;
    unordered_set<int> colors;
    for (int i = 0; i < k; i++)
        colors.insert(i);
    for (size_t i = 0, len = adjency_matrix.size(); i < len; i++)
    {
        if (adjency_matrix[vertice][i])
            colors.erase(color_map[i]);
    }
    for (auto &c : colors)
    {
        color_map[vertice] = c;
        if (recursive_call(adjency_matrix, color_map, vertice + 1, k))
            return true;
        color_map[vertice] = -1;
    }
    return false;
}

bool kcolor_painting(vector<vector<bool>> &adjency_matrix, int k)
{
    vector<int> colors_map(adjency_matrix.size(), -1);

    return recursive_call(adjency_matrix, colors_map, 0, k);
}

TEST(KCOLOR, kcolor)
{
    vector<vector<bool>> adjency_matrix {
        vector<bool>{0, 1, 1, 0, 0},
        vector<bool>{1, 0, 1, 0, 1},
        vector<bool>{1, 1, 0, 1, 0},
        vector<bool>{0, 0, 1, 0, 1},
        vector<bool>{0, 1, 0, 1, 0},
    };

    EXPECT_EQ(kcolor_painting(adjency_matrix, 1), false);
    EXPECT_EQ(kcolor_painting(adjency_matrix, 2), false);
    EXPECT_EQ(kcolor_painting(adjency_matrix, 3), true);
    EXPECT_EQ(kcolor_painting(adjency_matrix, 4), true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}