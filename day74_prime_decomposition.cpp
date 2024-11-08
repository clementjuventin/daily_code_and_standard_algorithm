/*
 * Good morning! Here's your coding interview problem for today.

This problem was asked by Apple.

Suppose you have a multiplication table that is N by N. That is, a 2D array
where the value at the i-th row and j-th column is (i + 1) * (j + 1) (if
0-indexed) or i * j (if 1-indexed).

Given integers N and X, write a function that returns the number of times X
appears as a value in an N by N multiplication table.

For example, given N = 6 and X = 12, you should return 4, since the
multiplication table looks like this:

| 1 | 2 | 3 | 4 | 5 | 6 |

| 2 | 4 | 6 | 8 | 10 | 12 |

| 3 | 6 | 9 | 12 | 15 | 18 |

| 4 | 8 | 12 | 16 | 20 | 24 |

| 5 | 10 | 15 | 20 | 25 | 30 |

| 6 | 12 | 18 | 24 | 30 | 36 |

And there are 4 12's in the table.
*/

#include <cmath>
#include <gtest/gtest.h>

using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

/**
 * Idea: At the begining, I was planing to get the prime decomposition of the number and then count the number of pairs than would give X.
 * The issue is that these pairs should not contain a number bigger than N. This makes the complexity increase.
 * Instead of getting the prime factors, I can just find every divisor and test if they match with the N constraint.
 */
int count(int N, int X)
{
    int count = 0;
    const int sup = min(N, static_cast<int>(sqrt(X)));
    for (int i = 1; i <= sup; ++i)
    {
        if (X % i == 0)
        { // i is a divisor of X
            int j = X / i;
            // Check if both divisors are within range [1, N]
            if (j <= N)
                // Count as two occurrences if i != j, else count as one
                count += (i == j) ? 1 : 2;
        }
    }
    return count;
}

TEST(COUNT, count)
{
    EXPECT_EQ(count(6, 12), 4);
    EXPECT_EQ(count(1, 1), 1);
    EXPECT_EQ(count(6, 1), 1);
    EXPECT_EQ(count(10, 100), 1);
    EXPECT_EQ(count(10, 7), 2);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
