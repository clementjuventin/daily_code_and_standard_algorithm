/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

A knight's tour is a sequence of moves by a knight on a chessboard such that all squares are visited once.

Given N, write a function to return the number of knight's tours on an N by N chessboard.
*/

#include <gtest/gtest.h>

using namespace std;

void display_game(vector<vector<bool>> &game)
{
    for (auto &array : game)
    {
        for (int i = 0; i < array.size(); i++)
            cout << (array[i] ? "X" : ".");
        cout << endl;
    }
    cout << "--------------------" << endl;
}

int ite(vector<pair<int, int>> &knight_move, vector<vector<bool>> &game, pair<int, int> pos, int n, int target)
{
    if (target <= 1)
        return 1;
    game[pos.first][pos.second] = true;
    int count = 0;
    for (auto &m : knight_move)
    {
        pair<int, int> next = pair<int, int>(pos.first + m.first, pos.second + m.second);
        if (next.first < 0 || next.first >= n || next.second < 0 || next.second >= n)
            continue;
        if (game[next.first][next.second])
            continue;
        count += ite(knight_move, game, next, n, target - 1);
    }

    game[pos.first][pos.second] = false;
    return count;
}

/**
 * Idea: Backtracking
 * 
 * TC: n^n
 * SC: n²
 */
int knight_tour(int n)
{
    vector<pair<int, int>> knight_move{
        pair<int, int>(2, 1),
        pair<int, int>(2, -1),
        pair<int, int>(-2, 1),
        pair<int, int>(-2, -1),
        pair<int, int>(1, -2),
        pair<int, int>(-1, -2),
        pair<int, int>(1, 2),
        pair<int, int>(-1, 2)};

    vector<vector<bool>> game(n, vector<bool>(n, false));

    int count = 0;
    int sup_i = n / 2 + (n % 2 == 1);
    int sup_j = n / 2;
    for (int i = 0; i < sup_i; i++)
    {
        for (int j = 0; j < sup_j; j++)
        {
            pair<int, int> start_pos = pair<int, int>(i, j);
            int res = ite(knight_move, game, start_pos, n, n * n);
            count += res * 4;
        }
    }
    if (n % 2 == 1)
        count += ite(knight_move, game, pair<int, int>(n / 2, n / 2), n, n * n);
    return count;
}

TEST(KNIGHT_TOUR, knight_tour)
{
    EXPECT_EQ(knight_tour(2), 0);
    EXPECT_EQ(knight_tour(3), 0);
    EXPECT_EQ(knight_tour(4), 0);
    EXPECT_EQ(knight_tour(5), 1728);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
