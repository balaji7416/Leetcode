#include <bits/stdc++.h>
using namespace std;

/*
    Problem 718: Maximum Length of Repeated Subarray
    Pattern: dp
    Time: O(m*n), Space: O(m*n)
*/

/*
    Brute force solution:
        Time -> O(n^3) space -> O(1)

class Solution
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        int m = nums2.size();
        int max_len = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int r = i, s = j;
                int len = 0;
                while (r < n && s < m && nums1[r] == nums2[s])
                {
                    len++;
                    r++;
                    s++;
                }
                max_len = max(max_len, len);
            }
        }
        return max_len;
    }
};

*/

/*  dp - bottom up approach
    dp[i][j] = len of longest common subarray in nums1[:i] and nums2[:j] that ends
    at nums1[i-1] and nums2[j-1];

    eg. nums1 = [1,2,5,4,7] nums2 = [1,2,5,3,4,7]
        dp[5][6] = 2 i.e., len of [4,7]


class Solution
{
public:
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        int m = nums2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        int ans = 0;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (nums1[i - 1] == nums2[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    ans = max(ans, dp[i][j]);
                }
            }
        }
        return ans;
    }
};

*/

/*  dp - top down approach */
/*
    solve(i, j) => length of the longest common subarray ending exactly at i and j
    dp[i][j] => length of the longest common subarray ending exactly at i and j

    the core concept of this question is definition of dp or recursive definition
    f(i,j) => len of longest common subarray ending exactly at i and j. #note ending at exactly i,j
*/

class Solution
{
public:
    int solve(int i, int j, vector<int> &nums1, vector<int> &nums2, vector<vector<int>> &dp)
    {
        if (i < 0 || j < 0)
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];
        if (nums1[i] == nums2[j])
        {
            return dp[i][j] = 1 + solve(i - 1, j - 1, nums1, nums2, dp);
        }
        return dp[i][j] = 0;
    }
    int findLength(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums1.size();
        int m = nums2.size();

        int ans = 0;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int len = solve(i, j, nums1, nums2, dp);
                ans = max(ans, len);
            }
        }
        return ans;
    }
};