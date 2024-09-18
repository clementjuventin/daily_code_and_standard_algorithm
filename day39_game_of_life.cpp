/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Dropbox.

Conway's Game of Life takes place on an infinite two-dimensional board of square cells. Each cell is either dead or alive, and at each tick, the following rules apply:

    Any live cell with less than two live neighbours dies.
    Any live cell with two or three live neighbours remains living.
    Any live cell with more than three live neighbours dies.
    Any dead cell with exactly three live neighbours becomes a live cell.

A cell neighbours another cell if it is horizontally, vertically, or diagonally adjacent.

Implement Conway's Game of Life. It should be able to be initialized with a starting list of live cell coordinates and the number of steps it should run for. Once initialized, it should print out the board state at each step. Since it's an infinite board, print out only the relevant coordinates, i.e. from the top-leftmost live cell to bottom-rightmost live cell.

You can represent a live cell with an asterisk (*) and a dead cell with a dot (.).
*/

#include <gtest/gtest.h>
#include <deque>
#include <chrono>
#include <thread>

using namespace std;

void game_of_life(vector<vector<bool>> initial_state, uint iterations)
{
    int current_iteration = 0;
    vector<vector<bool>> life;
    vector<vector<int>> array;
    vector<tuple<int, int>> neightbors{tuple{1, 0}, tuple{-1, 0}, tuple{0, -1}, tuple{0, 1}, tuple{1, 1}, tuple{-1, -1}, tuple{1, -1}, tuple{-1, 1}};

    for (int j = 0; j < initial_state.size(); j++)
    {
        life.push_back(vector<bool>(initial_state.at(0).size(), false));
        array.push_back(vector<int>(initial_state.at(0).size(), 0));
        for (int i = 0; i < initial_state.at(0).size(); i++)
            life.at(j).at(i) = initial_state.at(j).at(i);
    }

    while (current_iteration < iterations)
    {
        current_iteration++;
        if (life.size() == 0)
            break;

        uint width = life.at(0).size();
        uint height = life.size();

        // Display
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
                cout << (life.at(j).at(i) ? '0' : '_');
            cout << endl;
        }
        cout << "-------------------------------" << endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Set weight array
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (life.at(j).at(i))
                {
                    for (tuple<int, int> n : neightbors)
                    {
                        int n_x = i + get<0>(n);
                        int n_y = j + get<1>(n);
                        array.at(n_y).at(n_x) += 1;
                    }
                }
            }
        }

        bool push_x_front = false;
        bool push_x_back = false;
        bool push_y_front = false;
        bool push_y_back = false;
        // Set cells
        for (int j = 0; j < height; j++)
        {
            for (int i = 0; i < width; i++)
            {
                if (life.at(j).at(i) && (array.at(j).at(i) < 2 || 3 < array.at(j).at(i)))
                    life.at(j).at(i) = false;
                else if (!life.at(j).at(i) && array.at(j).at(i) == 3)
                    life.at(j).at(i) = true;
                if (life.at(j).at(i))
                {
                    push_x_front = (i == 0) || push_x_front;
                    push_x_back = (i == (width - 1)) || push_x_back;
                    push_y_front = (j == 0) || push_y_front;
                    push_y_back = (j == (height - 1)) || push_y_back;
                }
                array.at(j).at(i) = 0;
            }
        }
        if (push_x_front)
        {
            for (int j = 0; j < height; j++)
            {
                life.at(j).insert(life.at(j).begin(), false);
                array.at(j).insert(array.at(j).begin(), false);
            }
        }
        if (push_x_back)
        {
            for (int j = 0; j < height; j++)
            {
                life.at(j).push_back(false);
                array.at(j).push_back(false);
            }
        }
        if (push_y_front)
        {
            life.insert(life.begin(), vector<bool>(width, false));
            array.insert(array.begin(), vector<int>(width, 0));
        }
        if (push_y_back)
        {
            life.push_back(vector<bool>(width, false));
            array.push_back(vector<int>(width, 0));
        }
    }
}

TEST(GAME_OF_LIFE, game_of_life)
{
    vector<bool> l0 = {false, false, false, false, false, false};
    vector<bool> l1 = {false, false, false, true, false, false};
    vector<bool> l2 = {false, false, true, false, true, false};
    vector<bool> l3 = {false, true, false, false, true, false};
    vector<bool> l4 = {false, false, true, true, false, false};
    vector<bool> l5 = {false, true, false, false, true, false};
    vector<bool> l6 = {false, true, false, true, false, false};
    vector<bool> l7 = {false, false, true, false, false, false};
    vector<bool> l8 = {false, false, false, false, false, false};
    vector<vector<bool>> biloaf{l0, l1, l2, l3, l4, l5, l6, l7, l8};
    game_of_life(biloaf, 10);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
