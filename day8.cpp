/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

A unival tree (which stands for "universal value") is a tree where all nodes under it have the same value.

Given the root to a binary tree, count the number of unival subtrees.

For example, the following tree has 5 unival subtrees:

   0
  / \
 1   0
    / \
   1   0
  / \
 1   1
*/

#include <gtest/gtest.h>

using namespace std;

template <class T>
class Node
{
public:
    Node *left;
    Node *right;
    T val;

    Node(T v, Node *l = nullptr, Node *r = nullptr) : val{v}, left{l}, right{r} {}
};

bool count_unival_trees(Node<int> *node, int root_val, int *count)
{
    /*
    Idea: Recursive algo, we call each leaf passing a count reference and the root val
    If the recursive call returns true, it means that all leaf have the same value than the root
    */
    if (node == nullptr)
        return true;
    bool left_res = count_unival_trees(node->left, node->val, count);
    bool right_res = count_unival_trees(node->right, node->val, count);
    if (left_res && right_res)
    {
        *count += 1;
        return node->val == root_val;
    }
    return false;
}

TEST(COUNT_TREES, count_unival_trees)
{
    Node<int> one = Node<int>(0, nullptr, nullptr);
    Node<int> two = Node<int>(1, nullptr, nullptr);
    Node<int> tree = Node<int>(1, nullptr, nullptr);
    Node<int> four = Node<int>(1, &tree, &two);
    Node<int> five = Node<int>(0, &four, &one);
    Node<int> six = Node<int>(1, nullptr, nullptr);
    Node<int> seven = Node<int>(0, &six, &five);

    int res = 0;
    if (count_unival_trees(&seven, seven.val, &res))
    {
        res += 1;
    }

    EXPECT_EQ(res, 5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
