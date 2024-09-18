/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Suppose we represent our file system by a string in the following manner:

The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

dir
    subdir1
    subdir2
        file.ext

The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

dir
    subdir1
        file1.ext
        subsubdir1
    subdir2
        subsubdir2
            file2.ext

The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

Given a string representing the file system in the above format, return the length of the longest absolute path to a file in the abstracted file system. If there is no file in the system, return 0.

Note:

The name of a file contains at least a period and an extension.

The name of a directory or sub-directory will not contain a period.
*/

#include <gtest/gtest.h>
#include <string>

using namespace std;

vector<tuple<size_t, size_t>> current_solution;
size_t max_solution = 0;

/**
 * Idea: This is like going through a tree to find the longest branch (+ leaf has to be a file)
 * I want to avoid converting the string into a concrete tree because we don't necessary have to
 */
size_t find_deepest_file(string *s, size_t index = 0, uint depth = 0)
{
    const string NAME_DELIMITER{"\\n"};
    const string DEEP_DELIMITER{"\\t"};
    const string FILE_DELIMITER{"."};

    size_t node_end = s->find(NAME_DELIMITER, index);
    if (node_end == s->npos)
        node_end = s->size();
    else
        node_end += NAME_DELIMITER.size();

    current_solution.push_back({index, node_end});

    const string word = s->substr(index, node_end - index);
    // Is File
    if (word.find(FILE_DELIMITER) != s->npos)
    {
        if (max_solution < current_solution.size())
            max_solution = current_solution.size();
        current_solution.pop_back();
        return node_end;
    }

    int deep = 0;
    index = node_end;
    while (true)
    {
        size_t deep_delimiter_index = s->find(DEEP_DELIMITER, index);
        if (deep_delimiter_index == index)
        {
            index += DEEP_DELIMITER.size();
            deep += 1;
        }
        else
        {
            if (deep > depth)
            {
                index = find_deepest_file(s, index, deep);
                deep = 0;
            }
            else
            {
                auto back = current_solution.back();
                current_solution.pop_back();
                index = get<1>(back);
                return index;
            }
            if (deep_delimiter_index == s->npos)
                break;
        }
    }
    return index;
}

TEST(Log, log)
{
    string s = "dir\\n\\tsubdir1\\n\\t\\tfile1.ext\\n\\t\\tsubsubdir1\\n\\t\\t\\tsubsubsubdir1\\n\\t\\t\\t\\tfile0exe\\n\\tsubdir2\\n\\t\\tsubsubdir2\\n\\t\\t\\tfile2.ext";

    find_deepest_file(&s);

    EXPECT_EQ(max_solution, 4);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
