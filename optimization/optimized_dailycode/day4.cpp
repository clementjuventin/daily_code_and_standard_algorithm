/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Stripe.

Given an array of integers, find the first missing positive integer in linear time and constant space. In other words, find the lowest positive integer that does not exist in the array. The array can contain duplicates and negative numbers as well.

For example, the input [3, 4, -1, 1] should give 2. The input [1, 2, 0] should give 3.

You can modify the input array in-place.
*/

#include <vector>
#include "day4.hpp"

void place_element(std::vector<int> &array, int element)
{
    if (element < 1)
        return;
    int index = element - 1;
    if (index >= array.size())
        return;

    int replaced_element = array.at(index);
    array.at(index) = element;

    if (replaced_element != element)
        place_element(array, replaced_element);
}

int find_missing_positive_integer(std::vector<int> &array)
{
    for (int i = 0; i < array.size(); i++)
        place_element(array, array.at(i));
    for (int i = 0; i < array.size(); i++)
    {
        if (array.at(i) != i + 1)
            return i + 1;
    }
    return array.size();
}

/**
 * Idea: Turn the recursive call to an iterative call and replace by range for when possible
 *
 * Result:
 *  - A few improvments
 */
int find_missing_positive_integer_o1(std::vector<int> &array)
{
    const std::size_t len{array.size()};
    for (auto &e : array)
    {
        while (1 <= e && e <= len)
        {
            const std::size_t index{static_cast<std::size_t>(e) - 1};
            if (array[index] == e)
                break;
            std::swap(array[index], e);
        }
    }

    for (std::size_t i = 1; i < len; ++i)
    {
        if (array[i - 1] != i)
            return i;
    }

    return len;
}