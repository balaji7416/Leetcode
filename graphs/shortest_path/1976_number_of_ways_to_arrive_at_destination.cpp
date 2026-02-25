#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1976: Number of Ways to Arrive at Destination
    Pattern: Dikstra + DP
    Time: O(ElogV), Space: O(V+E)
*/

/*
Approach:

1. Run Dijkstra from node 0 to compute the shortest distance to every node.
   dist[u] stores the minimum distance from 0 to u.

2. Observe that edges satisfying:
      dist[u] + w == dist[v]
   lie on some shortest path.
   These edges form a Directed Acyclic Graph (DAG),
   because distances strictly increase (weights are positive).

3. Now the problem reduces to:
   Count number of paths from node 0 to node n-1 in this shortest-path DAG.

4. Use DFS + memoization (dp):
   dp[u] = number of shortest paths from u to destination.
   Each node is computed only once.

Time Complexity:
    O(E log V)   (Dijkstra dominates)

Space Complexity:
    O(V + E)
*/

#define ll long long
const ll mod = 1e9 + 7;
class Solution
{
public:
    ll dfs(ll u, vector<vector<pair<ll, ll>>> &adj, vector<ll> &dist, vector<ll> &dp)
    {
        ll n = dist.size();
        if (u == n - 1)
            return 1;
        if (dp[u] != -1)
            return dp[u];
        ll ans = 0;
        for (auto [v, w] : adj[u])
        {
            if (dist[u] + w == dist[v])
            {
                ans = (ans + dfs(v, adj, dist, dp)) % mod;
            }
        }
        return dp[u] = ans;
    }
    int countPaths(int n, vector<vector<int>> &roads)
    {
        vector<vector<pair<ll, ll>>> adj(n);
        // make adj list
        for (ll i = 0; i < roads.size(); i++)
        {
            ll u = roads[i][0], v = roads[i][1], w = roads[i][2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // find the mincost with dijstra
        vector<ll> dist(n, LONG_LONG_MAX);
        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
        pq.push({0, 0}); //{w,u}
        dist[0] = 0;
        ll min_time = -1;
        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();

            // skip if edge is outdated
            if (d > dist[u])
                continue;

            for (auto [v, w] : adj[u])
            {
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        // explore all the paths from node 0 to node n-1 through dfs
        vector<ll> dp(n, -1);
        ll ans = dfs(0, adj, dist, dp);
        return ans;
    }
};