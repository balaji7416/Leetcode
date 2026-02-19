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

/* with kahn's algorithm using bfs*/
class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        int n = numCourses;
        vector<vector<int>> adj(n);

        // build the adj list
        for (int i = 0; i < prerequisites.size(); i++)
        {
            int u = prerequisites[i][0];
            int v = prerequisites[i][1];
            adj[v].push_back(u);
        }

        // calc inDegres of all nodes
        vector<int> inDegree(n, 0);
        for (int u = 0; u < n; u++)
        {
            for (auto v : adj[u])
            {
                inDegree[v]++;
            }
        }

        // push nodes with inDegree 0, meaning no dependencies
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (inDegree[i] == 0)
            {
                q.push(i);
            }
        }

        vector<int> topo;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            // decrease the inDegree for all of it's neighbors
            for (auto v : adj[u])
            {
                inDegree[v]--;
                // if inDegree of any neighbor becomes 0 push it into q
                if (inDegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }

        // if toposize is not equal to no.of nodes then cycle exists
        if (topo.size() < n)
        {
            return {};
        }
        return topo;
    }
};

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