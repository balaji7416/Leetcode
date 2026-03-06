#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1697: Checking Existence of Edge-Length Limited Paths
    Pattern: MST
    Time: O(m logm + q log q), Space: O(n+q)
*/

/*
Offline DSU + Sorting

Observation:
A query (p, q, limit) asks if there exists a path between p and q using
only edges with weight < limit.


Approach:
1. Sort edgeList by edge weight.
2. Attach original index to each query and sort queries by limit.
3. Use a DSU and a pointer j over edgeList.
4. For each query (in increasing limit order):
      - Add all edges with weight < limit into DSU (union).
      - *** Check if p and q belong to the same component. ***
5. Store result using the original query index.

Key Idea:
As limits increase, more edges become usable. Since both edges and queries
are sorted, each edge is processed only once.

Time:  O((E + Q) log(E + Q))  ~ sorting dominates
DSU:   O((E + Q) α(N))
Space: O(N + Q)
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
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edgeList, vector<vector<int>> &queries)
    {
        int m = edgeList.size();
        int q = queries.size();
        for (int i = 0; i < q; i++)
        {
            queries[i].push_back(i);
        }
        auto comp = [&](vector<int> &a, vector<int> &b)
        {
            return a[2] < b[2];
        };
        sort(edgeList.begin(), edgeList.end(), comp);
        sort(queries.begin(), queries.end(), comp);

        DSU dsu(n);
        vector<bool> ans(q, false);
        int j = 0;
        for (int i = 0; i < q; i++)
        {
            int l = queries[i][2], p = queries[i][0], q = queries[i][1];
            int idx = queries[i][3];
            while (j < m && edgeList[j][2] < l)
            {
                int u = edgeList[j][0], v = edgeList[j][1];
                dsu.unite(u, v);
                j++;
            }
            if (dsu.find(p) == dsu.find(q))
            {
                ans[idx] = true;
            }
        }
        return ans;
    }
};
