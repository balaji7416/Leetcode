#include <bits/stdc++.h>
using namespace std;

/*
    Problem 934: Shortest Bridge
    Pattern: dfs marking + multi-source bfs
    Time: O(n^2), Space: O(n^2)
*/
/* idea:
Shortest Bridge (DFS + Multi-Source BFS)

1. Use DFS to mark the two islands
   with distinct values (2 and 3).

2. Push all cells of first island (2)
   into the queue (distance = 0).

3. Run multi-source BFS:
   - Expand level by level
   - Compute shortest distance
     to every cell.

4. The minimum distance to any
   cell of second island (3)
   gives the shortest bridge.
   Return ans - 1 (exclude last land step).
*/

class Solution
{
public:
    void dfs(int r, int c, int mark, vector<vector<int>> &grid)
    {
        int n = grid.size();
        stack<pair<int, int>> stk;
        grid[r][c] = mark;
        stk.push({r, c});

        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        while (!stk.empty())
        {
            auto [x, y] = stk.top();
            stk.pop();
            for (int i = 0; i < 4; i++)
            {
                int nr = x + dx[i];
                int nc = y + dy[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] == 1)
                {
                    grid[nr][nc] = mark;
                    stk.push({nr, nc});
                }
            }
        }
    }

    void bfs(vector<vector<int>> &dist, vector<vector<int>> &grid)
    {
        int n = grid.size();
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 2)
                {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                int nr = x + dx[i];
                int nc = y + dy[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && dist[nr][nc] == -1)
                {
                    dist[nr][nc] = dist[x][y] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }

    int shortestBridge(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        int mark = 2;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    dfs(i, j, mark++, grid);
                }
            }
        }

        bfs(dist, grid);
        int ans = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 3 && dist[i][j] < ans)
                {
                    ans = dist[i][j];
                }
            }
        }
        /* i calculated distance from one island to other but the last step lands on the other island so subtract 1*/
        return ans - 1;
    }
};