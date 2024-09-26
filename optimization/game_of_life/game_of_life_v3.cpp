#include <gtest/gtest.h>
#include "game_of_life.hpp"

using namespace std;

void game_of_life_v3(std::unordered_set<pair<int, int>, PairHash> &state)
{
    unordered_multimap<pair<int, int>, size_t, PairHash> counters;
    vector<pair<int, int>> neighbors{pair{1, 0}, pair{-1, 0}, pair{0, -1}, pair{0, 1}, pair{1, 1}, pair{-1, -1}, pair{1, -1}, pair{-1, 1}};

    for (const auto &c : state)
    {
        for (const auto &n : neighbors)
        {
            std::pair<int, int> neighbor_pos = {c.first + n.first, c.second + n.second};
            auto ite = counters.find(neighbor_pos);
            if (ite != counters.end())
                ite->second++;
            else
                counters.insert({neighbor_pos, 1});
        }
    }

    for (const auto &counter : counters)
    {
        const int x = counter.first.first;
        const int y = counter.first.second;
        const bool s = state.find(counter.first) != state.end();
        if (s && (counter.second < 2 || 3 < counter.second))
            state.erase(counter.first);
        else if (!s && counter.second == 3)
            state.insert(counter.first);
    }
}
