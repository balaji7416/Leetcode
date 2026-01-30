#include <bits/stdc++.h>
using namespace std;

/*
    Problem 516: Longest Palindromic Subsequence
    Pattern: dp + recursion
    Time: O(m*n), Space: O(m*n) + stack space
*/

/*
    idea:
        dp[i][j] = length of lps of s[i..j]
        lps = longest palindromic subsequence
        i used top to bottom dp
*/

class Solution
{
public:
    int solve(int i, int j, string &s, vector<vector<int>> &dp)
    {
        if (i > j)
            return 0;
        if (i == j)
            return 1;

        // if memorized
        if (dp[i][j] != -1)
            return dp[i][j];

        if (s[i] == s[j])
            return dp[i][j] = 2 + solve(i + 1, j - 1, s, dp);
        return dp[i][j] = max(solve(i + 1, j, s, dp), solve(i, j - 1, s, dp));
    }
    int longestPalindromeSubseq(string s)
    {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solve(0, n - 1, s, dp);
    }
};