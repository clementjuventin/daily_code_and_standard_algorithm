/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Amazon.

Implement a stack that has the following methods:

    push(val), which pushes an element onto the stack
    pop(), which pops off and returns the topmost element of the stack. If there are no elements in the stack, then it should throw an error or return null.
    max(), which returns the maximum value in the stack currently. If there are no elements in the stack, then it should throw an error or return null.

Each method should run in constant time.
*/

#include <gtest/gtest.h>
#include <stack>
#include <stdexcept>

using namespace std;

/**
 * Idea: We can use a second stack to track the max element at index i
 */
class MyStack
{
private:
    stack<int> stck{};
    stack<int> max_stck{};

public:
    void push(int val)
    {
        stck.push(val);
        if (max_stck.empty())
            max_stck.push(val);
        else
            max_stck.push(std::max(max_stck.top(), val));
    }
    int pop()
    {
        if (stck.empty())
            throw std::invalid_argument("Empty stack");
        int val = stck.top();
        stck.pop();
        max_stck.pop();
        return val;
    }
    int max()
    {
        if (max_stck.empty())
            throw std::invalid_argument("Empty stack");
        return max_stck.top();
    }
};

TEST(STACK, stack)
{
    MyStack stack;

    stack.push(1);
    EXPECT_EQ(stack.max(), 1);
    stack.push(3);
    EXPECT_EQ(stack.max(), 3);
    stack.push(2);
    EXPECT_EQ(stack.max(), 3);
    EXPECT_EQ(stack.pop(), 2);
    EXPECT_EQ(stack.max(), 3);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.max(), 1);
    stack.pop();
    EXPECT_THROW(stack.max(), std::invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
