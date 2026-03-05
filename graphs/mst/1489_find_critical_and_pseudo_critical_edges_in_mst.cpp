#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1489: Find Critical and Pseudo-Critical Edges in Minimum Spanning Tree
    Pattern: DSU + Kruskal's Algorithm
    Time: O(E log E + E^2 α(V)) => O(E^2), Space: O(V+E)
*/
/* Approach:
Time Complexity:
O(E log E + E^2 α(V))

- Sorting edges for Kruskal: O(E log E)
- For each edge we run Kruskal up to two times: O(E * (E α(V)))
- α(V) is inverse Ackermann from DSU (≈ constant)

Overall: O(E^2)

Space Complexity:
O(V + E)

- DSU structures: O(V)
- Edge list: O(E)
- Answer storage: O(E)

Logic:

1. First compute the global MST cost using Kruskal.

2. For each edge i we test two MST properties:

   (A) Critical Edge (Cut Edge Property)
   -------------------------------------
   Remove edge i and recompute MST.

   If MST cost increases (or MST cannot form),
   then edge i is CRITICAL.

   Reason:
   By the cut property, this edge is the minimum
   crossing edge for some cut. Removing it forces
   the MST to use a heavier edge.

   condition:
   mst_without_i > global_mst


   (B) Pseudo-Critical Edge
   ------------------------
   Force include edge i first, then run Kruskal
   on remaining edges.

   If MST cost remains equal to global MST,
   then edge i is PSEUDO-CRITICAL.

   Reason:
   The edge can appear in at least one MST,
   but it is not mandatory because another
   equal-weight choice exists.

   condition:
   forced_edge_cost + mst_remaining == global_mst

3. Store original indices of edges before sorting
   so answers correspond to the original graph.
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
int krushkal(vector<vector<int>> &edges, DSU dsu, int rm_idx, int e)
{
    int mst_cost = 0;
    int n = edges.size();
    for (int i = 0; i < n; i++)
    {
        if (i == rm_idx)
            continue;
        int u = edges[i][0], v = edges[i][1], w = edges[i][2];
        if (dsu.unite(u, v))
        {
            mst_cost += w;
            if (dsu.components == 1)
                return mst_cost;
        }
    }
    return mst_cost;
}
class Solution
{
public:
    vector<vector<int>>
    findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>> &edges)
    {
        if (edges.size() == n - 1)
        {
            vector<vector<int>> ans;
            vector<int> criticalEdges;
            for (int i = 0; i < edges.size(); i++)
            {
                criticalEdges.push_back(i);
            }
            ans.push_back(criticalEdges);
            ans.push_back({});
            return ans;
        }

        // store indices before sorting
        for (int i = 0; i < edges.size(); i++)
        {
            edges[i].push_back(i);
        }

        // sort by edge weight
        auto comp = [&](vector<int> &a, vector<int> &b)
        { return a[2] < b[2]; };
        sort(edges.begin(), edges.end(), comp);

        // calculate the global_mst cost
        DSU dsu(n);
        int mst_cost = krushkal(edges, dsu, -1, 0);

        vector<vector<int>> ans;
        vector<int> cutEdges;
        vector<int> pseudoEdges;

        for (int i = 0; i < edges.size(); i++)
        {
            DSU dsu2(n);
            if (krushkal(edges, dsu2, i, 0) != mst_cost)
            {
                cutEdges.push_back(edges[i][3]); // push the idx in original arr
            }
            else
            {
                DSU dsu3(n);
                dsu3.unite(edges[i][0], edges[i][1]);
                if (krushkal(edges, dsu3, i, 1) + edges[i][2] == mst_cost)
                {
                    pseudoEdges.push_back(edges[i][3]); // push the idx in org arr
                }
            }
        }

        ans.push_back(cutEdges);
        ans.push_back(pseudoEdges);
        return ans;
    }
};