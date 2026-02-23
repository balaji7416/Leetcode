#include <bits/stdc++.h>
using namespace std;

/*
    Problem 743: Network Delay Time
    Pattern: BFS
    Time: O(V+E)log(V), Space:
*/

/*
    idea:
        run dijkstra from src
        if the destination is reachable
        from src, return the max time among all nodes
        else return -1
*/

class Solution
{
public:
    const int inf = 1e8;
    int networkDelayTime(vector<vector<int>> &times, int n, int k)
    {
        vector<vector<pair<int, int>>> adj(n);
        for (int i = 0; i < times.size(); i++)
        {
            int u = times[i][0], v = times[i][1], w = times[i][2];
            u--;
            v--; // to make zero indexing
            adj[u].push_back({v, w});
        }

        vector<int> dist(n, inf);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        k--; // convert to zero indexing
        pq.push({0, k});
        dist[k] = 0;
        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
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

        int ans = INT_MIN;
        for (int i = 0; i < n; i++)
        {
            if (dist[i] == inf)
                return -1;
            ans = max(ans, dist[i]);
        }
        return ans;
    }
};