#include <bits/stdc++.h>
using namespace std;

/*
    Problem 841: Keys and Rooms
    Pattern: BFS
    Time: O(n + E), Space: O(n)
*/

/*
    idea:
        run bfs/dfs from the node(room) 0
        and mark all the reachable nodes(rooms) as true
        if all the rooms are marked as true then return true
        else return false
*/
class Solution
{
public:
    void bfs(int node, vector<vector<int>> &adj, vector<bool> &visited)
    {
        queue<int> q;
        q.push(node);
        visited[node] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto neighbor : adj[u])
            {
                if (!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }
    bool canVisitAllRooms(vector<vector<int>> &rooms)
    {
        int n = rooms.size();
        vector<bool> visited(n, false);
        bfs(0, rooms, visited);
        for (auto val : visited)
        {
            if (!val)
                return false;
        }
        return true;
    }
};