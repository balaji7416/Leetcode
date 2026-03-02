#include <bits/stdc++.h>
using namespace std;

/*
    Problem 787: Cheapest Flights Within K Stops
    Pattern: Dijkstra / BFS
    Time: O((E * k) log (E * k)), Space: O(E * k)
 */

/*
Approach:
We treat (node, edges_used) as a state instead of just (node), because
the cheapest path to a node is not always valid if it exceeds the stop constraint.

We use a modified Dijkstra:
- The priority queue stores (cost, node, edges_used).
- dist[node][edges] stores the minimum cost to reach 'node' using exactly 'edges' edges.
- From (u, s), we relax all outgoing edges only if s+1 is within limit.
- We prune outdated states using: if (current_cost > dist[node][edges]) continue.
- Since the PQ is ordered by cost, the first time we pop 'dst',
 it is the minimum valid cost within k stops.

Why it works:
This expands the graph into n × (k+1) states, ensuring paths with
different stop counts are treated independently.
Thus we correctly handle the stop constraint while preserving Dijkstra's optimality property.

Time Complexity:
Each edge can be relaxed up to (k+1) times.
O((E * k) log (E * k))

Space Complexity:
O(n * k) for the dist table
O(E * k) in worst case for the priority queue
*/

class Solution
{
public:
    int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
    {
        int m = flights.size();
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < m; i++)
        {
            int u = flights[i][0], v = flights[i][1], w = flights[i][2];
            adj[u].push_back({v, w});
        }

        // dist[node][stops used]
        vector<vector<int>> dist(n, vector<int>(k + 2, INT_MAX));

        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;
        pq.push({0, src, 0}); // w u s (weight,node,stop)
        dist[src][0] = 0;

        while (!pq.empty())
        {
            auto [d, u, s] = pq.top();
            pq.pop();
            if (u == dst)
                return d;
            if (s > k)
                continue;

            if (d > dist[u][s])
                continue;

            for (auto [v, w] : adj[u])
            {
                if (s + 1 < k + 2 && dist[u][s] + w < dist[v][s + 1])
                {
                    dist[v][s + 1] = dist[u][s] + w;
                    pq.push({dist[v][s + 1], v, s + 1});
                }
            }
        }
        return -1;
    }
};