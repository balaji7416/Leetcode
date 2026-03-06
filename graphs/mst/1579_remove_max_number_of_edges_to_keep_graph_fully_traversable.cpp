#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1579: Remove Max Number of Edges to Keep Graph Fully Traversable
    Pattern: DSU
    Time: O(E log E), Space: O(V+E)
*/

/* Approach:
Greedy + DSU

Idea:
Type 3 edges are most valuable since both Alice and Bob can use them.
Sort edges so type 3 are processed first.

1. Build Alice's MST using type 1 + type 3 edges.
2. Build Bob's MST using type 2 + type 3 edges.
3. Track which edges were used in Alice's MST to avoid double counting.
4. If either graph cannot become fully connected return -1.

Answer = total_edges - edges_used

Time: O(E log E + E α(N))
Space: O(N)
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
    int maxNumEdgesToRemove(int n, vector<vector<int>> &edges)
    {
        int m = edges.size();
        auto comp = [&](vector<int> &a, vector<int> &b)
        {
            return a[0] > b[0];
        };
        sort(edges.begin(), edges.end(), comp);
        vector<bool> used(m, false);
        int e = 0;

        // build mst for alice (type 1 + type 3)
        DSU dsu1(n);
        for (int i = 0; i < m; i++)
        {
            int type = edges[i][0], u = edges[i][1], v = edges[i][2];
            u--;
            v--;
            if (type == 2)
                continue;
            if (dsu1.unite(u, v))
            {
                used[i] = true;
                e++;
            }
            if (dsu1.components == 1)
                break;
        }

        // if alice can't travel fully
        if (dsu1.components != 1)
            return -1;

        // build mst for bob (type 2 + type 3)
        DSU dsu2(n);
        for (int i = 0; i < m; i++)
        {
            int type = edges[i][0], u = edges[i][1], v = edges[i][2];
            u--;
            v--;
            if (type == 1)
                continue;
            if (dsu2.unite(u, v) && !used[i])
            {
                e++;
            }
            if (dsu2.components == 1)
                break;
        }

        // if bob can't travel fully
        if (dsu2.components != 1)
            return -1;

        // total edges-used edges
        return m - e;
    }
};