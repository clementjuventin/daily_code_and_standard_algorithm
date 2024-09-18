/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

You are given an M by N matrix consisting of booleans that represents a board. Each True boolean represents a wall. Each False boolean represents a tile you can walk on.

Given this matrix, a start coordinate, and an end coordinate, return the minimum number of steps required to reach the end coordinate from the start. If there is no possible path, then return null. You can move up, left, down, and right. You cannot move through walls. You cannot wrap around the edges of the board.

For example, given the following board:

[[f, f, f, f],
[t, t, f, t],
[f, f, f, f],
[f, f, f, f]]

and start = (3, 0) (bottom left) and end = (0, 0) (top left), the minimum number of steps required to reach the end is 7, since we would need to go through (1, 2) because there is a wall everywhere else on the second row.
*/

#include <gtest/gtest.h>
#include <deque>

using namespace std;

vector<tuple<int, int>> get_neightbours(vector<vector<bool>> *map, tuple<int, int> position, int height, int width)
{
    vector<tuple<int, int>> directions{tuple<int, int>(1, 0), tuple<int, int>(0, 1), tuple<int, int>(-1, 0), tuple<int, int>(0, -1)};
    vector<tuple<int, int>> neightbours;

    for (auto it = directions.begin(); it < directions.end(); it++)
    {
        int x = get<0>(position);
        int y = get<1>(position);
        int x_direction = get<0>(*it);
        int y_direction = get<1>(*it);
        int next_pos_x = x + x_direction;
        int next_pos_y = y + y_direction;
        if (next_pos_x < 0 || next_pos_x >= width || next_pos_y < 0 || next_pos_y >= height)
            continue;
        if (!map->at(next_pos_y).at(next_pos_x))
            neightbours.push_back(tuple(next_pos_x, next_pos_y));
    }
    return neightbours;
}

/**
 * Idea: Dijkstra
 */

int dijkstra(vector<vector<bool>> *map, tuple<int, int> start, tuple<int, int> end)
{
    size_t width = map->at(0).size();
    size_t height = map->size();

    int x = get<0>(start);
    int y = get<1>(start);

    vector<vector<int>> grid;
    vector<vector<bool>> visited;
    deque<tuple<int, tuple<int, int>>> next;
    for (int i = 0; i < height; i++)
    {
        grid.push_back(vector<int>(width, -1));
        visited.push_back(vector<bool>(width, false));
    }

    grid.at(y).at(x) = 0;
    next.push_back(tuple(0, start));
    while (!next.empty())
    {
        auto element = next.front();
        next.pop_front();
        int weight = get<0>(element);
        auto position = get<1>(element);
        int x_next = get<0>(position);
        int y_next = get<1>(position);

        if (visited.at(y_next).at(x_next))
            continue;
        visited.at(y_next).at(x_next) = true;

        auto neightbours = get_neightbours(map, position, height, width);
        for (auto it = neightbours.begin(); it < neightbours.end(); it++)
        {
            int x_neightbour = get<0>(*it);
            int y_neightbour = get<1>(*it);
            if (visited.at(y_neightbour).at(x_neightbour))
                continue;
            if (grid.at(y_neightbour).at(x_neightbour) == -1 || grid.at(y_neightbour).at(x_neightbour) > weight + 1)
            {
                grid.at(y_neightbour).at(x_neightbour) = weight + 1;
                next.push_back(tuple(grid.at(y_neightbour).at(x_neightbour), *it));
            }
        }
    }

    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //         cout << grid.at(i).at(j) << " ";
    //     cout << endl;
    // }

    return grid.at(get<1>(end)).at(get<0>(end));
}

TEST(DIJKSTRA, dijkstra)
{
    vector<bool> line_1{false, true, false, false};
    vector<bool> line_2{false, true, false, true};
    vector<bool> line_3{false, false, false, false};
    vector<bool> line_4{false, false, false, false};
    vector<vector<bool>> map{line_1, line_2, line_3, line_4};

    int cost = dijkstra(&map, tuple(3, 0), tuple(0, 0));

    EXPECT_EQ(cost, 7);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
