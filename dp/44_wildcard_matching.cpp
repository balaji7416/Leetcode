#include <bits/stdc++.h>
using namespace std;

/*
    Problem 44: Wildcard Matching
    Pattern: dp
    Time: O(m*n), Space: O(m*n)
*/
/*
    f(i,j) => does string s[i:] match the pattern p[j:]
    base cases:
        if(string becomes empty and pattern doesnn't):
            then all left out char in pattern must be * to act as empty for a
   match if(pattern becomes emtpy and string doesn't): match is not possible
        if(s[i] == p[j]):
            check f(i+1,j+1)

*/

/*
    dp[i][j] = does string s[i:] match the pattern p[j:]
*/

class Solution
{
public:
    bool solve(int i, int j, string &s, string &p, vector<vector<int>> &dp)
    {
        // if string becomes emtpy while pattern doesn't
        if (i == s.size())
        {
            for (int k = j; k < p.size(); k++)
            {
                if (p[k] != '*')
                    return false;
            }
            return true;
        }

        // if pattern becomes empty while string doesn't
        if (j == p.size())
        {
            return false;
        }

        // if already memorized
        if (dp[i][j] != -1)
            return dp[i][j];

        // if chas match
        if (s[i] == p[j] || p[j] == '?')
        {
            return dp[i][j] = solve(i + 1, j + 1, s, p, dp);
        }

        // if char's doens't match but p[j] == '*'
        if (p[j] == '*')
        {
            return dp[i][j] = solve(i + 1, j, s, p, dp)     // take *
                              || solve(i, j + 1, s, p, dp); // not take *
        }

        // if doesn't match and p[j] != '*'
        return false;
    }
    bool isMatch(string s, string p)
    {
        int n = s.size();
        int m = p.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        // -1 = unknown, 0 = false, 1 = true

        return solve(0, 0, s, p, dp);
    }
};