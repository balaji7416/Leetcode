#include <bits/stdc++.h>
using namespace std;

/*
    Problem 40: Combination Sum II
    Pattern: Recursion, Backtracking
*/

/*
    idea:
        1. sort the array
        2. check condition to avoid duplicates
            if(i > idx && arr[i] == arr[i-1]) continue;
        generating unique combinations
*/

class Solution
{
public:
    void combine(int idx, int sum, int target, vector<int> &curr,
                 vector<int> &arr, vector<vector<int>> &ans)
    {
        if (sum > target)
        {
            return;
        }
        if (sum == target)
        {
            ans.push_back(curr);
            return;
        }
        for (int i = idx; i < arr.size(); i++)
        {
            if (i > idx && arr[i] == arr[i - 1])
                continue;
            curr.push_back(arr[i]);
            combine(i + 1, sum + arr[i], target, curr, arr, ans);
            curr.pop_back();
        }
    }
    vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        vector<int> curr;
        sort(candidates.begin(), candidates.end());
        combine(0, 0, target, curr, candidates, ans);
        return ans;
    }
};