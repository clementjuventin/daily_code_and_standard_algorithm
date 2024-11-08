#include <gtest/gtest.h>
#include <cmath>

using namespace std;

// TC: o(sqrt(n)), might be more efficient with a lookup table
vector<int> prime_factors(int n)
{
    vector<int> factors;
    while (n % 2 == 0)
    {
        factors.push_back(2);
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        while (n % i == 0)
        {
            factors.push_back(i);
            n = n / i;
        }
    }

    // If n is a prime number
    if (n > 2)
        factors.push_back(n);
    return factors;
}

TEST(PRIME_FACTORS, prime_factors)
{
    vector<int> factors = prime_factors(12);
    vector<int> expected = {2, 2, 3};
    EXPECT_EQ(factors, expected);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}