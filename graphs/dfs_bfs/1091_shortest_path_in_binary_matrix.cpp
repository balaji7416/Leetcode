#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1091: Shortest Path in Binary Matrix
    Pattern: BFS
    Time: O(n^2), Space: O(n^2)
*/

/*
Idea:
Use BFS on the grid (8 directions allowed) to find the shortest path
from (0,0) to (n-1,n-1).

Since the grid is unweighted, BFS guarantees the shortest path.
We maintain a dist matrix initialized to -1 to track:
    - whether a cell is visited
    - the shortest distance to reach it

Start from (0,0) if it is 0.
For each cell, explore all 8 neighbors.
If a neighbor is inside bounds, not blocked (grid == 0),
and not yet visited (dist == -1), update its distance as
dist[current] + 1 and push it into the queue.

Finally, return dist[n-1][n-1], which stores the shortest path length,
or -1 if unreachable.
*/

class Solution
{
public:
    void bfs(int i, int j, vector<vector<int>> &grid,
             vector<vector<int>> &dist)
    {
        int n = grid.size();
        if (grid[i][j] != 0 || grid[n - 1][n - 1] != 0)
            return;
        int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
        int dy[] = {1, -1, 0, 0, 1, -1, -1, 1};

        queue<pair<int, int>> q;
        q.push({i, j});
        dist[i][j] = 1;

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            for (int k = 0; k < 8; k++)
            {
                int nr = x + dx[k];
                int nc = y + dy[k];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n &&
                    grid[nr][nc] == 0 && dist[nr][nc] == -1)
                {
                    q.push({nr, nc});
                    dist[nr][nc] = dist[x][y] + 1;
                }
            }
        }
    }
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        bfs(0, 0, grid, dist);
        return dist[n - 1][n - 1];
    }
};