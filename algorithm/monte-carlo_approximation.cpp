#include <gtest/gtest.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

double find_pi()
{
    /*
    The Monte Carlo method is a probabilistic approach to calculation.

    Ex: Find the value of π

    The area of a circle is defined as πr²
    The basic equation of a circle is x2 + y2 = r2

    We create a square and a circle inside. If we generate a random point inside the square, chances that it will also be inside
    the circle depends on a probabilistic formula. We can calculate this probability and solve pi with this method.
    An easy way is to pick a square with area = 1 and so r = 0.5

    area_circle / area_square = πr² / 1 and probability to end inside the circle (pc) is also area_circle / area_square
    π = pc / r² and we just need to find pc
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
