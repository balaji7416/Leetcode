#include <bits/stdc++.h>
using namespace std;

/*
    Problem 886: Possible Bipartition
    Pattern: DFS
    Time: O(E+V), Space: O(V)
*/

/*
    idea:
        we can achieve the possible split given
        only if the graph is bipartite

        1. convert the edge list given into adj list
        2. run dfs on the graph
        3. if the graph is bipartite, return true
        4. else return false

        color[i] = -1 -> uncolored, 0 -> color A, 1 -> color B
        run dfs, if the neighbor is uncolored then color it with
        1 - color[u] and run dfs on the neighbor
        if the neighbor is colored with the same color then return false
*/

class Solution
{
public:
    bool dfs(int node, vector<int> &color, vector<vector<int>> &graph)
    {
        stack<int> stk;
        stk.push(node);
        while (!stk.empty())
        {
            int u = stk.top();
            stk.pop();

            for (auto neighbor : graph[u])
            {
                if (color[neighbor] == -1)
                {
                    color[neighbor] = 1 - color[u];
                    stk.push(neighbor);
                }
                else
                {
                    if (color[neighbor] == color[u])
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    bool possibleBipartition(int n, vector<vector<int>> &dislikes)
    {
        vector<int> color(n, -1);
        vector<vector<int>> adj(n);
        for (auto const &vec : dislikes)
        {
            adj[vec[0] - 1].push_back(vec[1] - 1);
            adj[vec[1] - 1].push_back(vec[0] - 1);
        }
        for (int i = 0; i < n; i++)
        {
            if (color[i] == -1)
            {
                color[i] = 0;
                if (!dfs(i, color, adj))
                {
                    return false;
                }
            }
        }
        return true;
    }
};