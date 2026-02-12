#include <bits/stdc++.h>
using namespace std;

/*
    Problem 695: Max Area of Island
    Pattern: DFS
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea: dfs + 2d grid
        mark visited
        max of no.of nodes in connect components
*/

class Solution
{
public:
    int dfs(int i, int j, vector<vector<int>> &grid, vector<vector<bool>> &visited)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (i < 0 || j < 0 || i >= n || j >= m)
        {
            return 0;
        }
        if (visited[i][j] || grid[i][j] == 0)
            return 0;
        visited[i][j] = true;
        return 1 +
               dfs(i + 1, j, grid, visited) +
               dfs(i, j + 1, grid, visited) +
               dfs(i - 1, j, grid, visited) +
               dfs(i, j - 1, grid, visited);
    }
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        int n = grid.size();    // no.of rows
        int m = grid[0].size(); // no.of cols

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j] || grid[i][j] == 0)
                {
                    continue;
                }
                ans = max(ans, dfs(i, j, grid, visited));
            }
        }
        return ans;
    }
};