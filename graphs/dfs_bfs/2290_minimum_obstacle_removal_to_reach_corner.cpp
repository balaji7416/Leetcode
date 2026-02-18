#include <bits/stdc++.h>
using namespace std;

/*
    Problem 2290: Minimum Obstacle Removal to Reach Corner
    Pattern: BFS

    Time Complexity:  O(n * m)
    Each cell can be relaxed at most a constant number of times,
    and each edge (4 directions per cell) is processed once.

    Space Complexity: O(n * m)
    For the dist matrix and deque in the worst case.
*/

/* idea:
We use 0-1 BFS because each move has cost either 0 (empty cell) or 1 (obstacle).
Maintain a dist matrix where dist[r][c] stores the minimum obstacles removed
to reach that cell.

Use a deque:
- If moving to a neighbor costs 0, push it to the front.
- If moving costs 1, push it to the back.

This ensures cells are processed in non-decreasing order of cost,
similar to Dijkstra but optimized for 0/1 weights.

We relax edges:
If dist[x][y] + cost < dist[nr][nc], update and push accordingly.

Early return is safe because 0-1 BFS guarantees that when a cell is popped
from the deque, its distance is already minimal.
*/

class Solution
{
public:
    int minimumObstacles(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        deque<pair<int, int>> dq;
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dq.push_front({0, 0});
        dist[0][0] = 0;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        while (!dq.empty())
        {
            auto [x, y] = dq.front();
            dq.pop_front();
            if (x == n - 1 && y == m - 1)
            {
                return dist[x][y];
            }
            for (int i = 0; i < 4; i++)
            {
                int nr = x + dx[i];
                int nc = y + dy[i];
                bool inbounds = nr >= 0 && nr < n && nc >= 0 && nc < m;
                int ext = (inbounds ? (grid[nr][nc] == 1 ? 1 : 0) : 0);
                if (inbounds && dist[x][y] + ext < dist[nr][nc])
                {
                    dist[nr][nc] = dist[x][y] + ext;
                    if (ext == 0)
                        dq.push_front({nr, nc});
                    else
                        dq.push_back({nr, nc});
                }
            }
        }
        return 0;
    }
};