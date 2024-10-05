/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

Implement integer exponentiation. That is, implement the pow(x, y) function, where x and y are integers and returns x^y.

Do this faster than the naive method of repeated multiplication.

For example, pow(2, 10) should return 1024.
*/

/**
 * Idea: It's hard to see when doing the problem for the first time but there is a mathematical tricks with exponents here
 * I just need to remember it..
 * For instance, instead of having 2¹⁰=2*2*2*2*2*2*2*2*2*2
 * we can write 2¹⁰=2⁵*2⁵ and only calculate 2⁵ which is 2*2²*2² and 2² is 2*2.
 * At the end we do 4 multiplications instead of 9.
 * We can always devide by two, for x^k it will either be equal to x^(k/2)*x^(k/2) or x^(k/2)*x^(k/2)*x
 * This is a logarithmique simplification passing from a time complexity of n to log2(n)
 * Regarding negative exponent, it works almost the same
 */

#include <gtest/gtest.h>

using namespace std;

double pow(int n, int e)
{
    if (e == 0)
        return 1;

    double half = pow(n, abs(e) / 2);
    double res = half * half;

    if (e % 2 != 0)
        res *= n;

    return e < 0 ? 1 / res : res;
}

// I asked chatgpt to give the iterative function, a bit less intuitive but probably more efficient
double pow_ite(int n, int e)
{
    double result = 1.0;
    int abs_e = abs(e);

    double base = n;

    while (abs_e > 0)
    {
        if (abs_e % 2 != 0)
            result *= base;

        base *= base;
        abs_e /= 2;
    }

    return e < 0 ? 1 / result : result;
}

TEST(POW, pow)
{
    EXPECT_EQ(pow(1, 0), 1);
    EXPECT_EQ(pow(10, 3), 1000);
    EXPECT_EQ(pow(10, 1), 10);
    EXPECT_EQ(pow(2, 10), 1024);
    EXPECT_EQ(pow(4, -1), 0.25);

    EXPECT_EQ(pow_ite(1, 0), 1);
    EXPECT_EQ(pow_ite(10, 3), 1000);
    EXPECT_EQ(pow_ite(10, 1), 10);
    EXPECT_EQ(pow_ite(2, 10), 1024);
    EXPECT_EQ(pow_ite(4, -1), 0.25);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}