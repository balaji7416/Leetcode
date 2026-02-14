#include <bits/stdc++.h>
using namespace std;

/*
    Problem 46: Permutations
    Pattern: Backtracking
    Time: O(n!), Space: O(n)
*/

/*
    idea:
        choose a element and recurse
        undo and recurse next element
*/

class Solution
{
public:
    void permute(vector<int> &curr, vector<int> nums, vector<vector<int>> &ans, unordered_set<int> &visited)
    {
        if (curr.size() == nums.size())
        {
            ans.push_back(curr);
            return;
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (visited.count(nums[i]))
                continue;
            visited.insert(nums[i]);

            curr.push_back(nums[i]);
            permute(curr, nums, ans, visited);
            curr.pop_back();
            visited.erase(nums[i]);
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        vector<int> curr;
        vector<vector<int>> ans;
        unordered_set<int> visited;

        permute(curr, nums, ans, visited);
        return ans;
    }
};