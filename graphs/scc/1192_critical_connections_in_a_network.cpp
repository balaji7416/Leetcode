#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1192: Critical Connections in a Network
    Pattern: Tarjan's Algorithm
    Time: O(V+E), Space: O(V+E)
*/

/*
Tarjan Bridge Algorithm (Undirected Graph)

tin[u] = discovery time of node u
low[u] = earliest discovery time reachable from u (via DFS tree or back edge)

DFS logic:
- skip the parent edge
- after visiting child v: low[u] = min(low[u], low[v])
- back edge case: low[u] = min(low[u], tin[v])

Bridge condition:
if (low[v] > tin[u]) → edge (u, v) is a bridge
(v's subtree cannot reach u or any ancestor of u)

Key points:
- works for undirected graphs
- always ignore parent edge
- back edges update using tin[v], not low[v]
*/

struct tarjan
{
    int timer, n;
    vector<int> tin, low;
    vector<vector<int>> adj;
    vector<vector<int>> bridges;
    // vector<bool> inStack;

    tarjan(int n)
    {
        this->n = n;
        timer = 0;
        tin.resize(n, -1);
        low.resize(n);
        //  inStack.resize(n,false);
        adj.resize(n);
        bridges.clear();
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfs(int u, int parent)
    {
        tin[u] = low[u] = timer++;
        // inStack[u] = true;

        for (auto v : adj[u])
        {
            if (v == parent)
                continue;

            if (tin[v] == -1)
            {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u])
                {
                    bridges.push_back({u, v});
                }
            }
            else
            {
                low[u] = min(low[u], tin[v]);
            }
        }
    }

    void run()
    {
        for (int i = 0; i < n; i++)
        {
            if (tin[i] == -1)
            {
                dfs(i, -1);
            }
        }
    }
};

class Solution
{
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>> &connections)
    {
        tarjan tr(n);
        for (auto &conn : connections)
        {
            tr.addEdge(conn[0], conn[1]);
        }
        tr.run();

        return tr.bridges;
    }
};