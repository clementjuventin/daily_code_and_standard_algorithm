/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Microsoft.

Given an array of numbers, find the length of the longest increasing subsequence
in the array. The subsequence does not necessarily have to be contiguous.

For example, given the array [0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7,
15], the longest increasing subsequence has length 6: it is 0, 2, 6, 9, 11, 15.
*/

#include <gtest/gtest.h>

using namespace std;

int longest_i_subs(vector<int> &subsq) {
  vector<int> dp(subsq.size(), 1);

  for (size_t i = 0; i < subsq.size(); i++) {
    for (size_t j = 0; j < i; j++) {
      if (subsq[j] < subsq[i]) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
  }
  return *max_element(dp.begin(), dp.end());
}

TEST(LONGEST_INCREASING_SUSQ, longest_increasing_subsq) {
    // Test case 1: Given example in the prompt
    vector<int> arr1 = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    EXPECT_EQ(longest_i_subs(arr1), 6);

    // Test case 2: Single element
    vector<int> arr2 = {42};
    EXPECT_EQ(longest_i_subs(arr2), 1);

    // Test case 3: All elements increasing
    vector<int> arr3 = {1, 2, 3, 4, 5};
    EXPECT_EQ(longest_i_subs(arr3), 5);

    // Test case 4: All elements decreasing
    vector<int> arr4 = {5, 4, 3, 2, 1};
    EXPECT_EQ(longest_i_subs(arr4), 1);

    // Test case 5: Repeated elements
    vector<int> arr5 = {2, 2, 2, 2, 2};
    EXPECT_EQ(longest_i_subs(arr5), 1);

    // Test case 6: Mixed positive and negative elements
    vector<int> arr6 = {-1, 2, -3, 4, -5, 6, -7, 8};
    EXPECT_EQ(longest_i_subs(arr6), 5); // Example sequence: -1, 2, 4, 6, 8
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
