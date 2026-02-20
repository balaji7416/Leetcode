#include <bits/stdc++.h>
using namespace std;

/*
    Problem 310: Minimum Height Trees
    Pattern: BFS + (topological sort style)
    Time: O(n), Space: O(n)
*/

/*
Key Idea:
The roots of Minimum Height Trees are the center(s) of the tree.
and a tree can have at most 2 centers.
Observation:
- Leaves (degree = 1) can never be optimal roots because they are farthest from some node.
- If we repeatedly remove all current leaves layer by layer,
  the tree shrinks inward toward its center.
- The last remaining 1 or 2 nodes are the tree centers.
- A tree can have at most 2 centers.

Algorithm:
1. Build adjacency list and compute degree (indegree) of each node.
2. Push all nodes with degree <= 1 (initial leaves) into a queue.
3. Perform BFS layer by layer:
   - For each layer, remove all current leaves.
   - Decrease the degree of their neighbors.
   - If a neighbor’s degree becomes 1, push it into the queue.
4. The last processed layer (1 or 2 nodes) is the answer.

Time Complexity: O(n)
Each node and edge is processed once.

Space Complexity: O(n)
*/

class Solution
{
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>> &edges)
    {
        vector<vector<int>> adj(n);
        if (edges.empty())
        {
            return {0};
        }
        for (int i = 0; i < edges.size(); i++)
        {
            int u = edges[i][0], v = edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<int> degree(n, 0);
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            degree[i] = adj[i].size();
            if (degree[i] == 1)
                q.push(i);
        }

        // you can also use the fact that a tree can have atmost 2 centers
        vector<int> ans;
        while (!q.empty())
        {
            int size = q.size();
            ans.clear();
            while (size--)
            {
                int u = q.front();
                q.pop();
                ans.push_back(u);
                for (auto v : adj[u])
                {
                    degree[v]--;
                    if (degree[v] == 1)
                    {
                        q.push(v);
                    }
                }
            }
        }

        return ans;
    }
};