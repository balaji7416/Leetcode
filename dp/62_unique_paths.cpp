#include <bits/stdc++.h>
using namespace std;

/*
    Problem 62: Unique Paths
    Pattern: DP
    Time: O(m*n), Space: O(m*n)
*/

/*IDEA:

    TOP_DOWN:
        dp[i][j] = no.of ways to reach cell (m-1,n-1) from cell (i,j)
        dp[i][j] = dp[i][j+1] + dp[i+1][j]
    BOTTOM_UP:
        dp[i][j] = no.of ways to reach cell (i,j) from cell (0,0)
        dp[i][j] = d[i][j-1] + dp[i-1][j]
*/

class Solution_bottom_up
{
public:
    int uniquePaths(int m, int n)
    {
        /*
            dp[i][j] => no.of ways to reach cell (i,j)
        */
        vector<vector<int>> dp(m, vector<int>(n));
        for (int i = 0; i < n; i++)
            dp[0][i] = 1;
        for (int i = 0; i < m; i++)
            dp[i][0] = 1;
        for (int i = 1; i < m; i++)
        {
            for (int j = 1; j < n; j++)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};

class Solution_top_down
{
public:
    int uniquePaths(int m, int n)
    {
        vector<vector<int>> dp(m, vector<int>(n, -1));

        auto dfs = [&](auto &&self, int i, int j) -> int
        {
            if (i < 0 || i > m || i < 0 || j > n)
                return 0;
            if (i == m - 1 || j == n - 1)
                return 1;
            if (dp[i][j] != -1)
                return dp[i][j];
            return dp[i][j] = self(self, i, j + 1) + // right
                              self(self, i + 1, j);  // down
        };
        return dfs(dfs, 0, 0);
    }
};