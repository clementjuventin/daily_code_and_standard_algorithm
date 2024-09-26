/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Apple.

Implement a queue using two stacks. Recall that a queue is a FIFO (first-in, first-out) data structure with the following methods: enqueue, which inserts an element into the queue, and dequeue, which removes it.
*/

/**
 * Idea: The second stack is used to reverse the first one. Insertion in o(n)
 * The description does not specify what happens when the queue is empty and we try to dequeue. I suppose it's
 * no gonna happen
 * 
 * I found a better implementation asking to ChatGPT. You can just stack the elements in s1, when dequeuing,
 * if s2 is not empty, we pick the top element, if not, we perform the same action that we did in the current
 * algorithm reversing elements of s1 into s2. with this technique we decrease the amount of operations while
 * keeping the same complexity.
 */

#include <gtest/gtest.h>
#include <stack>

using namespace std;

class StackQueue
{
private:
    stack<int> s1;
    stack<int> s2;

public:
    void enqueue(int v)
    {
        for (size_t i = 0, l = s1.size(); i < l; ++i)
        {
            s2.push(s1.top());
            s1.pop();
        }
        s1.push(v);
        for (size_t i = 0, l = s2.size(); i < l; ++i)
        {
            s1.push(s2.top());
            s2.pop();
        }
    }
    int dequeue()
    {
        int e = s1.top();
        s1.pop();
        return e;
    }
};

TEST(STACK_QUEUE, StackQueue)
{
    StackQueue sq;
    sq.enqueue(1);
    sq.enqueue(2);
    sq.enqueue(3);
    EXPECT_EQ(sq.dequeue(), 1);
    sq.enqueue(4);
    EXPECT_EQ(sq.dequeue(), 2);
    EXPECT_EQ(sq.dequeue(), 3);
    EXPECT_EQ(sq.dequeue(), 4);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
