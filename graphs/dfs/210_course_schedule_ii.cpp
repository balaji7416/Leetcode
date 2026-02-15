#include <bits/stdc++.h>
using namespace std;

/*
    Problem 210: Course Schedule II
    Pattern: DFS
    Time: O(V+E), Space: O(V+E)
*/

/*
    Approach:
    - Build a directed graph from prerequisites.
      (v -> u means: take v before u)
    - Perform DFS with recursion stack to detect cycles.
    - If a cycle exists, topological ordering is impossible → return {}.
    - Otherwise, push nodes to a stack after exploring all neighbors.
      (Postorder DFS gives topological sort)
    - Pop stack to get valid course order.
*/

class Solution
{
public:
    bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited, vector<bool> &inRec, stack<int> &stk)
    {
        visited[node] = true;
        inRec[node] = true;

        for (auto neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                if (dfs(neighbor, adj, visited, inRec, stk))
                {
                    return true;
                }
            }
            else if (inRec[neighbor])
            {
                return true;
            }
        }
        // back track
        inRec[node] = false;

        // push to stk
        stk.push(node);

        return false;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        vector<bool> visited(numCourses, false);
        vector<bool> inRec(numCourses, false);
        vector<vector<int>> adj(numCourses);
        for (auto vec : prerequisites)
        {
            int u = vec[0];
            int v = vec[1];
            adj[v].push_back(u);
        }
        stack<int> stk;
        for (int i = 0; i < numCourses; i++)
        {
            if (!visited[i])
            {
                if (dfs(i, adj, visited, inRec, stk))
                {
                    return {};
                }
            }
        }
        vector<int> ans;
        while (!stk.empty())
        {
            ans.push_back(stk.top());
            stk.pop();
        }
        return ans;
    }
};