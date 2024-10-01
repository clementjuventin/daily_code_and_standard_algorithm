/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

Given a dictionary of words and a string made up of those words (no spaces), return the original sentence in a list. If there is more than one possible reconstruction, return any of them. If there is no possible reconstruction, then return null.

For example, given the set of words "quick", "brown", "the", "fox", and the string "thequickbrownfox", you should return ["the", "quick", "brown", "fox"].

Given the set of words "bed", "bath", "bedbath", "and", "beyond", and the string "bedbathandbeyond", return either ["bed", "bath", "and", "beyond] or ["bedbath", "and", "beyond"].
*/

#include <gtest/gtest.h>
#include <string>

using namespace std;

/**
 * Idea: The "dictionnary" can be implemented as a set data structure and we just need to test every
 * strings. Here I made some backtracking which was not the best solution. Will implementing I realised we could
 * represent the problem as finding a group of letters inside a bigger group. Which makes the dp approach way easier to
 * think about
 * TC: O(2^n)
 * SP: O(n)
 * An improvment suggested by ChatGPT was to use a parameter as the return value to not have to call new and delete
 */

vector<string> *decompose_sentence(string *s, set<string> *dictionnary, std::string::iterator it)
{
    if (it == s->end())
        return new vector<string>{};
    auto start = it;
    while (it != s->end())
    {
        ++it;
        auto match = dictionnary->find(string{start, it});
        if (match != dictionnary->end())
        {
            auto result = decompose_sentence(s, dictionnary, it);
            if (result != nullptr)
            {
                result->push_back(string{start, it});
                return result;
            }
            else
            {
                delete result;
            }
        }
    }
    return nullptr;
}

TEST(DECOMPOSE, decompose_sentence)
{
    string sentence = "bedwadabathandbeyond";
    set<string> s{"bed", "bath", "bedbath", "and", "beyond"};

    vector<string>* res = decompose_sentence(&sentence, &s, sentence.begin());

    EXPECT_EQ(res->size(), 4);
    EXPECT_EQ(res->at(3), string{"bed"});
    EXPECT_EQ(res->at(2), string{"bath"});
    EXPECT_EQ(res->at(1), string{"and"});
    EXPECT_EQ(res->at(0), string{"beyond"});
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
