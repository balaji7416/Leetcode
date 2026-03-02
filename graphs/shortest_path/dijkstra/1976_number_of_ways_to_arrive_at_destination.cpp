#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1976: Number of Ways to Arrive at Destination
    Pattern: Dikstra + DP
    Time: O(ElogV), Space: O(V+E)
*/

/* Approach: 1

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
/* Approach: 2

1. Use Dijkstra to compute shortest distance from node 0 to all nodes.
2. Maintain two arrays:
   - dist[i]  → shortest distance to reach node i
   - ways[i]  → number of shortest ways to reach node i

3. Initialize:
   dist[0] = 0, ways[0] = 1

4. During relaxation of edge (u → v, weight w):

   a) If dist[u] + w < dist[v]:
        - Found a strictly shorter path
        - Update dist[v]
        - Replace ways[v] = ways[u]

   b) If dist[u] + w == dist[v]:
        - Found another shortest path
        - Add ways[u] to ways[v] (mod 1e9+7)

5. Since Dijkstra processes nodes in increasing distance order,
   all shortest contributions are accumulated correctly.

Time Complexity:  O((V + E) log V)
Space Complexity: O(V + E)
*/

#define ll long long
const ll mod = 1e9 + 7;
/* Approach - 1
build the dist array and traverse graph using dfs along those minimum cost edges*/
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

/*Approach - 2
    build no.of ways along with dijkstra
    more elegant
*/
class Solution
{
public:
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

        vector<ll> ways(n, 0); // ways[i] = no.of shortest ways to reach node i
        ways[0] = 1;
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
                    ways[v] = ways[u];
                    pq.push({dist[v], v});
                }
                else if (dist[u] + w == dist[v])
                {
                    ways[v] = (ways[u] + ways[v]) % mod;
                }
            }
        }
        return ways[n - 1];
    }
};