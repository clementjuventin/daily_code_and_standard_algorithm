/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Jane Street.

Suppose you are given a table of currency exchange rates, represented as a 2D array. Determine whether there is a possible arbitrage: that is, whether there is some sequence of trades you can make, starting with some amount A of any currency, so that you can end up with some amount greater than A of that currency.

There are no transaction costs and you can trade fractional quantities.
*/

#include <gtest/gtest.h>
#include <cmath>

using namespace std;

/**
 * Idea: Bellman Ford algo (ie: find a negative cycle in the graph) (works if the graph is fully connected)
 * I was struggling to find a way to represent weights and chatGPT hints me to use negative logs
 *
 * TC: o(n²)
 * SC: o(n²)
 */

bool arbitrage(vector<vector<double>> exchanges)
{
    const double EPSILON = 1e-9; // For floating point errors
    int vertices_len = exchanges.size();
    int edges_len = vertices_len * vertices_len; // We suppose the graph is complete
    vector<double> dist(vertices_len, INFINITY);

    for (int j = 0; j < vertices_len; j++)
    {
        for (int i = 0; i < vertices_len; i++)
        {
            exchanges.at(j).at(i) = -log(exchanges.at(j).at(i));
            // cout << exchanges.at(j).at(i) << " ";
        }
        // cout << endl;
    }

    dist.at(0) = 0;
    for (int src_index = 0; src_index < vertices_len; src_index++)
    {
        for (int dest_index = 0; dest_index < vertices_len; dest_index++)
        {
            double weight = exchanges.at(src_index).at(dest_index);
            if (dist.at(src_index) != INFINITY && dist.at(src_index) + weight < dist.at(dest_index))
                dist.at(dest_index) = dist.at(src_index) + weight;
        }
        // for (int i = 0; i < vertices_len; i++)
        // {
        //     cout << dist.at(i) << " ";
        // }
        // cout << endl;
    }

    for (int src_index = 0; src_index < vertices_len; src_index++)
    {
        for (int dest_index = 0; dest_index < vertices_len; dest_index++)
        {
            double weight = exchanges.at(src_index).at(dest_index);
            if (dist.at(src_index) != INFINITY && dist.at(src_index) + weight + EPSILON < dist.at(dest_index))
            {
                // cout << src_index << " " << dest_index << " " << dist.at(src_index) + weight << " " << dist.at(dest_index) << endl;
                return true;
            }
        }
    }

    return false;
}

TEST(ARBITRAGE, arbitrage)
{
    vector<double> A{1, 5, 2};
    vector<double> B{1 / 5.0, 1, 1 / 2.0};
    vector<double> C{1 / 2.0, 2, 1};

    vector<double> A2{1, 5, 2};
    vector<double> B2{1 / 5.0, 1, 2 / 5.0};
    vector<double> C2{1 / 2.0, 5 / 2.0, 1};

    vector<vector<double>> exchanges{A, B, C};
    vector<vector<double>> exchanges2{A2, B2, C2};

    bool res = arbitrage(exchanges);
    bool res2 = arbitrage(exchanges2);

    EXPECT_EQ(res, true);
    EXPECT_EQ(res2, false);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
