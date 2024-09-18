/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Implement locking in a binary tree. A binary tree node can be locked or unlocked only if all of its descendants or ancestors are not locked.

Design a binary tree node class with the following methods:

    is_locked, which returns whether the node is locked
    lock, which attempts to lock the node. If it cannot be locked, then it should return false. Otherwise, it should lock it and return true.
    unlock, which unlocks the node. If it cannot be unlocked, then it should return false. Otherwise, it should unlock it and return true.

You may augment the node to add parent pointers or any other property you would like. You may assume the class is used in a single-threaded program, so there is no need for actual locks or mutexes. Each method should run in O(h), where h is the height of the tree.
*/

#include <gtest/gtest.h>

using namespace std;

/**
 * Idea: The complexity here gives us a great hint.
 * From the current node we are not allowed to iterate over descendant or it will not be o(h). We can only iterate over
 * ancestors.
 * The node contains a data member called descendant_locked wich represent a counter of locked descendant
 * is_locked member function returns true if descendant_locked is >=1 or if an ancestor is locked
 * lock member function returns calls is_locked to see if the node is already locked, if not, it locks it and
 * iterate over ancestors to update descendant_locked
 * unlock member function do the same with is_locked
 * 
 * I realized after with chatGPT that I might have misunderstood the problem and considered a node would be locked
 * if it's ancestors or descendant was locked. Which is not the case and makes more sense. By the way I let the original code
 */

template <class T>
class Node
{
private:
    T value;
    uint descendant_locked;
    Node<T> *ancestor;
    bool locked;

public:
    bool is_locked()
    {
        if (this.descendant_locked > 0 || this.locked)
            return true;
        if (this->ancestor != nullptr)
            return this->ancestor->is_locked();
        return false;
    }
    bool lock()
    {
        if (this->is_locked())
            return false;
        this.locked = true;
        Node<T> *root = this->ancestor;
        while (root != nullptr)
        {
            root->descendant_locked += 1;
            root = root->ancestor;
        }
        return true;
    }
    bool unlock()
    {
        if (!is_locked() || !this.locked)
            return false;
        this.locked = false;
        Node<T> *root = this->ancestor;
        while (root != nullptr)
        {
            root->descendant_locked -= 1;
            root = root->ancestor;
        }
        return true;
    }
};

TEST(LOCKED_NODE, node)
{
    // Test cases (tested in my head)
    // 1 - Lock a leaf, the whole tree is locked, try to unlock another leaf (false), try to unlock the leaf (true)
    // 2 - Lock the root, once again the whole tree is locked (like everytime) we cannot unlock the tree from another node
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
