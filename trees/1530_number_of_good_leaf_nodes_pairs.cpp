#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1530: Number of Good Leaf Nodes Pairs
    Pattern: DFS
    Time: O(n), Space: O(n)
*/

/*Idea
    1. Solution 1:
    Efficient O(N * d^2) -> N = number of nodes, d = depth of tree
    (Bottom-up DFS on tree):

    For each node, we collect distances to all leaf nodes in its subtree.
    - A leaf returns {1} (distance from itself to parent = 1)

    At each node:
    - Get distances from left and right subtrees
    - Count all pairs (l, r) such that l + r <= d
      → these represent valid leaf pairs whose LCA is this node

    Then return distances to parent:
    - increment all distances by 1 (moving up the tree)
    - discard distances > d (they are useless further up)

    This ensures:
    - each leaf pair is counted exactly once (at their LCA)
    - overall complexity stays efficient (≈ O(N * d^2))

    2. Solution 2:
    Idea (Treat tree as an undirected graph + DFS from each leaf):
    complexity - O(N*L) ; N -> no. of nodes, L -> no. of leaf nodes

    . First DFS:
       - Store parent pointers to allow upward traversal
       - Collect all leaf nodes

    . For each leaf node:
       - Run DFS (can go left, right, and parent)
       - Explore all nodes within distance 'd'
       - Count how many leaf nodes are reachable

    . Optimization:
       - Stop DFS early if distance > d (pruning)
       - Use visited set to avoid revisiting nodes

    . Since each pair is counted twice (A→B and B→A),
       subtract self-count and divide final answer by 2

    Overall:
    - Conceptually simple (multi-source exploration)
    - Works due to small constraints + pruning
*/
/*solution 1 - bottom up */
/*solution 2 - top down */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int ans = 0;
    int d;
    vector<int> dfs(TreeNode *root)
    {
        if (!root)
            return {};
        if (!root->left && !root->right)
            return {1};

        auto left = dfs(root->left);
        auto right = dfs(root->right);

        for (int l : left)
        {
            for (int r : right)
            {
                if (l + r <= d)
                    ans++;
            }
        }

        vector<int> res;
        for (int l : left)
        {
            if (l + 1 <= d)
                res.push_back(l + 1);
        }
        for (int r : right)
        {
            if (r + 1 <= d)
                res.push_back(r + 1);
        }

        return res;
    }
    int countPairs(TreeNode *root, int distance)
    {
        d = distance;
        dfs(root);
        return ans;
    }
};

/*solution 2 - top down - O(N*L) -> L = leaf nodes, N = number of nodes
 */
class Solution
{
public:
    int countPairs(TreeNode *root, int distance)
    {

        unordered_map<TreeNode *, TreeNode *> parent;
        vector<TreeNode *> leafNodes;

        auto dfs1 = [&](auto &&self, TreeNode *root) -> void
        {
            if (root == nullptr)
                return;
            if (root->left == nullptr && root->right == nullptr)
            {
                leafNodes.push_back(root);
            }
            if (root->left)
            {
                parent[root->left] = root;
            }
            if (root->right)
                parent[root->right] = root;
            self(self, root->left);
            self(self, root->right);
        };

        dfs1(dfs1, root);

        int ans = 0;
        int temp_ans = 0;
        unordered_set<TreeNode *> visited;
        auto dfs2 = [&](auto &&self, TreeNode *root, int d) -> void
        {
            if (root == nullptr)
                return;
            if (d > distance)
                return;
            if (visited.count(root))
                return;
            visited.insert(root);
            if (root->left == nullptr && root->right == nullptr && d <= distance)
            {
                temp_ans++;
            }
            if (parent[root])
            {
                self(self, parent[root], d + 1);
            }
            if (root->left)
            {
                self(self, root->left, d + 1);
            }
            if (root->right)
            {
                self(self, root->right, d + 1);
            }
        };

        for (auto node : leafNodes)
        {
            visited.clear();
            temp_ans = 0;
            dfs2(dfs2, node, 0);
            ans += temp_ans - 1;
        }

        return ans / 2;
    }
};