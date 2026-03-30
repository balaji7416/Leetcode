#include <bits/stdc++.h>
using namespace std;

/*
    Problem 154: Find Minimum in Rotated Sorted Array II
    Pattern: Binary Search
    Time: avgCase(O(logn)), worstCase(O(n), Space: O(1)
*/

/* IDEA:
 * Binary Search Logic for Rotated Sorted Array (with Duplicates):
 * * 1. Compare mid with high to determine which "half" contains the pivot/minimum.
 * 2. If nums[mid] > nums[high]:
 * The pivot must be to the right of mid (left side is sorted and larger).
 * 3. If nums[mid] < nums[high]:
 * The right side is sorted; mid could be the minimum or the pivot is to its left.
 * 4. If nums[mid] == nums[high]:
 * Indeterminate due to duplicates. Safely shrink search space by high--.
 * * Time: O(log N) average, O(N) worst case (e.g., [1, 1, 1, 0, 1]).
 * Space: O(1).
 */

class Solution
{
public:
    int findMin(vector<int> &nums)
    {
        int n = nums.size();
        int low = 0, high = n - 1;
        while (low < high)
        {
            int mid = low + (high - low) / 2;

            if (nums[mid] > nums[high])
            {
                low = mid + 1;
            }
            else if (nums[mid] < nums[high])
            {
                high = mid;
            }
            else
            {
                high--;
            }
        }
        return nums[low];
    }
};