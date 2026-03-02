#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1514: Path with Maximum Probability
    Pattern: BFS
    Time: O((V+E)log(V)) or O(Elog(V)), Space: O(V+E)
*/

/*
    Problem: Path with Maximum Probability

    Idea:
    Treat graph edges as probabilities.
    We need to find a path that maximizes the product of edge probabilities.

    Use a modified Dijkstra:
    - Maintain prob[i] = maximum probability to reach node i.
    - Use a max-heap (default priority_queue).
    - Relax edges using multiplication instead of addition:
        if prob[u] * weight > prob[v], update.

    the only change needed is transition from standard relaxation
    i.e., minimize dist[u] + w to maximize prob[u] * w

    Time Complexity:  O(E log V)
    Space Complexity: O(E + V)
*/

class Solution
{
public:
    double maxProbability(int n, vector<vector<int>> &edges, vector<double> &succProb, int start_node, int end_node)
    {
        vector<vector<pair<int, double>>> adj(n);
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0];
            int v = edges[i][1];
            double w = succProb[i];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        vector<double> prob(n, 0);
        priority_queue<pair<double, int>, vector<pair<double, int>>> pq;
        pq.push({1, start_node});
        prob[start_node] = 1;

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (u == end_node)
            {
                return d;
            }
            if (d < prob[u])
                continue;
            for (auto [v, w] : adj[u])
            {
                if (prob[u] * w > prob[v])
                {
                    prob[v] = prob[u] * w;
                    pq.push({prob[v], v});
                }
            }
        }
        return 0;
    }
};