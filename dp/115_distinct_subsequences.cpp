#include <bits/stdc++.h>
using namespace std;

/*
    Problem 115: Distinct Subsequences
    Pattern: dp
    Time: O(m*n), Space: O(m*n) + stack space (O(m+n))
*/

/*
    f(i,j) => no.of disinct subsequences in s[i:] which match target string
   t[j:] base cases: if(target ends i.e., j == t.size()): return 1; (consider
   one perfect match) if(string ends before target i.e.,  i == s.size()): return
   0; (can't find subsequence in s anymore)
*/
/*
    dp[i][j] = no.of distinct subsequences in s[i:] which match target string
   t[j:]
*/
class Solution
{
public:
    int solve(int i, int j, string &s, string &t, vector<vector<int>> &dp)
    {

        // if target ends
        if (j == t.size())
            return 1;

        // if string ends while target doesn't
        if (i == s.size())
            return 0;

        // if memorized
        if (dp[i][j] != -1)
            return dp[i][j];

        return dp[i][j] = solve(i + 1, j, s, t, dp) // skip the curr char in s, i.e, s[i]
                          + (s[i] == t[j]
                                 ? solve(i + 1, j + 1, s, t, dp)
                                 : 0); // consider s[i] and check in f(i+1,j+1)
    }
    int numDistinct(string s, string t)
    {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, s, t, dp);
    }
};