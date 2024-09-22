/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Facebook.

Given a function that generates perfectly random numbers between 1 and k (inclusive), where k is an input, write a function that shuffles a deck of cards represented as an array using only swaps.

It should run in O(N) time.

Hint: Make sure each one of the 52! permutations of the deck is equally likely.
*/

/**
 * Idea: I can start by picking one card among the 52 availables, then among the 51.. until only one
 * last card stand.
 *
 * See Fisher-Yates (Knuth) shuffle, we don't need to add index each time we can just perform n rand swap
 * But this seems to work too
 */

#include <gtest/gtest.h>
#include <stdlib.h>

using namespace std;

void shuffle(vector<int> &cards)
{
    size_t len = cards.size();
    int index = 0;
    for (int i = len; i > 0; --i)
    {
        int card_index = (rand() % i) + index;
        swap(cards.at(index), cards.at(card_index));
        index++;
    }
}

TEST(SUFFLE, shuffle)
{
    vector<int> cards{0, 1, 2, 3};
    vector<uint64_t> occurences(cards.size(), 0);

    srand(1);
    const size_t ite = 100000;
    for (int i = 0; i < ite; i++)
    {
        shuffle(cards);
        occurences.at(cards.at(0))++;
    }
    for (int i = 0; i < 4; i++)
        cout << i << " " << 1.0 * occurences[i] / ite << endl;
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
