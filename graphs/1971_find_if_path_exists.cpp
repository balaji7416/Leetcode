#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1971: Find if Path Exists in Graph
    Pattern: DFS
    Time: O(V+E)
*/
/*
    idea:
        run dfs from src
        if the destination is reachable
        from src, return true
        else return false
*/

class Solution
{
public:
    bool dfs(int src, int dest, vector<vector<int>> &adj, vector<bool> &visited)
    {
        if (src == dest)
        {
            return true;
        }
        visited[src] = true;
        for (auto n : adj[src])
        {
            if (visited[n])
                continue;
            if (dfs(n, dest, adj, visited))
            {
                return true;
            }
        }
        return false;
    }
    bool validPath(int n, vector<vector<int>> &edges, int source, int destination)
    {
        vector<bool> visited(n, false);
        vector<vector<int>> adj(n);
        for (int i = 0; i < edges.size(); i++)
        {
            adj[edges[i][0]].push_back(edges[i][1]);
            adj[edges[i][1]].push_back(edges[i][0]);
        }
        return dfs(source, destination, adj, visited);
    }
};