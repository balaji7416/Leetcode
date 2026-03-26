#include <bits/stdc++.h>
using namespace std;

/*
    Problem 153: Find Minimum in Rotated Sorted Array
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/

/*IDEA:
Find pivot (smallest element) via binary search
reuturn the pivot
observe if arr[low] > arr[high] that means piv lies on the right side
else pivot lies on the left including the mid
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
            else
            {
                high = mid;
            }
        }
        int pos = low;
        return nums[pos];
    }
};