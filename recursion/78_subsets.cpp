#include <bits/stdc++.h>
using namespace std;

/*
    Problem 78: Subsets
    Pattern: Recursion
    Time: O(2^n), Space: O(n)
*/

class Solution
{
public:
    void generate(int i, vector<int> &curr, vector<int> &nums, vector<vector<int>> &ans)
    {
        if (i == nums.size())
        {
            ans.push_back(curr);
            return;
        }
        // include + recurse
        curr.push_back(nums[i]);
        generate(i + 1, curr, nums, ans);

        // undo + recurse
        curr.pop_back();
        generate(i + 1, curr, nums, ans);
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<vector<int>> ans;
        vector<int> curr;
        generate(0, curr, nums, ans);
        return ans;
    }
};