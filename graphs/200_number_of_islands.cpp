#include <bits/stdc++.h>
using namespace std;

/*
    Problem 200: Number of Islands
    Pattern: DFS
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea: dfs + 2d grid
        mark visited
        count number of connect components
*/

class Solution
{
public:
    void dfs(int i, int j, vector<vector<char>> &grid, vector<vector<bool>> &visited)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (i >= n || j >= m || i < 0 || j < 0)
        {
            return;
        }
        if (visited[i][j])
        {
            return;
        }
        if (grid[i][j] == '0')
            return;
        visited[i][j] = true;
        dfs(i + 1, j, grid, visited);
        dfs(i, j + 1, grid, visited);
        dfs(i - 1, j, grid, visited);
        dfs(i, j - 1, grid, visited);
    }
    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (visited[i][j])
                    continue;
                if (grid[i][j] == '0')
                    continue;
                dfs(i, j, grid, visited);
                ans++;
            }
        }
        return ans;
    }
};