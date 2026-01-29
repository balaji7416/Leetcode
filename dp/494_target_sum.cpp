#include <bits/stdc++.h>
using namespace std;

/*
    Problem 494: Target Sum
    Pattern: dp
    Time: O(m*n), Space: O(m*n)
*/

class Solution
{
public:
    int solve(int idx, int sum, int target, vector<int> &nums, vector<vector<int>> &dp)
    {
        if (sum > 1000 || sum < -1000)
            return 0;
        if (idx == nums.size())
        {
            if (sum == target)
            {
                return 1;
            }
            return 0;
        }
        if (dp[idx][sum + 1000] != -1)
            return dp[idx][sum + 1000];
        int add = solve(idx + 1, sum + nums[idx], target, nums, dp);
        int sub = solve(idx + 1, sum - nums[idx], target, nums, dp);
        return dp[idx][sum + 1000] = add + sub;
    }
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int ans = 0;
        int sum = 0;
        vector<vector<int>> dp(nums.size(), vector<int>(2001, -1));
        return solve(0, sum, target, nums, dp);
    }
};