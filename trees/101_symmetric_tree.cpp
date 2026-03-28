#include <bits/stdc++.h>
using namespace std;

/*
    Problem 101: Symmetric Tree
    Pattern: DFS
    Time: O(n), Space: O(n)
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
    bool isSymmetric(TreeNode *root)
    {
        if (!root)
            return true;
        auto dfs = [&](auto &&self, TreeNode *r, TreeNode *p)
        {
            if (!r && !p)
                return true;
            if (!r || !p)
                return false;
            if (r->val != p->val)
                return false;

            return self(self, r->left, p->right) &&
                   self(self, r->right, p->left);
        };
        return dfs(dfs, root->left, root->right);
    }
};