#include <stdlib.h>

/**
 * The first k items are initially copied to reservoir[] and may be removed later in iterations for stream[k] to stream[n].
The probability that an item from stream[0..k-1] is in final array = Probability that the item is not picked when items stream[k], stream[k+1], …. stream[n-1] are considered = [k/(k+1)] x [(k+1)/(k+2)] x [(k+2)/(k+3)] x … x [(n-1)/n] = k/n
 */

void reservoir_sampling(int stream[], int n, int k)
{
    int i; // index for elements in stream[]

    // Initialize reservoir with first k elements from stream[]
    int reservoir[k];
    for (i = 0; i < k; i++)
        reservoir[i] = stream[i];

    srand(1);

    for (; i < n; i++)
    {
        // Pick a random index from 0 to i.
        int j = rand() % (i + 1);

        // If the randomly picked index is smaller than k,
        // then replace the element present at the index
        // with new element from stream
        if (j < k)
            reservoir[j] = stream[i];
    }
}