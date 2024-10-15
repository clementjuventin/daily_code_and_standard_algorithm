/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

In a directed graph, each node is assigned an uppercase letter. We define a path's value as the number of most frequently-occurring letter along that path. For example, if a path in the graph goes through "ABACA", the value of the path is 3, since there are 3 occurrences of 'A' on the path.

Given a graph with n nodes and m directed edges, return the largest value path of the graph. If the largest value is infinite, then return null.

The graph is represented with a string and an edge list. The i-th character represents the uppercase letter of the i-th node. Each tuple in the edge list (i, j) means there is a directed edge from the i-th node to the j-th node. Self-edges are possible, as well as multi-edges.

For example, the following input graph:

ABACA

[(0, 1),
 (0, 2),
 (2, 3),
 (3, 4)]

Would have maximum value 3 using the path of vertices [0, 2, 3, 4], (A, A, C, A).

The following input graph:

A

[(0, 0)]

Should return null, since we have an infinite loop.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea:
 * Detect if there is a loop with Khan's algorithm and then if there is not we can just perform a 
 * DFS to check for the longest letter 
 */


TEST(LONGEST_FO_LETTER, longest_fo_letter)
{
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
