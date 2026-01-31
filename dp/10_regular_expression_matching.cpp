#include <bits/stdc++.h>
using namespace std;

/*
    Problem 10: Regular Expression Matching
    Pattern: dp
    Time: O(m*n), Space: O(m*n) + stack space(O(m+n))
*/

/*
    f(i,j) => is string s[i:] matches with pattern p[j:] according to the given conditions
        . => matches any single char
        * => matches one or more of the preceding char
    base cases:
        if(pattern becomes emtpy):
            string should be empty to be a perfect match

*/

/*
    dp[i][j] = is string s[i:] matches with pattern p[j:]
    dp[n][m] = is string emtpy string matches with empty pattern
    dp[n][] is handled by recursion
*/

class Solution
{
public:
    bool solve(int i, int j, string &s, string &p, vector<vector<int>> &dp)
    {
        // pattern becomes empty
        if (j == p.size())
        {
            return i == s.size();
        }

        if (dp[i][j] != -1)
            return dp[i][j];

        bool firstMatch = i < s.size() && (s[i] == p[j] || p[j] == '.');
        if (j + 1 < p.size() && p[j + 1] == '*')
        {
            return dp[i][j] = solve(i, j + 2, s, p, dp) ||               // skip the *
                              (firstMatch && solve(i + 1, j, s, p, dp)); // include the *
        }

        // s[i] == p[j] and p[j+1] != '*'
        if (firstMatch)
        {
            return dp[i][j] = solve(i + 1, j + 1, s, p, dp);
        }

        // s[i] != s[j]
        return dp[i][j] = false;
    }
    bool isMatch(string s, string p)
    {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solve(0, 0, s, p, dp);
    }
};