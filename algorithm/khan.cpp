#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include <queue>
#include <unordered_map>

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
 * Khan's algo. Return a possible topological order or throw an error if a cycle exists.
 * TC: o(V+E)
 * SC: o(V)
 */
template <class T, class U>
vector<Node<T, U> *> khan(Graph<T, U> *graph)
{
    unordered_map<Node<T, U> *, U> indegree;
    deque<Node<T, U> *> queue;
    vector<Node<T, U> *> topological_order;
    for (auto node : graph->nodes)
    {
        if (node->in.empty())
            queue.push_back(node);
        else
            indegree[node] = node->in.size();
    }

    while (!queue.empty())
    {
        Node<T, U> *node = queue.front();
        queue.pop_front();
        topological_order.push_back(node);
        for (auto &edge : node->out)
        {
            indegree[edge.second->dest] -= 1;
            if (indegree[edge.second->dest] == 0)
                queue.push_back(edge.second->dest);
        }
    }

    if (topological_order.size() != graph->nodes.size())
        throw invalid_argument("There is a cycle");

    return topological_order;
}

TEST(KHAN, khan)
{
    Node<char, uint> A('A');
    Node<char, uint> B('B');
    Node<char, uint> C('C');
    Node<char, uint> D('D');
    Node<char, uint> E('E');

    A.addEdge(&B, 1);
    B.addEdge(&E, 3);
    A.addEdge(&D, 2);
    B.addEdge(&C, 4);
    C.addEdge(&E, 2);
    D.addEdge(&C, 1);

    Graph<char, uint> graph;
    graph.nodes.push_back(&A);
    graph.nodes.push_back(&B);
    graph.nodes.push_back(&C);
    graph.nodes.push_back(&D);
    graph.nodes.push_back(&E);

    khan(&graph);
    E.addEdge(&D, 1);
    EXPECT_THROW(khan(&graph), invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
