#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1584: Min Cost to Connect All Points
    Pattern: DSU + Kruskal's Algorithm
    Time: O(V+E), Space: O(V)
*/

/* Logic:

    Idea: Build Minimum Spanning Tree using Kruskal's Algorithm.

    1. Model the problem as a complete graph:
       - Each point = node
       - Edge weight = Manhattan distance between two points

    2. Generate all possible edges (since graph is complete).

    3. Sort edges in increasing order of weight.

    4. Use DSU to greedily add edges:
       - If adding an edge connects two different components,
         include it in the MST (no cycle formed).
       - If both nodes already belong to same component,
         skip it (would create cycle).

    5. Stop when all nodes are connected
       (i.e., only one component remains).

    This guarantees minimum total cost because
    we always choose the smallest valid edge first
    (Greedy choice + cycle prevention via DSU).
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
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        vector<tuple<int, int, int>> edges;
        int n = points.size();
        for (int i = 0; i < n; i++)
        {
            int u1 = points[i][0], v1 = points[i][1];
            for (int j = i + 1; j < n; j++)
            {
                int u2 = points[j][0], v2 = points[j][1];
                int w = abs(u2 - u1) + abs(v2 - v1);
                edges.push_back({w, i, j});
            }
        }
        sort(edges.begin(), edges.end());
        DSU dsu(n);
        int cost = 0;
        for (auto [w, u, v] : edges)
        {
            if (dsu.unite(u, v))
            {
                cost += w;
            }
            if (dsu.components == 1)
                break;
        }
        return cost;
    }
};