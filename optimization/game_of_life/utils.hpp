#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include "game_of_life.hpp"

void display(const std::vector<std::vector<bool>> &state);
void display_v3(std::unordered_set<std::pair<int, int>, PairHash> &state);
std::vector<std::vector<bool>> decode_table(const std::string &table);
std::unordered_set<std::pair<int, int>, PairHash> decode_table_v3(const std::string &table);
std::string encode_table(const std::vector<std::vector<bool>> &state);
std::string encode_table_v3(std::unordered_set<std::pair<int, int>, PairHash> &state);
