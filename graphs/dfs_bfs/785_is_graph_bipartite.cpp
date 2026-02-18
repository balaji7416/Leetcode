#include <bits/stdc++.h>
using namespace std;

/*
    Problem 785: Is Graph Bipartite?
    Pattern: DFS
    Time: O(E+V), Space: O(V)
*/

/*
    idea:
        run dfs from every uncolored node and check
        if the graph is bipartite
*/

class Solution
{
public:
    bool dfs(int node, vector<int> &color, vector<vector<int>> &graph)
    {

        for (auto neighbor : graph[node])
        {

            // if neighbor not color
            if (color[neighbor] == -1)
            {
                color[neighbor] = 1 - color[node];
                if (!dfs(neighbor, color, graph))
                {
                    return false;
                }
            }
            // if neighbor already colored
            else
            {
                if (color[node] == color[neighbor])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool dfs_iterative(int node, vector<int> &color, vector<vector<int>> &graph)
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
    bool bfs(int node, vector<int> &color, vector<vector<int>> &adj)
    {
        queue<int> q;
        q.push(node);
        while (!q.empty())
        {
            auto x = q.front();
            q.pop();
            for (auto neighbor : adj[x])
            {
                if (color[neighbor] == -1)
                {
                    color[neighbor] = 1 - color[x];
                    q.push(neighbor);
                }
                else if (color[neighbor] == color[x])
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool isBipartite(vector<vector<int>> &graph)
    {
        int n = graph.size();

        // -1 -> uncolored, 0 -> color A, 1 -> color B
        vector<int> color(n, -1);

        // check for all connected components
        for (int i = 0; i < n; i++)
        {
            if (color[i] == -1)
            {
                color[i] = 0;
                if (!dfs(i, color, graph))
                {
                    return false;
                }
            }
        }

        return true;
    }
};