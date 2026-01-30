#include <bits/stdc++.h>
using namespace std;

/*
    Problem 64: Minimum Path Sum
    Pattern: dp
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea:
        dp[i][j] = minimum sum i can get from i,j to n-1,m-1 with down and right moves
*/

class Solution
{
public:
    int solve(int i, int j, int n, int m, vector<vector<int>> &grid, vector<vector<int>> &dp)
    {
        if (i >= n || j >= m)
        {
            return INT_MAX;
        }
        if (i == n - 1 && j == m - 1)
        {
            return grid[i][j];
        }
        if (dp[i][j] != -1)
            return dp[i][j];
        int right = solve(i, j + 1, n, m, grid, dp);
        int down = solve(i + 1, j, n, m, grid, dp);
        return dp[i][j] = grid[i][j] + min(right, down);
    }
    int minPathSum(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, n, m, grid, dp);
    }
};