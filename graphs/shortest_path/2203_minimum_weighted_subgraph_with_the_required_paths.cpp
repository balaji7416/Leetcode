#include <bits/stdc++.h>
using namespace std;

/*
    Problem 2203: Minimum Weighted Subgraph with the Required Paths
    Pattern: Dijstra
    Time: O((n + m) log n), Space: O(n + m)
*/

/*
LOGIC:
------
Goal:
We want the minimum total weight of a subgraph such that:
- src1 can reach dest
- src2 can reach dest
- They are allowed to share part of the path

Key Insight:
Instead of fixing paths greedily, we allow both sources to
converge at some intermediate node 'i' and then share the path
from 'i' to dest.

So for every node i, we compute:

    dist1[i] = shortest distance from src1 to i
    dist2[i] = shortest distance from src2 to i
    dist3[i] = shortest distance from i to dest

Then the answer is:

    min over all i of (dist1[i] + dist2[i] + dist3[i])

Implementation Details:
- Run Dijkstra from src1 → fill dist1
- Run Dijkstra from src2 → fill dist2
- Reverse the graph
- Run Dijkstra from dest on reversed graph → fill dist3
  (this gives shortest distance from any node to dest)
- Iterate over all nodes and compute the minimum valid sum

If no such node exists, return -1.

TIME COMPLEXITY:
----------------
Each Dijkstra: O((n + m) log n)
We run it 3 times.

Total:
    O((n + m) log n)

SPACE COMPLEXITY:
-----------------
Adjacency list: O(n + m)
Three distance arrays: O(n)
Priority queue: O(n)

Total:
    O(n + m)
*/

#define ll long long
class Solution
{
public:
    long long minimumWeight(int n, vector<vector<int>> &edges, int src1,
                            int src2, int dest)
    {
        vector<vector<pair<ll, ll>>> adj(n);
        for (auto vec : edges)
        {
            ll u = vec[0], v = vec[1], w = vec[2];
            adj[u].push_back({v, w});
        }

        priority_queue<pair<ll, ll>, vector<pair<ll, ll>>,
                       greater<pair<ll, ll>>>
            pq;

        // find the shortest path for all nodes from src1
        vector<ll> dist1(n, LONG_LONG_MAX);
        pq.push({0, src1});
        dist1[src1] = 0;
        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist1[u])
                continue;

            for (auto [v, w] : adj[u])
            {
                if (dist1[u] + w < dist1[v])
                {
                    dist1[v] = dist1[u] + w;
                    pq.push({dist1[v], v});
                }
            }
        }

        // while (!pq.empty())
        //     pq.pop();

        pq = {};

        // find the shortest path for all nodes from src2
        vector<ll> dist2(n, LONG_LONG_MAX);
        pq.push({0, src2});
        dist2[src2] = 0;

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist2[u])
                continue;

            for (auto [v, w] : adj[u])
            {
                if (dist2[u] + w < dist2[v])
                {
                    dist2[v] = dist2[u] + w;
                    pq.push({dist2[v], v});
                }
            }
        }

        // while (!pq.empty())
        //     pq.pop();

        pq = {};

        // reverse edges
        adj = vector<vector<pair<ll, ll>>>(n);
        for (auto vec : edges)
        {
            ll u = vec[0], v = vec[1], w = vec[2];
            adj[v].push_back({u, w});
        }

        // find the shortest path for all nodes to dest
        vector<ll> dist3(n, LONG_LONG_MAX);
        pq.push({0, dest});
        dist3[dest] = 0;

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist3[u])
                continue;

            for (auto [v, w] : adj[u])
            {
                if (dist3[u] + w < dist3[v])
                {
                    dist3[v] = dist3[u] + w;
                    pq.push({dist3[v], v});
                }
            }
        }

        /* dist1[i] = min dist from src1 to node i
           dist2[i] = min dist from src2 to node i
           dist3[i] = min dist from node i to dest

           ans = min(dist1[i]+dist2[i]+dist3[i]) for all 0 <= i <= n-1
        */

        auto isSafe =
            [&](ll a, ll b, ll c)
        {
            return a != LONG_LONG_MAX && b != LONG_LONG_MAX && c != LONG_LONG_MAX;
        };

        ll ans = LONG_LONG_MAX;
        for (int i = 0; i < n; i++)
        {
            if (isSafe(dist1[i], dist2[i], dist3[i]) &&
                dist1[i] + dist2[i] + dist3[i] < ans)
            {
                ans = dist1[i] + dist2[i] + dist3[i];
            }
        }
        return ans == LONG_LONG_MAX ? -1 : ans;
    }
};