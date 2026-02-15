#include <bits/stdc++.h>
using namespace std;

/*
    Problem 207: Course Schedule
    Pattern: DFS
    Time: O(V+E), Space: O(V+E)
*/

/*
    idea:
        the idea is to check whether it's possible to
        find a topological sort of the graph
        and it's only possible if the grapsh has no cycles
        make adj list out of given edges in prerequisites
        run dfs on the graph
        if the graph is cyclic, return false
        else return true
*/

/*
    the question is asking is it possible to find a toposort order for the given graph
    and it's only possible if the directed graph has no cycles
*/

class Solution
{
public:
    bool dfs(int node, vector<vector<int>> &adj, vector<bool> &visited,
             vector<bool> &inRec)
    {
        visited[node] = true;
        inRec[node] = true;
        for (auto neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                if (dfs(neighbor, adj, visited, inRec))
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
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
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
        for (int i = 0; i < numCourses; i++)
        {
            if (!visited[i])
            {
                if (dfs(i, adj, visited, inRec))
                {
                    return false;
                }
            }
        }
        return true;
    }
};