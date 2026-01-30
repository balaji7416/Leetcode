#include <bits/stdc++.h>
using namespace std;

/*
    Problem 416: Partition Equal Subset Sum
    Pattern: dp
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea: equal subset sum => check whether there exits a subset with sum equal to total_sum/2
        dp[idx][sum] = from my current idx and current sum, whether i can find a subset with sum equal to total_sum/2
*/
class Solution
{
public:
    bool solve(int i, int sum, int total_sum, vector<int> &nums, vector<vector<int>> &dp)
    {
        if (sum == total_sum / 2)
            return true;
        if (i == nums.size() || sum > total_sum / 2)
        {
            return false;
        }
        if (dp[i][sum] != -1)
            return dp[i][sum];
        bool take = solve(i + 1, sum + nums[i], total_sum, nums, dp);
        bool not_take = solve(i + 1, sum, total_sum, nums, dp);
        return dp[i][sum] = take || not_take;
    }
    bool canPartition(vector<int> &nums)
    {
        int n = nums.size();
        int total_sum = accumulate(nums.begin(), nums.end(), 0);
        if (total_sum % 2 != 0)
            return false;
        vector<vector<int>> dp(n, vector<int>(total_sum + 1, -1));
        return solve(0, 0, total_sum, nums, dp);
    }
};