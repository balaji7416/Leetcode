#include <bits/stdc++.h>
using namespace std;

/*
    Problem 39: Combination Sum
    Pattern: Recursion, Backtracking
    Time: O(n^T), Space: O(T+output) T->target, output->no.of valid combinations
*/

/*
    idea:
    1. choose a idx repeatedly and recurse
    2. undo and recurse next idx

*/

class Solution
{
public:
    void generate(int i, int &sum, int target, vector<int> &curr,
                  vector<int> &candidates, vector<vector<int>> &ans)
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
        if (i == candidates.size())
        {
            if (sum == target)
            {
                ans.push_back(curr);
            }
            return;
        }

        // choose + recurse
        curr.push_back(candidates[i]);
        sum += candidates[i];
        generate(i, sum, target, curr, candidates, ans);

        curr.pop_back();
        sum -= candidates[i];
        generate(i + 1, sum, target, curr, candidates, ans);
    }
    vector<vector<int>> combinationSum(vector<int> &candidates, int target)
    {
        vector<vector<int>> ans;
        vector<int> curr;
        int sum = 0;
        generate(0, sum, target, curr, candidates, ans);
        return ans;
    }
};