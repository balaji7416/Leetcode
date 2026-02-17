#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1293: Shortest Path in a Grid with Obstacles Elimination
    Pattern: BFS
    Time: O(m*n*k), Space: O(m*n*k)
*/
/**
 * LOGIC:
 * BFS in 3D state space (row, col, remaining eliminations)
 * - State: (x, y, k) where k = obstacles you can still eliminate
 * - From current state, try 4 directions
 * - If cell is obstacle, reduce k by 1
 * - Visited tracks (x,y,k) to avoid revisiting same state
 * - Early exit: if k >= Manhattan distance, take shortest path directly
 * - Level-order BFS ensures first time reaching target = min steps
 */

class Solution
{
public:
    int shortestPath(vector<vector<int>> &grid, int k)
    {
        int n = grid.size();    // rows
        int m = grid[0].size(); // cols
        // if the k >= manhattan distance then return shortest distance possible right away
        if (k >= n + m - 2)
            return n + m - 2;
        vector<vector<vector<bool>>> visited(
            n, vector<vector<bool>>(m, vector<bool>(k + 1, false)));

        queue<tuple<int, int, int>> q;
        q.push({0, 0, k});
        visited[0][0][k] = true;
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        int steps = 0;
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {

                auto [x, y, z] = q.front();
                q.pop();

                if (x == n - 1 && y == m - 1)
                    return steps;
                for (int i = 0; i < 4; i++)
                {
                    int nr = x + dx[i];
                    int nc = y + dy[i];
                    bool inbounds = nr >= 0 && nr < n && nc >= 0 && nc < m;
                    int nk = z + (inbounds ? (grid[nr][nc] == 1 ? -1 : 0) : 0);
                    if (inbounds && nk >= 0 && !visited[nr][nc][nk])
                    {
                        visited[nr][nc][nk] = true;
                        q.push({nr, nc, nk});
                    }
                }
            }
            steps++;
        }
        return -1;
    }
};