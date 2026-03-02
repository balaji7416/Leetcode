#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1319: Number of Operations to Make Network Connected
    Pattern: DSU / BFS / DFS
    Time: O(V+E), Space: O(V)
*/

/* #NOTE:
    this problem can be solved using either of these:
    1. DSU
    2. BFS
    3. DFS
*/
/* APPROACH:
    Goal: Connect all n computers using given connections.

    Key Observations:
    1. To connect n nodes, we need at least n-1 edges.
       - If connections.size() < n-1 → impossible → return -1.

    2. Use DSU (Disjoint Set Union) to track connected components:
       - Initialize each node as its own component.
       - For each connection (u, v):
           • Unite u and v.
           • DSU keeps track of number of components.

    3. After processing all edges:
       - Number of operations needed = components - 1
         (connect all components with minimal extra edges).

    Complexity:
       - Time: O(E * α(N)) ≈ O(E)
       - Space: O(N)
*/

struct DSU
{
    int components;
    vector<int> parent, size;
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
        int rootA = find(x);
        int rootB = find(y);
        if (rootA == rootB)
        {
            return false;
        }
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
    int makeConnected(int n, vector<vector<int>> &connections)
    {
        DSU dsu(n);
        /*e could hanndle the note possible case by just the fact that
        we need atleast n-1 edges to connect n nodes,
        or you can use the extra logic i used(commented out), but seriously
        that's a overkill
        */
        // int extra = 0;
        if (connections.size() < n - 1)
            return -1;
        for (auto e : connections)
        {
            int u = e[0], v = e[1];
            dsu.unite(u, v);
            // if(!dsu.unite(u,v)){
            //     extra++;
            // }
        }
        // if(dsu.components -1 > extra){
        //     return -1;
        // }
        return dsu.components - 1;
    }
};