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
 * Dijktra. Shortest path.
 * TC: o(V+E)
 * SC: o(V)
 */
template <class T, class U>
U dijkstra(Node<T, U> *src, Node<T, U> *dest)
{
    using Pair = pair<U, Node<T, U> *>;
    priority_queue<Pair, vector<Pair>, greater<Pair>> pq;

    unordered_map<Node<T, U> *, U> distances;
    distances[src] = 0;

    pq.push({0, src});

    while (!pq.empty())
    {
        auto [current_distance, current_node] = pq.top();
        pq.pop();

        if (current_node == dest)
            return current_distance;

        for (auto &edge : current_node->out)
        {
            Node<T, U> *neighbor = edge.second->dest;
            U weight = edge.second->weight;
            U new_distance = current_distance + weight;

            if (distances.find(neighbor) == distances.end() || new_distance < distances[neighbor])
            {
                distances[neighbor] = new_distance;
                pq.push({new_distance, neighbor});
            }
        }
    }

    throw invalid_argument("Cannot connect src and dest");
}

TEST(DIJKSTRA, dijkstra)
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

    EXPECT_EQ(dijkstra(&A, &A), 0);
    EXPECT_EQ(dijkstra(&A, &E), 4);
    EXPECT_EQ(dijkstra(&A, &C), 3);
    EXPECT_EQ(dijkstra(&E, &D), 1);
    EXPECT_EQ(dijkstra(&B, &D), 4);
    EXPECT_THROW(dijkstra(&D, &A), invalid_argument);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
