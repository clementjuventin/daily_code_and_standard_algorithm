#include <iostream>
#include <queue>
#include <vector>

// Comparator function to compare pairs based on the product of their elements
bool comparePairs(const std::pair<int, int>& a, const std::pair<int, int>& b) {
    return (a.first * a.second) < (b.first * b.second); // Max-heap based on product
}

int main() {
    // Define the priority_queue with a custom comparator function
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(&comparePairs)> pq(comparePairs);

    // Push some pairs into the priority_queue
    pq.emplace(2, 3); // Product is 6
    pq.emplace(1, 5); // Product is 5
    pq.emplace(4, 1); // Product is 4
    pq.emplace(2, 2); // Product is 4

    // Print the pairs based on their product in descending order
    while (!pq.empty()) {
        std::pair<int, int> top = pq.top();
        std::cout << "(" << top.first << ", " << top.second << ") - Product: " 
                  << top.first * top.second << "\n";
        pq.pop();
    }

    return 0;
}
