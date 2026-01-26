#include <bits/stdc++.h>
using namespace std;

/*
    Problem 62: Unique Paths
    Pattern: Recursion + dp(memoization)
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea: dp + recursion
*/

class Solution
{
public:
    int calculate(int i, int j, int m, int n, vector<vector<int>> &dp)
    {
        if (i == m - 1 && j == n - 1)
            return 1;
        if (i >= m || j >= n)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];
        return dp[i][j] = calculate(i + 1, j, m, n, dp) + calculate(i, j + 1, m, n, dp);
    }
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return calculate(0, 0, m, n, dp);
    }
};