#include <bits/stdc++.h>
using namespace std;

/*
    Problem 162: Find Peak Element
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/

class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int n = nums.size();
        long long inf = LLONG_MAX;
        int low = 0, high = n - 1;
        auto is_valid = [&](int mid)
        {
            return nums[mid] > (mid > 0 ? nums[mid - 1] : -inf) &&
                   nums[mid] > (mid < n - 1 ? nums[mid + 1] : -inf);
        };
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (is_valid(mid))
            {
                return mid;
            }
            else if (mid > 0 && nums[mid - 1] > nums[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return -1;
    }
};

// another simplified approach
class Solution
{
public:
    int findPeakElement(vector<int> &nums)
    {
        int n = nums.size();
        int low = 0, high = n - 1;
        while (low < high)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] > nums[mid + 1])
            {
                // peak in left
                high = mid;
            }
            else
            {
                // peak in right
                low = mid + 1;
            }
        }
        return high;
    }
};