#include <bits/stdc++.h>
using namespace std;

/*
    Problem 98: Validate Binary Search Tree
    Pattern: DFS
    Time: O(n), Space: O(n)
*/

/* IDEA:
    Validate BST using DFS + range propagation.

    Idea:
    Each node must lie within a valid range (minm, maxm) inherited
    from its ancestors.

    - For left child → range becomes (minm, node->val)
    - For right child → range becomes (node->val, maxm)

    If any node violates: node->val <= minm OR node->val >= maxm → invalid BST.

    We propagate constraints down the tree instead of checking only parent,
    ensuring global BST correctness.

    Use long long bounds to safely hand

*/
// Definition for a binary tree node.
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
    bool isValidBST(TreeNode *root)
    {
        long long inf = 1e18;
        auto dfs = [&](auto &&self, TreeNode *r, long long minm, long long maxm)
        {
            if (!r)
                return true;
            if (r->val <= minm || r->val >= maxm)
                return false;

            return self(self, r->left, minm, r->val) &&
                   self(self, r->right, r->val, maxm);
        };
        return dfs(dfs, root, -inf, inf);
    }
};