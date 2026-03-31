#include <bits/stdc++.h>
using namespace std;

/*
    Problem 45: Jump Game II
    Pattern: DP / greedy
    Time: O(n^2) with dp, O(n) with greedy
    Space: O(n)
*/

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> dp(n, -1);
        auto dfs = [&](auto &&self, int i) -> int
        {
            if (i >= n - 1)
                return 0;
            int ans = 1e6;
            if (dp[i] != -1)
                return dp[i];
            for (int _ = 1; _ <= nums[i]; _++)
            {
                ans = min(ans, self(self, i + _));
            }
            return dp[i] = 1 + ans;
        };
        return dfs(dfs, 0);
    }
};