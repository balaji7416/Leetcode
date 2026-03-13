#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1443: Minimum Time to Collect All Apples in a Tree
    Pattern: BFS
    Time: O(n), Space: O(n)
*/
/*
IDEA:
Do a postorder DFS on the tree. For every node, determine:
1) whether its subtree contains an apple
2) the total traversal cost needed to collect those apples.

If a child subtree contains an apple, we must traverse that edge
twice (go to the child and come back), so we add:

        childCost + 2

to the current node's cost.

DFS returns:
    {totalCostInSubtree, subtreeHasApple}

The root does not need special handling because we only add +2
when returning from children that contain apples.

Time Complexity: O(N)
Space Complexity: O(N)
*/

class Solution
{
public:
    vector<bool> apple;
    vector<vector<int>> adj;
    pair<int, bool> dfs(int u, int p)
    {
        bool subTreeHasApple = apple[u];
        int totalCost = 0;
        for (int v : adj[u])
        {
            if (v == p)
                continue;
            auto [childCost, has] = dfs(v, u);
            if (has)
            {
                totalCost += childCost + 2;
                subTreeHasApple = true;
            }
        }
        return {totalCost, subTreeHasApple};
    }
    int minTime(int n, vector<vector<int>> &edges, vector<bool> &hasApple)
    {
        apple = hasApple;
        adj.resize(n);
        for (auto e : edges)
        {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        return dfs(0, -1).first;
    }
};