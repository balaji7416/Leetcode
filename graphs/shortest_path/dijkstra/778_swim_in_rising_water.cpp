#include <bits/stdc++.h>
using namespace std;

/*
    Problem 778: Swim in Rising Water
    Pattern: BFS
    Time: O(n^2log(n)), Space: O(n^2)
*/

/* Approach 1: Dijkstra
Treat each cell as a node and apply Dijkstra.

1. dist[r][c] = minimum time required to reach cell (r,c),
   where time of a path is the maximum elevation seen along that path.

2. Use a min-heap storing {time, row, col}.
   Start from (0,0) with time = grid[0][0].

3. For each popped cell:
   - Try 4-directional neighbors.
   - New time = max(current path time, neighbor elevation).
   - If this time is smaller than dist[nr][nc], update and push to heap.

4. Since Dijkstra processes states in increasing time order,
   the first time we reach (n-1,n-1) is the minimum possible answer.

Time:  O(n² log n)
Space: O(n²)
*/

/* Approach 2: DFS + Binary Search
1. Binary search on the minimum time (water level).
   - low = minimum possible value
   - high = maximum possible value

2. For each mid:
   - Run DFS from (0,0)
   - Only move to cells with grid[i][j] <= mid
   - If we can reach (n-1,n-1), then this mid is valid

3. If reachable:
      - Store answer
      - Try smaller value (high = mid - 1)
   Else:
      - Increase water level (low = mid + 1)

4. Final answer is the smallest mid for which a path exists.

Time Complexity:
- DFS takes O(n²)
- Binary search runs O(log(n²)) ≈ O(log n)
- Overall: O(n² log n)

Space Complexity:
- O(n²) for visited array
- O(n²) recursion stack in worst case
*/

/* Approach 1: Dijkstra*/
class Solution
{
public:
    int swimInWater(vector<vector<int>> &grid)
    {
        int n = grid.size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        int dx[] = {1, -1, 0, 0};
        int dy[] = {0, 0, 1, -1};
        pq.push({grid[0][0], 0, 0});
        dist[0][0] = grid[0][0];
        int t = 0;
        while (!pq.empty())
        {
            auto [d, r, c] = pq.top();
            pq.pop();

            // skip processing outdated entries
            if (d > dist[r][c])
                continue;

            // return immediately if required square found
            if (r == n - 1 && c == n - 1)
            {
                return d;
            }

            for (int i = 0; i < 4; i++)
            {
                int nr = r + dx[i];
                int nc = c + dy[i];
                if (nr >= 0 && nr < n && nc >= 0 && nc < n)
                {
                    int t = max(dist[r][c], grid[nr][nc]);
                    if (t < dist[nr][nc])
                    {
                        dist[nr][nc] = t;
                        pq.push({t, nr, nc});
                    }
                }
            }
        }
        // shouldn't reach here
        return 0;
    }
};

/* Approach 2: DFS + Binary Search
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

class Solution
{
public:
    bool isValid(int mid, int i, int j, vector<vector<bool>> &visited,
                 vector<vector<int>> &grid)
    {
        int n = grid.size();
        if (i < 0 || i >= n || j < 0 || j >= n)
        {
            return false;
        }
        if (visited[i][j] || grid[i][j] > mid)
        {
            return false;
        }
        if (i == n - 1 && j == n - 1)
            return true;
        visited[i][j] = true;
        for (int k = 0; k < 4; k++)
        {
            if (isValid(mid, i + dx[k], j + dy[k], visited, grid))
            {
                return true;
            }
        }
        return false;
    }
    int swimInWater(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int low = 0, high = n * n;
        int ans = n * n;
        while (low <= high)
        {
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            int mid = low + (high - low) / 2;
            if (isValid(mid, 0, 0, visited, grid))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};
*/
