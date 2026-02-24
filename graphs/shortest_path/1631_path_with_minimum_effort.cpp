#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1631: Path With Minimum Effort
    Pattern: BFS
    Time: O(n*m log(n*m)), Space: O(m*n)
*/
/*
    Problem: Path With Minimum Effort (Leetcode 1631)

    Idea:
    Treat the grid as a graph where each cell is a node and edges
    connect adjacent cells with weight = absolute height difference.

    The path cost is defined as the maximum edge weight along the path.
    We need to minimize this maximum value.

    This is a classic "minimum bottleneck path" problem.
    Use Dijkstra’s algorithm with a modified relaxation:
        newCost = max(currentCost, edgeWeight)
    the only change is from dist[u]+w to max(dist[u], w).
    Time Complexity:  O(n*m log(n*m))
    Space Complexity: O(n*m)
*/

class Solution
{
public:
    int minimumEffortPath(vector<vector<int>> &heights)
    {
        int n = heights.size();
        int m = heights[0].size();

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        pq.push({0, 0, 0});
        dist[0][0] = 0;

        while (!pq.empty())
        {
            auto [effort, r, c] = pq.top();
            pq.pop();

            // skip outdated entries
            if (effort > dist[r][c])
                continue;

            // return ans if reached dest
            if (r == n - 1 && c == m - 1)
                return effort;

            // try four directions
            for (int i = 0; i < 4; i++)
            {
                int nr = r + dx[i];
                int nc = c + dy[i];

                if (nr >= 0 && nr < n && nc >= 0 && nc < m)
                {
                    int cost = abs(heights[nr][nc] - heights[r][c]);
                    int newCost = max(cost, effort);
                    if (newCost < dist[nr][nc])
                    {
                        dist[nr][nc] = newCost;
                        pq.push({newCost, nr, nc});
                    }
                }
            }
        }

        // won't reach here
        return 0;
    }
};