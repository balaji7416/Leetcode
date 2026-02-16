#include <bits/stdc++.h>
using namespace std;

/*
    Problem 542: 01 Matrix
    Pattern: multi-source bfs
    Time: O(m*n), Space: O(m*n)
*/

/* idea:
Multi-Source BFS (01 Matrix)

1. Push all cells containing 0 into the queue.
   → These act as multiple starting points (distance = 0).

2. Initialize dist matrix with -1 (unvisited).

3. Run BFS:
   - For each cell popped,
     check its 4 neighbors.
   - If a neighbor is unvisited (-1),
     set dist = current_dist + 1
     and push it into the queue.

4. Since BFS expands level by level,
   the first time a cell is visited,
   it gets the shortest distance
   to the nearest 0.
*/

class Solution
{
public:
    void bfs(vector<vector<int>> &dist, vector<vector<int>> &mat)
    {
        int n = mat.size();
        int m = mat[0].size();
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (mat[i][j] == 0)
                { // if cell has 0
                    q.push({i, j});
                    dist[i][j] = 0; // it's distance from 0's cell is 0
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
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && dist[nr][nc] == -1)
                {
                    dist[nr][nc] = 1 + dist[x][y];
                    q.push({nr, nc});
                }
            }
        }
    }
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        int n = mat.size();    // rows
        int m = mat[0].size(); // cols
        vector<vector<int>> dist(n, vector<int>(m, -1));
        bfs(dist, mat);
        return dist;
    }
};