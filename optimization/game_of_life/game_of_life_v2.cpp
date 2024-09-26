#include <gtest/gtest.h>
#include "game_of_life.hpp"

using namespace std;

void game_of_life_v2(std::vector<std::vector<bool>> &state)
{
    vector<vector<int>> array;
    vector<tuple<int, int>> neightbors{tuple{1, 0}, tuple{-1, 0}, tuple{0, -1}, tuple{0, 1}, tuple{1, 1}, tuple{-1, -1}, tuple{1, -1}, tuple{-1, 1}};

    const size_t size_y = state.size();
    if (size_y == 0)
        return;
    const size_t size_x = state[0].size();

    for (size_t j = 0; j < size_y; j++)
    {
        array.push_back(vector<int>(size_x, 0));
    }

    // Set weight array
    for (size_t j = 0; j < size_y; j++)
    {
        for (size_t i = 0; i < size_x; i++)
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
    for (int j = 0; j < size_y; j++)
    {
        for (int i = 0; i < size_x; i++)
        {
            if (state.at(j).at(i) && (array.at(j).at(i) < 2 || 3 < array.at(j).at(i)))
                state.at(j).at(i) = false;
            else if (!state.at(j).at(i) && array.at(j).at(i) == 3)
                state.at(j).at(i) = true;
            if (state.at(j).at(i))
            {
                push_x_front = (i == 0) || push_x_front;
                push_x_back = (i == (size_x - 1)) || push_x_back;
                push_y_front = (j == 0) || push_y_front;
                push_y_back = (j == (size_y - 1)) || push_y_back;
            }
        }
    }
    const size_t new_size_x = size_x + push_x_front + push_x_back;
    if (push_x_front)
    {
        for (int j = 0; j < size_y; j++)
        {
            state.at(j).insert(state.at(j).begin(), false);
            array.at(j).insert(array.at(j).begin(), false);
        }
    }
    if (push_x_back)
    {
        for (int j = 0; j < size_y; j++)
        {
            state.at(j).push_back(false);
            array.at(j).push_back(false);
        }
    }
    if (push_y_front)
    {
        state.insert(state.begin(), vector<bool>(new_size_x, false));
        array.insert(array.begin(), vector<int>(new_size_x, 0));
    }
    if (push_y_back)
    {
        state.push_back(vector<bool>(new_size_x, false));
        array.push_back(vector<int>(new_size_x, 0));
    }
}
