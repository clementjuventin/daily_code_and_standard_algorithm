/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Given the root to a binary tree, implement serialize(root), which serializes the tree into a string, and deserialize(s), which deserializes the string back into the tree.

For example, given the following Node class

class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

The following test should pass:

node = Node('root', Node('left', Node('left.left')), Node('right'))
assert deserialize(serialize(node)).left.left.val == 'left.left'
*/

#include <gtest/gtest.h>
#include <queue>

using namespace std;

const char NULL_CHAR = 'n';

template <class T>
class Node
{
public:
    Node *left;
    Node *right;
    T val;

    Node(T v, Node *l = nullptr, Node *r = nullptr) : val{v}, left{l}, right{r} {}
};

string serialize(Node<int> *root)
{
    /*
        Idea: We can represent a binary tree using an array (sequential representation), ex:
        [3, 2, 4, 1, null, null, null, null, null, null, null]
                        3
                       / \
                      2   4
                     /     \
                    1       5
        We could leverage polymorphism an create an interface giving the prototype of serialize and
        deserialize for the value of the node but as for the example I will suppose that we are
        working with integers.
    */

    queue<Node<int> *> q;
    q.push(root);
    string serializedTree{""};

    if (root == nullptr)
        return serializedTree;

    while (!q.empty())
    {
        Node<int> *n = q.front();
        q.pop();
        if (n != nullptr)
        {
            serializedTree.append(to_string(n->val));
        }
        else
        {
            serializedTree.append(string(1, NULL_CHAR));
            continue;
        }
        q.push(n->left);
        q.push(n->right);
    }

    return serializedTree;
}

Node<int> *deserialize(string str)
{
    if (str.size() == 0)
        return nullptr;

    Node<int> *root = new Node<int>(str.at(0) - '0', nullptr, nullptr);
    int treePointer = 1;
    queue<Node<int> *> q;

    q.push(root);
    while (!q.empty())
    {
        Node<int> *node = q.front();
        q.pop();
        char lc = str.at(treePointer);
        char rc = str.at(treePointer + 1);
        if (lc != NULL_CHAR)
        {
            node->left = new Node<int>(lc - '0', nullptr, nullptr);
            q.push(node->left);
        }
        if (rc != NULL_CHAR)
        {
            node->right = new Node<int>(rc - '0', nullptr, nullptr);
            q.push(node->right);
        }

        treePointer += 2;
    }
    return root;
}

TEST(SERIALIZEDESERIALIZE, Serialize)
{
    Node<int> one = Node<int>(1, nullptr, nullptr);
    Node<int> two = Node<int>(2, &one, nullptr);
    Node<int> five = Node<int>(5, nullptr, nullptr);
    Node<int> four = Node<int>(4, nullptr, &five);
    Node<int> tree = Node<int>(3, &two, &four);

    string serializedTree = serialize(&tree);
    string deseriaAndSeria = serialize(deserialize(serializedTree));

    EXPECT_STREQ(serializedTree.c_str(), "3241nn5nnnn");
    EXPECT_STREQ(deseriaAndSeria.c_str(), "3241nn5nnnn");

    EXPECT_STREQ(serialize(nullptr).c_str(), "");
    EXPECT_EQ(deserialize(string("")), nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
