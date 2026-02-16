#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1162: As Far from Land as Possible
    Pattern: multi-source bfs
    Time: O(n^2), Space: O(n^2)
*/
/* idea:
Multi-Source BFS (Max Distance from Land)

1. Push all land cells (1) into the queue.
   → These act as multiple starting sources (distance = 0).

2. Initialize dist matrix with -1 (unvisited).

3. Run BFS:
   - For each popped cell,
     explore its 4 neighbors.
   - If neighbor is unvisited (-1),
     set dist = current_dist + 1
     and push into queue.

4. Since BFS expands level by level,
   each water cell gets its shortest
   distance from nearest land.

5. The maximum value in dist
   is the final answer.
*/

class Solution
{
public:
    void bfs(vector<vector<int>> &dist, vector<vector<int>> &grid)
    {
        int n = grid.size();
        queue<pair<int, int>> q;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
            }
        }
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
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
    int maxDistance(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        bool onefound = false, zerofound = false;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                    onefound = true;
                else if (grid[i][j] == 0)
                    zerofound = true;
            }
            if (onefound && zerofound)
                break;
        }
        if (!onefound || !zerofound)
            return -1;

        bfs(dist, grid);
        int ans = -1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][j] > ans)
                {
                    ans = dist[i][j];
                }
            }
        }
        return ans;
    }
};