/*
On our special chessboard, two bishops attack each other if they share the same diagonal. This includes bishops that have another bishop located between them, i.e. bishops can attack through pieces.

You are given N bishops, represented as (row, column) tuples on a M by M chessboard. Write a function to count the number of pairs of bishops that attack each other. The ordering of the pair doesn't matter: (1, 2) is considered the same as (2, 1).

For example, given M = 5 and the list of bishops:

    (0, 0)
    (1, 2)
    (2, 2)
    (4, 0)

The board would look like this:

[b 0 0 0 0]
[0 0 b 0 0]
[0 0 b 0 0]
[0 0 0 0 0]
[b 0 0 0 0]

You should return 2, since bishops 1 and 3 attack each other, as well as bishops 3 and 4.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea:
 * We can iterate over all diagonals and count the number of bishops. Then we add to the result the number of bishops less one (with a min value of 0)
 * 
 * TC: o(m2) 
 * SC: o(m2)
 */

size_t count_bishops(vector<pair<size_t, size_t>> &bishops, size_t m){
    vector<vector<bool>> game(m, vector(m, false));
    for(auto &e: bishops){
        game[e.second][e.first]= true;
    }
    size_t total = 0;
    for(size_t i = 0; i < m; i++){
        size_t h1 = 0;
        size_t h2 = 0;
        for(size_t j = 0; j <= i; j++){
            h1+=game[j][i-j];
            h2+=game[m-1-i+j][j];
        }
        if (h1 > 1)
            total += h1-1;
        if (h2 > 1)
            total += h2-1;
    }
    return total;
}


TEST(BISHOPS, bishops)
{
    vector<pair<size_t,size_t>> b {pair<size_t, size_t>(0, 0),pair<size_t,size_t>(1, 2),pair<size_t,size_t>(2, 2),pair<size_t,size_t>(4, 0)};
    size_t res = count_bishops(b, 5);
    EXPECT_EQ(res, 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
