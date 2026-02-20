#include <bits/stdc++.h>
using namespace std;

/*
    Problem 802: Find Eventual Safe States
    Pattern: DFS
    Time: O(V+E), Space: O(V+E)
*/

/*sol 1 with kahn's algo + reverse graph technique (sorting dominates the time)*/
class Solution
{
public:
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = graph.size();

        // calc out Degree of nodes
        vector<int> outDegree(n, 0);
        for (int i = 0; i < n; i++)
        {
            outDegree[i] = graph[i].size();
        }

        // reverse the edges to do topo sort
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < graph[i].size(); j++)
            {
                adj[graph[i][j]].push_back(i);
            }
        }

        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            if (outDegree[i] == 0)
            {
                q.push(i);
            }
        }
        vector<int> ans;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            ans.push_back(u);

            for (auto v : adj[u])
            {
                outDegree[v]--;
                if (outDegree[v] == 0)
                {
                    q.push(v);
                }
            }
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

/*sol 2 with dfs state marking
    this one is more feasible here since it's naturally
    collects sorted order of nodes
    it works since dfs returns if there's a cycle rejecting those nodes as unsafe
    and only marks if a node reaches a terminal as safe
    ensuring safe nodes are marked as true
*/
class Solution
{
public:
    bool dfs(int node, vector<vector<int>> &adj, vector<bool> &inRec, vector<bool> &visited, vector<bool> &safe)
    {
        visited[node] = true;
        inRec[node] = true;
        for (auto neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                if (!dfs(neighbor, adj, inRec, visited, safe))
                {
                    return false;
                }
            }
            else if (inRec[neighbor])
            {
                return false;
            }
        }
        safe[node] = true;
        inRec[node] = false;
        return true;
    }
    vector<int> eventualSafeNodes(vector<vector<int>> &graph)
    {
        int n = graph.size();
        vector<bool> visited(n, false);
        vector<bool> inRec(n, false);
        vector<bool> safe(n, false);

        for (int i = 0; i < n; i++)
        {
            if (!visited[i])
            {
                dfs(i, graph, inRec, visited, safe);
            }
        }
        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            if (safe[i])
                ans.push_back(i);
        }
        return ans;
    }
};