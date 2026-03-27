#include <bits/stdc++.h>
using namespace std;

/*
    Problem 81: Search in Rotated Sorted Array II
    Pattern: Binary Search
    Time: avgCase(O(logn)), worstCase(O(n))
    Space: O(1)
*/

class Solution
{
public:
    bool search(vector<int> &nums, int target)
    {
        int n = nums.size();
        int low = 0, high = n - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target)
                return true;
            else if (nums[mid] == nums[low] && nums[mid] == nums[high])
            {
                low++;
                high--;
            }
            else if (nums[low] <= nums[mid])
            {
                // left half is sorted
                if (nums[low] <= target && target < nums[mid])
                {
                    high = mid - 1;
                }
                else
                {
                    low = mid + 1;
                }
            }
            else
            {
                // right is sorted
                if (target <= nums[high] && target > nums[mid])
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
        }
        return false;
    }
};