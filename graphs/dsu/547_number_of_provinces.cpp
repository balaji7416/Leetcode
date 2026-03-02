#include <bits/stdc++.h>
using namespace std;

/*
    Problem 547: Number of Provinces
    Pattern: DSU / BFS / DFS
    Time: O(V+E), Space: O(V)
*/

/*
    this problem can be solved using either:
    1. DSU
    2. BFS
    3. DFS
*/
/* Approach:
   Goal: Find the number of connected components in the graph.
   just build the dsu and return the number of components
   or just use bfs/dfs to find the number of connected components
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
            parent[i] = i;
    }
    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int x, int y)
    {
        int rootA = find(x), rootB = find(y);
        if (rootA == rootB)
            return false;
        if (size[rootA] < size[rootB])
        {
            swap(rootA, rootB);
        }
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
        components--;
        return true;
    }
};

class Solution
{
public:
    int findCircleNum(vector<vector<int>> &isConnected)
    {
        int n = isConnected.size();
        DSU dsu(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (isConnected[i][j])
                {
                    dsu.unite(i, j);
                }
            }
        }
        return dsu.components;
    }
};