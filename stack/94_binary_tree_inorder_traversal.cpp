#include <bits/stdc++.h>
using namespace std;

/*
    Problem 94: Binary Tree Inorder Traversal
    Pattern: recursive stack
    Time: O(n), Space: O(n)
*/

/*
    idea: implicit stack (recursion)
*/

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
    void inorder(TreeNode *root, vector<int> &result)
    {
        if (root == nullptr)
            return;

        inorder(root->left, result);
        result.push_back(root->val);
        inorder(root->right, result);
    }
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        inorder(root, result);
        return result;
    }
};