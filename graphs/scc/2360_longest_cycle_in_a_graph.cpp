#include <bits/stdc++.h>
using namespace std;

/*
    Problem 2360: Longest Cycle in a Graph
    Pattern: Kosaraju's Algorithm
    Time: O(V+E), Space: O(V+E)
*/

/*
    Approach:
    1. find the SCC's using kosaraju algorithm
    2. find the longest length cycle in the graph
        which is nothing but the length of the longest scc other than 1
*/

class Solution
{
public:
    vector<vector<int>> adj, radj;
    vector<bool> visited;
    vector<int> comp, order;

    void dfs1(int u)
    {
        visited[u] = true;
        for (auto v : adj[u])
        {
            if (!visited[v])
            {
                dfs1(v);
            }
        }
        order.push_back(u);
    }
    void dfs2(int u)
    {
        visited[u] = true;
        comp.push_back(u);
        for (auto v : radj[u])
        {
            if (!visited[v])
            {
                dfs2(v);
            }
        }
    }
    int longestCycle(vector<int> &edges)
    {
        int n = edges.size();
        adj.resize(n);
        radj.resize(n);
        comp.clear();

        for (int i = 0; i < n; i++)
        {
            if (edges[i] == -1)
                continue;
            adj[i].push_back(edges[i]);
            radj[edges[i]].push_back(i);
        }
        order.clear();
        visited.assign(n, false);
        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs1(i);
            }
        }
        reverse(order.begin(), order.end());

        comp.clear();
        fill(visited.begin(), visited.end(), false);
        int maxCycle = 0;
        for (auto i : order)
        {
            if (!visited[i])
            {
                dfs2(i);
                if (comp.size() > maxCycle)
                {
                    maxCycle = comp.size();
                }
                comp.clear();
            }
        }

        return maxCycle == 1 ? -1 : maxCycle;
    }
};