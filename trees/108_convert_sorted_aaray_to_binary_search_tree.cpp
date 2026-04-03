#include <bits/stdc++.h>
using namespace std;

/*
    Problem 108: Convert Sorted Array to Binary Search Tree
    Pattern: DFS
    Time: O(n), Space: O(n)
*/

// Definition for a binary tree node
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
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        int n = nums.size();
        auto dfs = [&](auto &&self, int l, int r) -> TreeNode *
        {
            if (l > r)
                return nullptr;
            int m = l + (r - l) / 2;
            TreeNode *root = new TreeNode(nums[m]);
            root->left = self(self, l, m - 1);
            root->right = self(self, m + 1, r);
            return root;
        };
        return dfs(dfs, 0, n - 1);
    }
};