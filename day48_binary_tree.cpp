/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given pre-order and in-order traversals of a binary tree, write a function to reconstruct the tree.

For example, given the following preorder traversal:

[a, b, d, e, c, f, g]

And the following inorder traversal:

[d, b, e, a, f, c, g]

You should return the following tree:

    a
   / \
  b   c
 / \ / \
d  e f  g
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

/**
 * Idea: We know that preo[0] is the root. Having the root, we can split preo by preo[1:len/2+1] and preo[len/2+1:len]
 * and ino[0:len/2], ino[len/2+1:len]
 * This gives us a recursive approach by solving the sub problems
 */
Node<char> *build_tree(vector<char> &inorder, vector<char> &preorder, size_t left_ino, size_t right_ino, size_t left_prio, size_t right_prio)
{
    // cout << "li " << left_ino << " ri " << right_ino << " lp " << left_prio << " rp " << right_prio << endl;
    size_t len = right_ino - left_ino;
    if (len <= 1)
        return new Node(preorder.at(left_prio));

    size_t len_shift = len >> 1;
    auto left = build_tree(inorder, preorder, left_ino, left_ino + len_shift, left_prio + 1, left_prio + len_shift + 1);
    auto right = build_tree(inorder, preorder, left_ino + len_shift + 1, right_ino, left_prio + len_shift + 1, right_prio);
    Node<char> *n = new Node(preorder.at(left_prio), left, right);
    return n;
}

TEST(BUILD_TREE, build_tree)
{
    vector<char> preo{'a', 'b', 'd', 'e', 'c', 'f', 'g'};
    vector<char> ino{'d', 'b', 'e', 'a', 'f', 'c', 'g'};

    Node<char> *node = build_tree(ino, preo, 0, ino.size(), 0, preo.size());

    EXPECT_EQ(node->val, 'a');
    EXPECT_EQ(node->left->val, 'b');
    EXPECT_EQ(node->left->left->val, 'd');
    EXPECT_EQ(node->left->right->val, 'e');
    EXPECT_EQ(node->left->left->left, nullptr);
    EXPECT_EQ(node->left->left->right, nullptr);
    EXPECT_EQ(node->left->right->right, nullptr);
    EXPECT_EQ(node->left->right->right, nullptr);
    EXPECT_EQ(node->right->val, 'c');
    EXPECT_EQ(node->right->left->val, 'f');
    EXPECT_EQ(node->right->right->val, 'g');
    EXPECT_EQ(node->right->left->left, nullptr);
    EXPECT_EQ(node->right->left->right, nullptr);
    EXPECT_EQ(node->right->right->right, nullptr);
    EXPECT_EQ(node->right->right->right, nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
