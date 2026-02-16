#include <bits/stdc++.h>
using namespace std;

/*
    Problem 994: Rotting Oranges
    Pattern: multi-source bfs
    Time: O(m*n), Space: O(m*n)
*/
/* idea:
Multi-Source BFS Approach (Rotten Oranges)

1. Push all initially rotten oranges (value 2) into the queue.
   → These act as multiple starting sources (time = 0).

2. Initialize distance grid with:
   - -1 for fresh oranges (unvisited)
   -  0 for rotten oranges
   - -2 for empty cells (blocked)

3. Run BFS:
   - For each cell popped from queue,
     visit its 4-direction neighbors.
   - If neighbor is fresh (dist == -1),
     set dist = current_dist + 1
     and push into queue.

4. After BFS:
   - If any fresh orange remains (-1), return -1.
   - Otherwise, the maximum value in dist
     is the total time required.
*/

class Solution
{
public:
    void bfs(vector<vector<int>> &dist, vector<vector<int>> &grid)
    {
        int n = dist.size();
        int m = dist[0].size();

        queue<pair<int, int>> q;
        // push all the srcs (rotten oranges)
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 2)
                { // if orange is rotten
                    q.push({i, j});
                    dist[i][j] = 0; // rotten at min 0
                }
                else if (grid[i][j] == 0)
                {
                    dist[i][j] = -2; // not visitable (blank)
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
                    dist[nr][nc] = dist[x][y] + 1;
                    q.push({nr, nc});
                }
            }
        }
    }
    int orangesRotting(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> dist(n, vector<int>(m, -1));
        bfs(dist, grid);
        int time = 0;
        for (auto vec : dist)
        {
            for (auto t : vec)
            {
                if (t > time)
                {
                    time = t;
                }
                if (t == -1)
                { // if there's a fresh orange left
                    return -1;
                }
            }
        }
        return time;
    }
};