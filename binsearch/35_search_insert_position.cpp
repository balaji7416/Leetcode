#include <bits/stdc++.h>
using namespace std;

/*
    Problem 35: Search Insert Position
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/

/*
    Lower bound = first element >= target
    Upper bound = first element > target
*/

class Solution
{
public:
    int searchInsert(vector<int> &nums, int target)
    {
        int n = nums.size();
        int low = 0, high = n - 1;
        int ans = n;

            while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (nums[mid] >= target)
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
        // return lower_bound(nums.begin(),nums.end(),target)-nums.begin();
    }
};
