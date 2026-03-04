#include <bits/stdc++.h>
using namespace std;

/*
    Problem 200: Number of Islands
    Pattern: DSU / DFS / BFS
    Time: O(m*n), Space: O(m*n)
*/

/* Logic:

Model the 2D grid as a graph where each cell is a node.
Convert (i, j) → id = i*m + j to flatten the grid into a 1D structure,
so DSU can operate on m*n nodes.

Only land cells ('1') are considered active nodes.
Initially, treat every land cell as its own island (islands++).

Traverse the grid and for each land cell,
attempt to unite it with its right and down neighbors
(if they are also land).

If unite() returns true, it means two separate components merged,
so decrement islands.

Final islands count equals the number of connected components
among land cells.

Time: O(n*m * α(n*m))
Space: O(n*m)
*/

struct DSU
{
    int components;
    vector<int> parent, size;
    DSU(int n)
    {
        components = n;
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int find(int x)
    {
        if (parent[x] == x)
        {
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    bool unite(int x, int y)
    {
        int rootA = find(x);
        int rootB = find(y);
        if (rootA == rootB)
            return false;
        if (size[rootA] < size[rootB])
            swap(rootA, rootB);
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
        components--;
        return true;
    }
};
class Solution
{
public:
    int numIslands(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        DSU dsu(m * n);
        int islands = 0;
        vector<pair<int, int>> dir = {{0, 1}, {1, 0}};
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == '1')
                {
                    islands++;
                    for (auto [dx, dy] : dir)
                    {
                        int nr = i + dx;
                        int nc = j + dy;
                        if (nr < n && nc < m && grid[nr][nc] == '1')
                        {
                            if (dsu.unite(i * m + j, nr * m + nc))
                            {
                                islands--;
                            }
                        }
                    }
                }
            }
        }
        return islands;
    }
};