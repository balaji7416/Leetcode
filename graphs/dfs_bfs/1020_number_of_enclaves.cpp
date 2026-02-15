#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1020: Number of Enclaves
    Pattern: DFS
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea:
        run dfs/bfs from the bounday 1's
        and mark all 1's reachable from boundary 1's as not safe 0's
        count remaining 1's in the grid
        which are required enclaves

        i used iterative dfs here
        but you can also use recursive dfs
*/

class Solution
{
public:
    void dfs(int r, int c, vector<vector<int>> &grid)
    {
        if (grid[r][c] == 0)
            return;

        int n = grid.size();
        int m = grid[0].size();
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        stack<pair<int, int>> stk;
        stk.push({r, c});
        grid[r][c] = 0;
        while (!stk.empty())
        {
            auto [x, y] = stk.top();
            stk.pop();
            for (int i = 0; i < 4; i++)
            {
                int nr = x + dx[i];
                int nc = y + dy[i];
                if (nr >= 0 && nc >= 0 && nr < n && nc < m && grid[nr][nc] != 0)
                {
                    stk.push({nr, nc});
                    grid[nr][nc] = 0;
                }
            }
        }
    }
    int numEnclaves(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();

        for (int i = 0; i < n; i++)
        {
            dfs(i, 0, grid);
            dfs(i, m - 1, grid);
        }
        for (int j = 0; j < m; j++)
        {
            dfs(0, j, grid);
            dfs(n - 1, j, grid);
        }

        int ans = 0;

        /*remove & and you can see the performance drop. to your hearts content. period
          that's cause of vector copying overhead which can be avoid using & by directly
          referencing the original one */
        for (auto &vec : grid)
        {
            for (auto &el : vec)
            {
                if (el == 1)
                {
                    ans++;
                }
            }
        }
        return ans;
    }
};