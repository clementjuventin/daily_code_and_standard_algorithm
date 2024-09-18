/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Google.

The area of a circle is defined as πr^2. Estimate π to 3 decimal places using a Monte Carlo method.

Hint: The basic equation of a circle is x2 + y2 = r2.
*/

#include <gtest/gtest.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

double find_pi()
{
    /*
    Idea: I had no idea what the Monte Carlo method was until I checked. It's a probabilistic approach to calculation.
    Honestly I wouldn't have tackle this problem without seing the example I found on pi calculation.

    We create a square and a circle inside. We can express the area of the circle using pi (ap) and the area of the
    square (as). If we generate a random point inside the square, we have ap/as chance that it will also be inside
    the circle. We can calculate this probability and solve pi with this method.
    An easy way is to pick a square with area = 1 and so r = 0.5

    How do we estimate to 3 decimals?
    I'am not sure if the question asks to give a result with 3 decimals or if it asks to find for sure the 3 first
    decimals. In the second case I don't see how would it be possible to be sure at 100% that the 3 decimals are
    correct.
    */
    const double R = 0.5;
    int iterations = 10000000;
    double count = 0;
    double total_count = 0;

    for (int i = 0; i < iterations; ++i)
    {
        // We devide by two because considering the center of the circle to 0,0, x and y can be max 0.5
        double x = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) / 2;
        double y = static_cast<double>(rand()) / static_cast<double>(RAND_MAX) / 2;

        bool is_inside = sqrt(pow(x, 2) + pow(y, 2)) <= R;
        if (is_inside)
            count++;
        total_count++;
    }

    // as = 1, ap = pi * R² = pi * 0.25 ie ap / as = pi / 4 ~= count / total_count
    double pi = count / total_count * 4;
    return round(pi * 1000) / 1000;
}

TEST(PI, find_pi)
{
    srand(1);

    double pi = find_pi();
    EXPECT_EQ(pi, 3.141);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
