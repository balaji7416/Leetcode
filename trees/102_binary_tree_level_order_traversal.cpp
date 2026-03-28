#include <bits/stdc++.h>
using namespace std;

/*
    Problem 102: Binary Tree Level Order Traversal
    Pattern: BFS
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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        if (!root)
            return {};

        vector<vector<int>> ans;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            vector<int> temp;
            int sz = q.size();
            while (sz--)
            {
                auto u = q.front();
                q.pop();
                temp.push_back(u->val);
                if (u->left)
                    q.push(u->left);
                if (u->right)
                    q.push(u->right);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};