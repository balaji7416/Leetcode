#include <bits/stdc++.h>
using namespace std;

/*
    Problem 70: Climbing Stairs
    Pattern: Recursion + dp
    Time: O(n), Space: O(n)
*/

/*
    idea: dp + recursion
*/

class Solution
{
public:
    int calculate(int n, unordered_map<int, int> &dp)
    {
        if (n <= 1)
            return 1;
        if (dp.count(n))
            return dp[n];
        return dp[n] = calculate(n - 1, dp) + calculate(n - 2, dp);
    }
    int climbStairs(int n)
    {
        unordered_map<int, int> dp;
        return calculate(n, dp);
    }
};