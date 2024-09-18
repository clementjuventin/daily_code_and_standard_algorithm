/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Twitter.

Implement an autocomplete system. That is, given a query string s and a set of all possible query strings, return all strings in the set that have s as a prefix.

For example, given the query string de and the set of strings [dog, deer, deal], return [deer, deal].

Hint: Try preprocessing the dictionary into a more efficient data structure to speed up queries.
*/

#include <gtest/gtest.h>
#include <string>

using namespace std;

void find_word()
{
    /*
    Idea: I would use a tree data structure, a root is a letter and the branches are containing the
    next letters. I think we can represent this structure using a dictionnary of dictionnaries
    and preprocessing data. We can also have in each node an array of pointers to every word
    existing as a leaf of the current node to save time
    */
}

TEST(FIND_WORDS, find_word)
{
    const set<string> words = {"dog", "deer", "deal"};
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
