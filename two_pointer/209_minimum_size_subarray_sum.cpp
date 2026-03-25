#include <bits/stdc++.h>
using namespace std;

/*
    Problem 209: Minimum Size Subarray Sum
    Pattern: Two Pointer
    Time: O(n), Space: O(1)
*/

/*
Variable-size sliding window:
Expand right to increase sum, shrink left while sum >= target
Track minimum window length satisfying condition
→ two pointers + greedy shrink, O(n)
*/

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int n = nums.size();
        int sum = 0, l = 0;
        int ans = n + 1;
        for (int r = 0; r < n; r++)
        {
            sum += nums[r];
            while (sum >= target)
            {
                ans = min(ans, r - l + 1);
                sum -= nums[l];
                l++;
            }
        }
        return ans == n + 1 ? 0 : ans;
    }
};