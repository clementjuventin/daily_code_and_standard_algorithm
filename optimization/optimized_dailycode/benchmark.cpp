#include <benchmark/benchmark.h>
#include <iostream>
#include <vector>
#include <numeric>
#include <limits>
#include <random>

#include "day1.hpp"
#include "day2.hpp"
#include "day4.hpp"

static std::vector<int> generate_random_array(size_t size, unsigned seed = 1)
{
    std::vector<int> array(size);
    std::mt19937 rng(seed); // Mersenne Twister RNG
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    for (auto &element : array)
        element = dist(rng);

    return array;
}

// This initializes the random arrays once
static std::vector<int> random_huge_array = generate_random_array(10000000);
static std::vector<int> random_big_array = generate_random_array(10000);
static std::vector<int> random_medium_array = generate_random_array(1000);
static std::vector<int> random_small_array = generate_random_array(10);

// Benchmarking function (generic)
static void benchmark_sum_2(benchmark::State &state, const std::vector<int> &array, const int k, bool (*sum_func)(std::vector<int> &, const int))
{
    for (auto _ : state)
    {
        std::vector<int> array_cpy = std::vector(array);
        sum_func(array_cpy, k);
    }
}

static void benchmark_mult(benchmark::State &state, const std::vector<int> &array, void (*mult_func)(std::vector<int> &))
{
    for (auto _ : state)
    {
        std::vector<int> array_cpy = std::vector(array);
        mult_func(array_cpy);
    }
}

static void benchmark_mult_o2plus_variant(benchmark::State &state, const std::vector<int> &array, void (*mult_func)(const std::vector<int> &, std::vector<int> &))
{
    std::vector<int> result = std::vector(array.size(), 0);

    for (auto _ : state)
    {
        const std::vector<int> array_cpy = std::vector(array);
        mult_func(array_cpy, result);
    }
}

static void benchmark_missing_int(benchmark::State &state, const std::vector<int> &array, int (*func)(std::vector<int> &))
{
    for (auto _ : state)
    {
        std::vector<int> array_cpy = std::vector(array);
        func(array_cpy);
    }
}

template <typename T>
void register_benchmarks_sum(const std::string &name, const std::vector<int> &array, T sum_func)
{
    benchmark::RegisterBenchmark((name + "_min").c_str(), benchmark_sum_2, std::ref(array), std::numeric_limits<int>::min(), sum_func);
    benchmark::RegisterBenchmark((name + "_max").c_str(), benchmark_sum_2, std::ref(array), std::numeric_limits<int>::max(), sum_func);
    benchmark::RegisterBenchmark((name + "_0").c_str(), benchmark_sum_2, std::ref(array), 0, sum_func);
}

template <typename T, typename BenchmarkFunc>
void register_benchmarks_mult(const std::string &name, const std::vector<int> &array, T func, BenchmarkFunc benchmark_func)
{
    benchmark::RegisterBenchmark(name.c_str(), benchmark_func, std::ref(array), func);
}

template <typename T>
void register_benchmarks_missing_int(const std::string &name, const std::vector<int> &array, T func)
{
    benchmark::RegisterBenchmark(name.c_str(), benchmark_missing_int, std::ref(array), func);
}

int main(int argc, char **argv)
{
    // Register benchmarks for sum functions
    register_benchmarks_sum("DAY_1_00_huge_array", random_huge_array, sum_2);
    register_benchmarks_sum("DAY_1_00_big_array", random_big_array, sum_2);
    register_benchmarks_sum("DAY_1_00_medium_array", random_medium_array, sum_2);
    register_benchmarks_sum("DAY_1_00_small_array", random_small_array, sum_2);

    register_benchmarks_sum("DAY_1_01_huge_array", random_huge_array, sum_2_o1);
    register_benchmarks_sum("DAY_1_01_big_array", random_big_array, sum_2_o1);
    register_benchmarks_sum("DAY_1_01_medium_array", random_medium_array, sum_2_o1);
    register_benchmarks_sum("DAY_1_01_small_array", random_small_array, sum_2_o1);

    register_benchmarks_sum("DAY_1_02_huge_array", random_huge_array, sum_2_o2);
    register_benchmarks_sum("DAY_1_02_big_array", random_big_array, sum_2_o2);
    register_benchmarks_sum("DAY_1_02_medium_array", random_medium_array, sum_2_o2);
    register_benchmarks_sum("DAY_1_02_small_array", random_small_array, sum_2_o2);

    // Register benchmarks for multiplication functions
    register_benchmarks_mult("DAY_2_00_huge_array", random_huge_array, mult, benchmark_mult);
    register_benchmarks_mult("DAY_2_00_big_array", random_big_array, mult, benchmark_mult);
    register_benchmarks_mult("DAY_2_00_medium_array", random_medium_array, mult, benchmark_mult);
    register_benchmarks_mult("DAY_2_00_small_array", random_small_array, mult, benchmark_mult);

    register_benchmarks_mult("DAY_2_01_huge_array", random_huge_array, mult_o1, benchmark_mult);
    register_benchmarks_mult("DAY_2_01_big_array", random_big_array, mult_o1, benchmark_mult);
    register_benchmarks_mult("DAY_2_01_medium_array", random_medium_array, mult_o1, benchmark_mult);
    register_benchmarks_mult("DAY_2_01_small_array", random_small_array, mult_o1, benchmark_mult);

    register_benchmarks_mult("DAY_2_02_huge_array", random_huge_array, mult_o2, benchmark_mult_o2plus_variant);
    register_benchmarks_mult("DAY_2_02_big_array", random_big_array, mult_o2, benchmark_mult_o2plus_variant);
    register_benchmarks_mult("DAY_2_02_medium_array", random_medium_array, mult_o2, benchmark_mult_o2plus_variant);
    register_benchmarks_mult("DAY_2_02_small_array", random_small_array, mult_o2, benchmark_mult_o2plus_variant);

    // Register benchmarks for missing integer functions
    register_benchmarks_missing_int("DAY_4_00_huge_array", random_huge_array, find_missing_positive_integer);
    register_benchmarks_missing_int("DAY_4_00_big_array", random_big_array, find_missing_positive_integer);
    register_benchmarks_missing_int("DAY_4_00_medium_array", random_medium_array, find_missing_positive_integer);
    register_benchmarks_missing_int("DAY_4_00_small_array", random_small_array, find_missing_positive_integer);

    register_benchmarks_missing_int("DAY_4_01_huge_array", random_huge_array, find_missing_positive_integer_o1);
    register_benchmarks_missing_int("DAY_4_01_big_array", random_big_array, find_missing_positive_integer_o1);
    register_benchmarks_missing_int("DAY_4_01_medium_array", random_medium_array, find_missing_positive_integer_o1);
    register_benchmarks_missing_int("DAY_4_01_small_array", random_small_array, find_missing_positive_integer_o1);

    // Initialize and run benchmarks
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
}