#include <bits/stdc++.h>
using namespace std;

/*
    Problemm 63: Unique Paths II
    Pattern: DP
    Time: O(m*n), Space: O(m*n)
*/

/*IDEA:

    TOP_DOWN:
        dp[i][j] = no.of ways to reach cell (m-1,n-1) from cell (i,j)
        dp[i][j] = dp[i][j+1] + dp[i+1][j]
        just handle the obstacles (return 0 if obstacle)
    BOTTOM_UP:
        dp[i][j] = no.of ways to reach cell (i,j) from cell (0,0)
        dp[i][j] = d[i][j-1] + dp[i-1][j]
        handle base cases and obstacles
        (if obstacle, dp[i][j] = 0)
*/

class Solution_top_down
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        auto dfs = [&](auto &&self, int i, int j) -> int
        {
            if (i < 0 || i >= n || j < 0 || j >= m)
                return 0;
            if (obstacleGrid[i][j] == 1)
                return 0;
            if (i == n - 1 && j == m - 1)
                return 1;
            if (dp[i][j] != -1)
                return dp[i][j];

            return dp[i][j] = self(self, i + 1, j) + self(self, i, j + 1);
        };
        return dfs(dfs, 0, 0);
    }
};

class Solution_bottom_up
{
public:
    int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
    {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();
        vector<vector<int>> dp(n, vector<int>(m, 0));
        for (int i = 0; i < m; i++)
        {
            if (obstacleGrid[0][i] == 1)
                break;
            dp[0][i] = 1;
        }
        for (int i = 0; i < n; i++)
        {
            if (obstacleGrid[i][0] == 1)
                break;
            dp[i][0] = 1;
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                dp[i][j] = (obstacleGrid[i][j] == 1 ? 0 : dp[i - 1][j] + dp[i][j - 1]);
            }
        }

        return dp[n - 1][m - 1];
    }
};