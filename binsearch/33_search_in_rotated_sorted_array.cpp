#include <bits/stdc++.h>
using namespace std;

/*
    Problem 33: Search in Rotated Sorted Array
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/

/*IDEA:
Find pivot (smallest element) via binary search
Array splits into two sorted halves
Run binary search on both halves to find target
→ overall O(log n)
*/

class Solution
{
public:
    int search(vector<int> &nums, int target)
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
        auto bin_s = [&](int l, int h, int k)
        {
            while (l <= h)
            {
                int m = l + (h - l) / 2;
                if (nums[m] == k)
                    return m;
                if (nums[m] < k)
                    l = m + 1;
                else
                    h = m - 1;
            }
            return -1;
        };
        int l_ = bin_s(0, pos - 1, target);
        int r_ = bin_s(pos, n - 1, target);
        int ans_ = l_ != -1 ? l_ : r_;
        return ans_;
    }
};

// approach 2
class Solution
{
public:
    int search(vector<int> &nums, int target)
    {
        int n = nums.size();
        int low = 0, high = n - 1;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[low] <= nums[mid])
            {
                // left sorted
                if (target >= nums[low] && target < nums[mid])
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
                // right sorted
                if (target > nums[mid] && target <= nums[high])
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};