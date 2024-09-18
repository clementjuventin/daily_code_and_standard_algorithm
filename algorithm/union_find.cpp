#include <gtest/gtest.h>
#include <vector>
#include <stack>

using namespace std;

template <class T>
class UnionFind
{
private:
    unordered_map<T, T> parents;
    unordered_map<T, uint> ranks;

public:
    uint group_count;
    T find(T element)
    {
        if (parents.find(element) == parents.end())
        {
            parents[element] = element;
            ranks[element] = 0;
            group_count++;
        }
        if (parents[element] != element)
            parents[element] = find(parents[element]); // Path compression
        return parents[element];
    }

    void connect(T a, T b)
    {
        T rootA = find(a);
        T rootB = find(b);

        if (rootA == rootB)
            return;

        if (ranks[rootA] < ranks[rootB])
            parents[rootA] = rootB;
        else if (ranks[rootA] > ranks[rootB])
            parents[rootB] = rootA;
        else
        {
            parents[rootB] = rootA;
            ranks[rootA]++;
        }
        group_count--;
    }
};

TEST(UNION_FIND, union_find)
{
    UnionFind<int> uf;

    uf.find(1);
    uf.find(2);
    EXPECT_EQ(uf.group_count, 2);
    uf.find(3);
    EXPECT_EQ(uf.group_count, 3);
    EXPECT_EQ(uf.find(1), 1);
    EXPECT_EQ(uf.find(2), 2);
    uf.connect(1, 2);
    EXPECT_EQ(uf.group_count, 2);
    EXPECT_EQ(uf.find(1), 1);
    EXPECT_EQ(uf.find(2), 1);
    uf.connect(2, 3);
    EXPECT_EQ(uf.group_count, 1);
    EXPECT_EQ(uf.find(3), 1);
    uf.connect(3, 3);
    EXPECT_EQ(uf.group_count, 1);
    EXPECT_EQ(uf.find(3), 1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
