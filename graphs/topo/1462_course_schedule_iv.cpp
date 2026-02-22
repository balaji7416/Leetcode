#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1462: Course Schedule IV
    Pattern: DFS
    Time: O(n^3) space: O(n^2)
*/

/*
For each query (src, dest):

Use DFS to check if dest is reachable from src.
Use a 2D dp array where:
    dp[u][v] = 1  → reachable
    dp[u][v] = 0  → not reachable
    dp[u][v] = -1 → not computed yet

During DFS:
    - If dp[src][dest] is already computed → reuse it.
    - Otherwise, try all neighbors of src.
    - If any neighbor can reach dest → mark dp[src][dest] = 1.
    - Else mark dp[src][dest] = 0.

Since the graph is a DAG, recursion always terminates.
Memoization ensures each (u, v) pair is computed at most once.
*/

class Solution
{
public:
    // no need for visited array since the problems garauntees to graph to DAG
    bool dfs(int src, int dest, vector<vector<int>> &adj, vector<vector<int>> &dp)
    {
        if (dp[src][dest] != -1)
        {
            return dp[src][dest];
        }
        // if(src == dest) return dp[src][dest] = true;
        // visited[src] = true;
        for (auto v : adj[src])
        {
            if (v == dest || dfs(v, dest, adj, dp))
            {
                return dp[src][dest] = true;
            }
        }
        return dp[src][dest] = false;
    }
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries)
    {
        int n = numCourses;
        vector<vector<int>> adj(n);
        for (int i = 0; i < prerequisites.size(); i++)
        {
            int u = prerequisites[i][0];
            int v = prerequisites[i][1];
            adj[u].push_back(v);
        }
        vector<vector<int>> dp(n, vector<int>(n, -1));
        vector<bool> visited(n, false);
        vector<bool> ans(queries.size(), false);
        for (int i = 0; i < queries.size(); i++)
        {
            int u = queries[i][0], v = queries[i][1];
            if (dfs(u, v, adj, dp))
            {
                ans[i] = true;
            }
            // visited = vector<bool>(n,false);
        }
        return ans;
    }
};