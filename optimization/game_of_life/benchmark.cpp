#include <benchmark/benchmark.h>
#include "game_of_life.hpp"
#include "utils.hpp"
#include <iostream>

const std::string biloaf{"......\n...#..\n..#.#.\n.#..#.\n..##..\n.#..#.\n.#.#..\n..#...\n......\n"};
const std::string block{"....\n.##.\n.##.\n....\n"};
const std::string blinker{".....\n.###.\n.....\n"};
const std::string glider{".....\n...#.\n.#.#.\n..##.\n.....\n"};
const std::string eater_1{"......\n.##...\n.#.#..\n...#..\n...##.\n......\n"};
const std::string herschel{".....\n.#...\n.###.\n.#.#.\n...#.\n.....\n"};

void run_benchmark(benchmark::State &state, const std::function<void(std::vector<std::vector<bool>> &)> &game_of_life_func, const std::string string_table, const size_t iterations = 10)
{
    std::vector<std::vector<bool>> table = decode_table(string_table);

    for (auto _ : state)
    {
        std::vector<std::vector<bool>> current_table = table;
        for (int i = 0; i < iterations; i++)
        {
            // display(current_table);
            game_of_life_func(current_table);
        }
    }
}

void run_benchmark_v3(benchmark::State &state, const std::function<void(std::unordered_set<std::pair<int, int>, PairHash> &)> &game_of_life_func, const std::string string_table, const size_t iterations = 10)
{
    std::unordered_set<std::pair<int, int>, PairHash> table = decode_table_v3(string_table);

    for (auto _ : state)
    {
        std::unordered_set<std::pair<int, int>, PairHash> current_table = table;
        for (int i = 0; i < iterations; i++)
        {
            // display_v3(current_table);
            game_of_life_func(current_table);
        }
    }
}

static void BM_V1_BILOAF(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v1, biloaf);
}

static void BM_V2_BILOAF(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v2, biloaf);
}

static void BM_V3_BILOAF(benchmark::State &state)
{
    run_benchmark_v3(state, game_of_life_v3, biloaf);
}

static void BM_V1_BLOCK(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v1, block);
}

static void BM_V2_BLOCK(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v2, block);
}

static void BM_V3_BLOCK(benchmark::State &state)
{
    run_benchmark_v3(state, game_of_life_v3, block);
}

static void BM_V1_BLINKER(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v1, blinker);
}

static void BM_V2_BLINKER(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v2, blinker);
}

static void BM_V3_BLINKER(benchmark::State &state)
{
    run_benchmark_v3(state, game_of_life_v3, blinker);
}

static void BM_V1_GLIDER(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v1, glider);
}

static void BM_V2_GLIDER(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v2, glider);
}

static void BM_V3_GLIDER(benchmark::State &state)
{
    run_benchmark_v3(state, game_of_life_v3, glider);
}

static void BM_V1_EATER_1(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v1, eater_1);
}

static void BM_V2_EATER_1(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v2, eater_1);
}

static void BM_V3_EATER_1(benchmark::State &state)
{
    run_benchmark_v3(state, game_of_life_v3, eater_1);
}

static void BM_V1_HERSCHEL(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v1, herschel);
}

static void BM_V2_HERSCHEL(benchmark::State &state)
{
    run_benchmark(state, game_of_life_v2, herschel);
}

static void BM_V3_HERSCHEL(benchmark::State &state)
{
    run_benchmark_v3(state, game_of_life_v3, herschel);
}

BENCHMARK(BM_V1_BILOAF);
BENCHMARK(BM_V1_BLOCK);
BENCHMARK(BM_V1_BLINKER);
BENCHMARK(BM_V1_GLIDER);
BENCHMARK(BM_V1_EATER_1);
BENCHMARK(BM_V1_HERSCHEL);
BENCHMARK(BM_V2_BILOAF);
BENCHMARK(BM_V2_BLOCK);
BENCHMARK(BM_V2_BLINKER);
BENCHMARK(BM_V2_GLIDER);
BENCHMARK(BM_V2_EATER_1);
BENCHMARK(BM_V2_HERSCHEL);
BENCHMARK(BM_V3_BILOAF);
BENCHMARK(BM_V3_BLOCK);
BENCHMARK(BM_V3_BLINKER);
BENCHMARK(BM_V3_GLIDER);
BENCHMARK(BM_V3_EATER_1);
BENCHMARK(BM_V3_HERSCHEL);

BENCHMARK_MAIN();
