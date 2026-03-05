#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1584: Min Cost to Connect All Points
    Pattern: DSU + Kruskal's Algorithm
    Time: with krushkal -> O(n^2 log n), with prims -> O(n^2)
    Space: O(n^2) ; n->number of points
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

/*prims*/
class Solution
{
public:
    int minCostConnectPoints(vector<vector<int>> &points)
    {
        int n = points.size();
        vector<int> dist(n, INT_MAX);   // cost of nodes to be added in mst
        vector<bool> visited(n, false); // nodes in mst

        dist[0] = 0;
        int cost = 0;
        for (int i = 0; i < n; i++)
        {
            int u = -1;

            // pick the min cost node
            for (int j = 0; j < n; j++)
            {
                if (!visited[j] && (u == -1 || dist[j] < dist[u]))
                {
                    u = j;
                }
            }

            cost += dist[u];
            visited[u] = true;

            // update the distances
            int x1 = points[u][0], y1 = points[u][1];
            for (int v = 0; v < n; v++)
            {
                if (!visited[v])
                {
                    int x2 = points[v][0], y2 = points[v][1];
                    int w = abs(x2 - x1) + abs(y2 - y1);
                    dist[v] = min(dist[v], w);
                }
            }
        }
        return cost;
    }
};

/*Krushkal's Algorithm*/
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