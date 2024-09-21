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
 * Hierholzer is a kind of DFS giving a path that traverses every edge of a graph ending on a given vertice.
 * If there is no eulerian path, the path will be smaller than E count +1
 * TC: o(V+E)
 * SC: o(V+E)
 */
template <class T, class U>
vector<Node<T, U> *> hierholzer(Graph<T, U> graph, Node<T, U> *start)
{
    stack<Node<T, U> *> stack;
    vector<Node<T, U> *> path;

    stack.push(start);
    while (!stack.empty())
    {
        Node<T, U> *node = stack.top();
        if (!node->out.empty())
        {
            Node<T, U> *next = (node->out.begin())->first;
            node->out.erase(next);
            stack.push(next);
        }
        else
        {
            path.push_back(node);
            stack.pop();
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

TEST(HIERHOLZER, hierholzer)
{
    Node<char, uint> A('A');
    Node<char, uint> B('B');
    Node<char, uint> C('C');
    Node<char, uint> D('D');
    Node<char, uint> E('E');

    A.addEdge(&B, 1);
    C.addEdge(&A, 3);
    A.addEdge(&D, 2);
    B.addEdge(&C, 4);
    C.addEdge(&E, 2);
    D.addEdge(&C, 1);
    E.addEdge(&D, 1);

    Graph<char, uint> graph;
    graph.nodes.push_back(&A);
    graph.nodes.push_back(&B);
    graph.nodes.push_back(&C);
    graph.nodes.push_back(&D);
    graph.nodes.push_back(&E);

    vector<Node<char, uint> *> path = hierholzer<char, uint>(graph, &A);

    EXPECT_EQ(path.size(), 8);
    EXPECT_EQ(path.at(0), &A);
    EXPECT_EQ(path.at(1), &D);
    EXPECT_EQ(path.at(2), &C);
    EXPECT_EQ(path.at(3), &A);
    EXPECT_EQ(path.at(4), &B);
    EXPECT_EQ(path.at(5), &C);
    EXPECT_EQ(path.at(6), &E);
    EXPECT_EQ(path.at(7), &D);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
