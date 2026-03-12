#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1519: Number of Nodes in the Sub-Tree With the Same Label
    Pattern: DFS
    Time: O(n), Space: O(n)
*/

/* Idea:
Tree DP with frequency merging.

For each node u, DFS returns a frequency array cnt[26] where
cnt[c] = number of nodes with label 'c' in the subtree of u.

During DFS:
1. Recursively compute frequency arrays for all children.
2. Merge children's frequencies into the current node's array.
3. Add the current node's label to the count.
4. The answer for u is the frequency of its own label in its subtree.

Time: O(26 * N) ≈ O(N)
*/

class Solution
{
    vector<vector<int>> adj;
    string label;
    vector<int> ans;

public:
    vector<int> dfs(int u, int p)
    {
        vector<int> cnt(26, 0);
        for (int v : adj[u])
        {

            if (v == p)
                continue;
            auto child = dfs(v, u);

            for (int i = 0; i < 26; i++)
            {
                cnt[i] += child[i];
            }
        }
        cnt[label[u] - 'a']++;
        ans[u] = cnt[label[u] - 'a'];
        return cnt;
    }
    vector<int> countSubTrees(int n, vector<vector<int>> &edges, string labels)
    {
        adj.resize(n);
        ans.resize(n, 0);
        label = labels;
        for (auto e : edges)
        {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, -1);
        return ans;
    }
};