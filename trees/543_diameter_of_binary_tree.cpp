#include <bits/stdc++.h>
using namespace std;

/*
    Problem 543: Diameter of Binary Tree
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
    int diameterOfBinaryTree(TreeNode *root)
    {
        int dia = 0;
        auto dfs = [&](auto &&self, TreeNode *u)
        {
            if (!u)
                return 0;
            int left = self(self, u->left);
            int right = self(self, u->right);

            dia = max(dia, left + right);
            return 1 + max(left, right);
        };
        dfs(dfs, root);
        return dia;
    }
};