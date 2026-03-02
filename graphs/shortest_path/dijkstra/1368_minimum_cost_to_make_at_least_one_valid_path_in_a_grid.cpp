#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1368: Minimum Cost to Make at Least One Valid Path in a Grid
    Pattern: BFS
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea: 0-1 BFS
        it's just dijkstra disguised as 0-1 BFS
        use deque instead of priority queue which makes the edge access
        from O(logn) to O(1)
        everything else is same
*/
/**
 * IMPLEMENTATION:
 * - Treat the grid as a graph where each cell is a node.
 * - Each cell points in one direction for "free" (edge weight 0), and all other directions cost 1.
 * - Use 0-1 BFS with a deque:
 *     - push_front for 0-cost edges (following the cell's direction)
 *     - push_back for 1-cost edges (changing direction)
 * - Maintain `dist[r][c]` as the minimum cost to reach cell (r,c).
 * - Pop cells from the front of the deque, relax neighbors, and push them accordingly.
 * - Stop when bottom-right cell is reached.
 *
 * Time Complexity: O(N*M)
 *     - Each cell can be added to the deque at most 4 times (once per possible direction),
 *       so total operations proportional to number of edges (~4*N*M)
 * Space Complexity: O(N*M)
 *     - `dist` array stores minimum cost for each cell.
 *     - Deque can hold up to O(N*M) elements in the worst case.
 */

class Solution
{
public:
    pair<int, int> getPrc(int n, int r, int c)
    {
        if (n == 1)
        {
            return {r, c + 1};
        }
        else if (n == 2)
        {
            return {r, c - 1};
        }
        else if (n == 3)
        {
            return {r + 1, c};
        }
        else
        {
            return {r - 1, c};
        }
    }
    int minCost(vector<vector<int>> &grid)
    {
        int n = grid.size();    // rows
        int m = grid[0].size(); // cols
        vector<vector<int>> adj(n, vector<int>(m, 1));
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        deque<pair<int, int>> dq; //{row,col}
        dq.push_front({0, 0});
        dist[0][0] = 0;

        while (!dq.empty())
        {
            auto [r, c] = dq.front();
            dq.pop_front();

            if (r == n - 1 && c == m - 1)
                return dist[r][c];
            auto [pr, pc] = getPrc(grid[r][c], r, c); // get poinint row,col
            for (int i = 0; i < 4; i++)
            {
                int nr = r + dx[i];
                int nc = c + dy[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < m)
                {
                    int edge = 1;
                    if (nr == pr && nc == pc)
                    {
                        edge = 0;
                    }
                    if (dist[r][c] + edge < dist[nr][nc])
                    {
                        dist[nr][nc] = dist[r][c] + edge;
                        if (edge == 0)
                        {
                            dq.push_front({nr, nc});
                        }
                        else
                        {
                            dq.push_back({nr, nc});
                        }
                    }
                }
            }
        }

        // shouldn't reach here
        return dist[n - 1][m - 1];
    }
};