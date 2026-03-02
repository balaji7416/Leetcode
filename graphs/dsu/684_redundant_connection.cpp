#include <bits/stdc++.h>
using namespace std;

/*
    Problem 684: Redundant Connection
    Pattern: DSU
    Time: O(Ek), space: O(E)
        where k = ackerman constant which is at most 4 for any real constraints
*/
/* Logic:
    The graph was originally a tree (n nodes, n-1 edges).
    Adding one extra edge creates exactly one cycle.

    We use Disjoint Set Union (Union-Find) to detect that cycle.

    - Initialize DSU with each node as its own parent.
    - For each edge (u, v):
        • If u and v belong to different components,
          unite them (merge the sets).
        • If they already have the same root,
          adding this edge forms a cycle.
          → This edge is the redundant one.

    Since DSU uses:
        - Path Compression (in find)
        - Union by Size

    Each operation runs in amortized O(α(N)),
    so total complexity ≈ O(E).
*/

struct DSU
{
    vector<int> parent, size;
    int components;
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
        components = n;
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
    vector<int> findRedundantConnection(vector<vector<int>> &edges)
    {
        // use can use n = edges.size() as the graph is initially a tree
        DSU dsu(1000);
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0], v = edges[i][1];
            u--;
            v--;
            if (!dsu.unite(u, v))
            {
                return {u + 1, v + 1};
            }
        }
        // shouldn't reach here
        return {};
    }
};