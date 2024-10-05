/**
Good morning! Here's your coding interview problem for today.

This problem was recently asked by Google.

Given a list of numbers and a number k, return whether any two numbers from the list add up to k.

For example, given [10, 15, 3, 7] and k of 17, return true since 10 + 7 is 17.

Bonus: Can you do this in one pass?
 */

#include "day1.hpp"
#include <vector>
#include <algorithm>
#include <unordered_set>

bool sum_2(std::vector<int> &array, const int k)
{
    auto left = array.begin(), right = array.end() - 1;
    std::sort(left, right);

    long long sum;
    while (left < right)
    {
        long long left_val = static_cast<long>(*left);
        long long right_val = static_cast<long>(*right);
        sum = left_val + right_val;
        if (sum == k)
            return true;
        else if (sum > k)
            --right;
        else
            ++left;
    }

    return false;
}

/**
 * Optimisation attempts:
 * - Change the checks order to start with a more likely scenario
 * - Use cbegin and cend instead of begin and end
 *
 * Results:
 * - No significant improvement
 */
bool sum_2_o1(std::vector<int> &array, const int k)
{
    std::sort(array.begin(), array.end());
    auto left = array.cbegin(), right = array.cend() - 1;

    long long sum;
    while (left < right)
    {
        long long left_val = static_cast<long>(*left);
        long long right_val = static_cast<long>(*right);
        sum = left_val + right_val;
        if (sum > k)
            --right;
        else if (sum < k)
            ++left;
        else
            return true;
    }

    return false;
}

/**
 * Algo change:
 *  - Use a hash table to store the values instead of sorting nlog(n) complexity to n
 *
 * Results:
 *  - It is slower for most of the executions and equal for the biggest one.
 * My intuition is that the precedent version o1 is way more cache efficient, in addition with this, the constant time overhead of using a hashmap is significant. This leads to better performances for most of the inputs.
 */
bool sum_2_o2(std::vector<int> &array, const int k)
{
    std::unordered_set<int> set(array.begin(), array.end());

    int k_div_2{k / 2};
    bool k_even{k % 2 == 0};
    size_t k_div_2_count{0};

    for (auto &e : array)
    {
        if (k_even && k_div_2 == e)
            k_div_2_count++;
        else if (set.find(k - e) != set.end())
            return true;
    }

    return k_div_2_count > 1;
}

// Running ./benchmark
// Run on (16 X 4463 MHz CPU s)
// CPU Caches:
//   L1 Data 32 KiB (x8)
//   L1 Instruction 32 KiB (x8)
//   L2 Unified 512 KiB (x8)
//   L3 Unified 16384 KiB (x1)
// Load Average: 0.80, 0.94, 0.90
// --------------------------------------------------------------------
// Benchmark                          Time             CPU   Iterations
// --------------------------------------------------------------------
// DAY_1_00_huge_array_min    848951395 ns    848725606 ns            1
// DAY_1_00_huge_array_max    886842995 ns    886776150 ns            1
// DAY_1_00_huge_array_0      846436009 ns    846314565 ns            1
// DAY_1_00_big_array_min         91264 ns        91257 ns         7631
// DAY_1_00_big_array_max         91067 ns        91060 ns         7605
// DAY_1_00_big_array_0           91134 ns        91127 ns         7621
// DAY_1_00_medium_array_min       6343 ns         6343 ns       110456
// DAY_1_00_medium_array_max       6331 ns         6329 ns       110262
// DAY_1_00_medium_array_0         6338 ns         6336 ns       110205
// DAY_1_00_small_array_min        25.0 ns         25.0 ns     25572191
// DAY_1_00_small_array_max        18.0 ns         18.0 ns     34816713
// DAY_1_00_small_array_0          18.3 ns         18.3 ns     38146422
// DAY_1_01_huge_array_min    572768280 ns    572705425 ns            1
// DAY_1_01_huge_array_max    557467720 ns    557416847 ns            1
// DAY_1_01_huge_array_0      553930906 ns    553878325 ns            1
// DAY_1_01_big_array_min         60471 ns        60452 ns        11344
// DAY_1_01_big_array_max         60815 ns        60799 ns        11246
// DAY_1_01_big_array_0           62129 ns        62115 ns        10987
// DAY_1_01_medium_array_min       4079 ns         4078 ns       171533
// DAY_1_01_medium_array_max       4137 ns         4136 ns       169436
// DAY_1_01_medium_array_0         4288 ns         4287 ns       162704
// DAY_1_01_small_array_min        21.2 ns         21.2 ns     33404973
// DAY_1_01_small_array_max        20.7 ns         20.7 ns     33822484
// DAY_1_01_small_array_0          19.8 ns         19.8 ns     35234907
// DAY_1_02_huge_array_min    558166051 ns    558127185 ns            1
// DAY_1_02_huge_array_max    558921906 ns    558868463 ns            1
// DAY_1_02_huge_array_0      555498018 ns    555438334 ns            1
// DAY_1_02_big_array_min        576981 ns       576929 ns         1177
// DAY_1_02_big_array_max        599876 ns       599771 ns         1131
// DAY_1_02_big_array_0          572709 ns       572529 ns         1162
// DAY_1_02_medium_array_min      42377 ns        42361 ns        16608
// DAY_1_02_medium_array_max      42355 ns        42350 ns        16600
// DAY_1_02_medium_array_0        42632 ns        42626 ns        16549
// DAY_1_02_small_array_min         222 ns          222 ns      3041553
// DAY_1_02_small_array_max         223 ns          223 ns      3129448
// DAY_1_02_small_array_0           230 ns          230 ns      3039227