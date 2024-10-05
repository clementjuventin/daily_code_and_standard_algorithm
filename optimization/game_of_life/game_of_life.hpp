#pragma once
#include <unordered_set>
#include <vector>

struct PairHash
{
    template <typename T1, typename T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const
    {
        return std::hash<T1>()(p.first) ^ (std::hash<T2>()(p.second) << 1);
    }
};

void game_of_life_v1(std::vector<std::vector<bool>> &state);
void game_of_life_v2(std::vector<std::vector<bool>> &state);
void game_of_life_v3(std::unordered_set<std::pair<int, int>, PairHash> &state);

void game_of_life_v4(void *state, size_t width, size_t height, unsigned int iterations);