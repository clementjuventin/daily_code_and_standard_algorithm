using namespace std;

#include <vector>
#include <limits>

/**
 * This code build a vector one element at a time, and it keeps it sorted, each insertion costs O(log n) time and
 * you can access the element before or after to compare it with the current element.
 * 
 * lower_bound is a binary search algorithm that works on sorted containers
 */
int minimumLoss(vector<long> prices) {
    vector<long> sortedPrices;
    long mi = numeric_limits<long>::max();

    for (auto& p : prices) {
        // Find the position to insert the element using binary search
        auto pos = lower_bound(sortedPrices.begin(), sortedPrices.end(), p);

        if (pos != sortedPrices.end()) {
            long diff = *pos - p;
            mi = min(diff, mi);
        }
        sortedPrices.insert(pos, p);
    }

    return mi;
}
