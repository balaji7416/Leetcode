#include <bits/stdc++.h>
using namespace std;

/*
    Problem 746: Min Cost Climbing Stairs
    Pattern: dp
    Time: O(n), Space: O(n)
*/

/*
    idea:
        dp[i] = min cost to reach i
        dp[i] = min(dp[i-1] + cost[i-1], dp[i-2] + cost[i-2])
*/

class Solution
{
public:
    int solve(int i, vector<int> &cost, vector<int> &dp)
    {
        if (i == cost.size())
            return 0;
        if (i > cost.size())
            return 999;
        if (dp[i] != -1)
            return dp[i];
        return dp[i] = cost[i] + min(
                                     solve(i + 1, cost, dp),
                                     solve(i + 2, cost, dp));
    }
    int minCostClimbingStairs(vector<int> &cost)
    {
        int n = cost.size();
        vector<int> dp(n + 1, -1);
        return min(solve(0, cost, dp), solve(1, cost, dp));
    }
};