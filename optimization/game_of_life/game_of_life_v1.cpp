#include <gtest/gtest.h>
#include "game_of_life.hpp"

using namespace std;

void game_of_life_v1(std::vector<std::vector<bool>> &state)
{
    vector<vector<int>> array;
    vector<tuple<int, int>> neightbors{tuple{1, 0}, tuple{-1, 0}, tuple{0, -1}, tuple{0, 1}, tuple{1, 1}, tuple{-1, -1}, tuple{1, -1}, tuple{-1, 1}};

    // Copy the state
    for (int j = 0; j < state.size(); j++)
    {
        array.push_back(vector<int>(state.at(0).size(), 0));
    }

    if (state.size() == 0)
        return;

    uint width = state.at(0).size();
    uint height = state.size();

    // Set weight array
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (state.at(j).at(i))
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
            if (state.at(j).at(i) && (array.at(j).at(i) < 2 || 3 < array.at(j).at(i)))
                state.at(j).at(i) = false;
            else if (!state.at(j).at(i) && array.at(j).at(i) == 3)
                state.at(j).at(i) = true;
            if (state.at(j).at(i))
            {
                push_x_front = (i == 0) || push_x_front;
                push_x_back = (i == (width - 1)) || push_x_back;
                push_y_front = (j == 0) || push_y_front;
                push_y_back = (j == (height - 1)) || push_y_back;
            }
            array.at(j).at(i) = 0;
        }
    }
    width += push_x_front + push_x_back;
    if (push_x_front)
    {
        for (int j = 0; j < height; j++)
        {
            state.at(j).insert(state.at(j).begin(), false);
            array.at(j).insert(array.at(j).begin(), false);
        }
    }
    if (push_x_back)
    {
        for (int j = 0; j < height; j++)
        {
            state.at(j).push_back(false);
            array.at(j).push_back(false);
        }
    }
    if (push_y_front)
    {
        state.insert(state.begin(), vector<bool>(width, false));
        array.insert(array.begin(), vector<int>(width, 0));
    }
    if (push_y_back)
    {
        state.push_back(vector<bool>(width, false));
        array.push_back(vector<int>(width, 0));
    }
}
