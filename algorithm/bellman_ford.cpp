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
 * Bellman Ford. Shortest path accepting negative costs between vertices.
 * TC: o(V*E)
 * SC: o(V)
 */
template <class T, class U>
U bellman_ford(Node<T, U> *src, Node<T, U> *dest, Graph<T, U> *graph)
{
    unordered_map<Node<T, U> *, U> distances;

    for (auto node : graph->nodes)
        distances[node] = numeric_limits<U>::max();
    distances[src] = 0;

    int V = graph->nodes.size();
    for (int i = 0; i < V - 1; i++)
    {
        for (auto node : graph->nodes)
        {
            if (distances[node] == numeric_limits<U>::max())
                continue;
            for (auto &edge : node->out)
            {
                Node<T, U> *neighbor = edge.second->dest;
                U weight = edge.second->weight;

                if (distances[node] + weight < distances[neighbor])
                    distances[neighbor] = distances[node] + weight;
            }
        }
    }

    for (auto node : graph->nodes)
    {
        if (distances[node] == numeric_limits<U>::max())
            continue;
        for (auto &edge : node->out)
        {
            Node<T, U> *neighbor = edge.second->dest;
            U weight = edge.second->weight;

            if (distances[node] + weight < distances[neighbor])
                throw invalid_argument("Graph contains a negative-weight cycle");
        }
    }

    if (distances[dest] == numeric_limits<U>::max())
        throw invalid_argument("Cannot connect src and dest");

    return distances[dest];
}

TEST(BELLMAN_FORD, bellman_ford)
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
    E.addEdge(&D, 1);

    Graph<char, uint> graph;
    graph.nodes.push_back(&A);
    graph.nodes.push_back(&B);
    graph.nodes.push_back(&C);
    graph.nodes.push_back(&D);
    graph.nodes.push_back(&E);

    EXPECT_EQ(bellman_ford(&A, &A, &graph), 0);
    EXPECT_EQ(bellman_ford(&A, &E, &graph), 4);
    EXPECT_EQ(bellman_ford(&A, &C, &graph), 3);
    EXPECT_EQ(bellman_ford(&E, &D, &graph), 1);
    EXPECT_EQ(bellman_ford(&B, &D, &graph), 4);
    EXPECT_THROW(bellman_ford(&D, &A, &graph), invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
