#include <gtest/gtest.h>
#include <vector>
#include <stack>

using namespace std;

template <class T, class U>
class Edge;

template <class T, class U>
class Node
{
public:
    Node(T value) : value(value) {}
    void addEdge(Node<T, U> *dest, U weight)
    {
        Edge<T, U> *edge = new Edge(this, dest, weight);
        this->out.insert({dest, edge});
        dest->in.insert({this, edge});
    }
    ~Node()
    {
        for (auto it = this->out.begin(); it != this->out.end(); ++it)
        {
            it->second->dest->in.erase(this);
            delete it->second;
        }

        for (auto it = this->in.begin(); it != this->in.end(); ++it)
        {
            it->second->src->out.erase(this);
            delete it->second;
        }
    }
    T value;
    unordered_map<Node<T, U> *, Edge<T, U> *> out;
    unordered_map<Node<T, U> *, Edge<T, U> *> in;
};

template <class T, class U>
class Edge
{
public:
    Edge(Node<T, U> *src, Node<T, U> *dest, U weight) : src(src), dest(dest), weight(weight) {}
    Node<T, U> *src;
    Node<T, U> *dest;
    U weight;
};

template <class T, class U>
class Graph
{
public:
    vector<Node<T, U> *> nodes;
};

/**
 * DFS.
 * TC: o(V+E)
 * SC: o(V)
 */
template <class T, class U>
bool dfs(Node<T, U> *src, Node<T, U> *dest)
{
    stack<Node<T, U> *> stack;
    set<Node<T, U> *> visited;
    stack.push(src);

    while (!stack.empty())
    {
        Node<T, U> *node = stack.top();
        stack.pop();

        if (node == dest)
            return true;

        if (visited.find(node) == visited.end())
        {
            visited.insert(node);
            for (auto &edge : node->out)
            {
                Node<T, U> *neighbor = edge.second->dest;
                if (visited.find(neighbor) == visited.end())
                    stack.push(neighbor);
            }
        }
    }

    return false;
}

TEST(DFS, dfs)
{
    Node<char, uint> A('A');
    Node<char, uint> B('B');
    Node<char, uint> C('C');
    Node<char, uint> D('D');
    Node<char, uint> E('E');
    Node<char, uint> O('O');

    A.addEdge(&B, 1);
    B.addEdge(&E, 3);
    A.addEdge(&D, 2);
    B.addEdge(&C, 4);
    C.addEdge(&E, 2);
    D.addEdge(&C, 1);
    E.addEdge(&D, 1);

    EXPECT_EQ(dfs(&A, &A), true);
    EXPECT_EQ(dfs(&A, &E), true);
    EXPECT_EQ(dfs(&E, &A), false);
    EXPECT_EQ(dfs(&O, &A), false);
    EXPECT_EQ(dfs(&A, &O), false);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
