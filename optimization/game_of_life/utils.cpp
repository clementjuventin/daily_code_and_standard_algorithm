#include "utils.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <limits>

#define CELL_IDENTIFIER '#'
#define EMPTY_CELL_IDENTIFIER '.'
#define NEW_LINE '\n'

void display(const std::vector<std::vector<bool>> &state)
{
    std::cout << encode_table(state) << std::endl;
}

void display_v3(std::unordered_set<std::pair<int, int>, PairHash> &state)
{
    std::cout << encode_table_v3(state) << std::endl;
}

std::vector<std::vector<bool>> decode_table(const std::string &table)
{
    std::vector<std::vector<bool>> state;
    std::vector<bool> line;

    for (auto &c : table)
    {
        if (c == NEW_LINE)
        {
            state.push_back(line);
            line.clear();
        }
        else
            line.push_back(c == CELL_IDENTIFIER);
    }

    if (!line.empty())
        state.push_back(line);

    return state;
}

std::string encode_table(const std::vector<std::vector<bool>> &state)
{
    std::string table;
    for (const auto &row : state)
    {
        for (bool cell : row)
            table += (cell ? CELL_IDENTIFIER : EMPTY_CELL_IDENTIFIER);
        table += NEW_LINE;
    }
    return table;
}

std::unordered_set<std::pair<int, int>, PairHash> decode_table_v3(const std::string &table)
{
    std::unordered_set<std::pair<int, int>, PairHash> state;
    const size_t line_size = table.find(NEW_LINE) + 1;

    for (size_t i = 0, len = table.size(); i < len; ++i)
    {
        if (table[i] == CELL_IDENTIFIER)
        {
            int x = i % (line_size);
            int y = i / line_size;
            state.insert(std::pair(x, y));
        }
    }

    return state;
}

std::string encode_table_v3(std::unordered_set<std::pair<int, int>, PairHash> &state)
{
    int x_min{std::numeric_limits<int>::max()}, y_min{std::numeric_limits<int>::max()}, x_max{0}, y_max{0};
    for (auto &s : state)
    {
        x_min = std::min(x_min, s.first);
        y_min = std::min(y_min, s.second);
        x_max = std::max(x_max, s.first);
        y_max = std::max(y_max, s.second);
    }

    std::string table;
    for (int y = y_min - 1; y <= y_max + 1; ++y)
    {
        for (int x = x_min - 1; x <= x_max + 1; ++x)
            table += (state.find(std::pair(x, y)) != state.end() ? CELL_IDENTIFIER : EMPTY_CELL_IDENTIFIER);
        table += NEW_LINE;
    }
    return table;
}