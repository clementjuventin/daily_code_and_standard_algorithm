/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Uber.

Given an array of integers, return a new array such that each element at index i of the new array is the product of all the numbers in the original array except the one at i.

For example, if our input was [1, 2, 3, 4, 5], the expected output would be [120, 60, 40, 30, 24]. If our input was [3, 2, 1], the expected output would be [2, 3, 6].

Follow-up: what if you can't use division?
*/

#include <vector>
#include <iostream>

/*
    Idea: With division
    Get the total product and then iterate over each elements of the array and devide the total product by the element

    Idea: Without division
    I couldn't find a solution with a constant space complexity, since there is no indication I don't know
    if it's the expected solution but assuming we want to optimise the execution using multiplications
    instead of division, I guess that allocating an array of size N looses all the benefits of the approach.
    No implementation but the idea is that the element i of the solution is equal to
    proudct(array[:i]) * product(array[i+1:])

    We do not considere overflows
*/
void mult(std::vector<int> &array)
{
    int product{1};
    size_t zero_count = 0;
    for (auto it = array.begin(); it < array.end(); it++)
    {
        if (*it == 0)
            zero_count++;
        else
            product *= *it;
    }
    if (zero_count > 0)
    {
        product = (zero_count == 1) * product; // 0 if more than 1 zero
        for (auto it = array.begin(); it < array.end(); it++)
            *it = *it == 0 ? product : 0;
    }
    else
    {
        for (auto it = array.begin(); it < array.end(); it++)
            *it = product / *it;
    }
}

/**
 * Algo change, we do not use a division
 *
 * Result:
 *  - We got an improvment, but I think a huge overhead is introduced by the array copying step.
 * If we changed the prototype by accepting a const array and a reference to another array for the result,
 * we could let the responssability of the memory management to higher level functions and hope for
 * potential optimizations.
 */
void mult_o1(std::vector<int> &array)
{
    int n = array.size();
    std::vector<int> tmp(array);

    // Step 1: Calculate the prefix products (product of all elements to the left)
    int prefix{1};
    for (int i = 0; i < n; i++)
    {
        array[i] = prefix;
        prefix *= tmp[i];
    }

    // Step 2: Calculate the suffix products (product of all elements to the right)
    int suffix{1};
    for (int i = n - 1; i >= 0; i--)
    {
        array[i] *= suffix;
        suffix *= tmp[i];
    }
}

/**
 * We changed the prototype and removed the array copy here
 *
 * Result:
 *  - We got a huge speed up, particularly on small arrays
 */
void mult_o2(const std::vector<int> &array, std::vector<int> &result)
{
    const size_t n = array.size();
    // Step 1: Calculate the prefix products (product of all elements to the left)
    int prefix{1};
    for (size_t i{0}; i < n; ++i)
    {
        result[i] = prefix;
        prefix *= array[i];
    }

    // Step 2: Calculate the suffix products (product of all elements to the right)
    int suffix{1};
    for (size_t i{n - 1}; i >= 0 && i < n; --i)
    {
        result[i] *= suffix;
        suffix *= array[i];
    }
}

// Running ./benchmark
// Run on (16 X 4463 MHz CPU s)
// CPU Caches:
//   L1 Data 32 KiB (x8)
//   L1 Instruction 32 KiB (x8)
//   L2 Unified 512 KiB (x8)
//   L3 Unified 16384 KiB (x1)
// Load Average: 1.87, 1.03, 0.91
// ----------------------------------------------------------------
// Benchmark                      Time             CPU   Iterations
// ----------------------------------------------------------------
// DAY_2_00_huge_array     65360464 ns     65347438 ns           10
// DAY_2_00_big_array         32334 ns        32326 ns        21658
// DAY_2_00_medium_array       3199 ns         3198 ns       218939
// DAY_2_00_small_array        39.8 ns         39.8 ns     17489659
// DAY_2_01_huge_array    110106322 ns    110091248 ns            6
// DAY_2_01_big_array         26332 ns        26325 ns        26596
// DAY_2_01_medium_array       2641 ns         2640 ns       265157
// DAY_2_01_small_array        53.2 ns         53.2 ns     13151581
// DAY_2_02_huge_array     60673337 ns     60663623 ns           10
// DAY_2_02_big_array         16471 ns        16468 ns        38565
// DAY_2_02_medium_array       1653 ns         1652 ns       423576
// DAY_2_02_small_array        23.1 ns         23.1 ns     31313661