#include <bits/stdc++.h>
using namespace std;

/*
    Problem 97: Interleaving String
    Pattern: dp
    Time: O(m*n), Space: O(m*n)
*/

/*
    f(i,j,i+j) => can s3[i+j:] be formed from s1[i:] and s2[j:]
    base cases:
        if(s3 completes):
            i == s1.size() && j == s2.size()

*/
/*
    i+j = k
    dp[i][j] = can s3[i+j:] be formed from s1[i:] and s2[j:]

*/
class Solution
{
public:
    bool solve(int i, int j, string &s1, string &s2, string &s3, vector<vector<int>> &dp)
    {

        // if s3 completes check whether s1,s2 completed as well
        if (i + j == s3.size())
        {
            return i == s1.size() && j == s2.size();
        }

        // if memorized
        if (dp[i][j] != -1)
            return dp[i][j];

        // try chars from both s1 and s2 to form s3
        bool ans = false;
        if (i < s1.size() && s1[i] == s3[i + j])
        {
            ans |= solve(i + 1, j, s1, s2, s3, dp);
        }

        if (j < s2.size() && s2[j] == s3[i + j])
        {
            ans |= solve(i, j + 1, s1, s2, s3, dp);
        }

        return dp[i][j] = ans;
    }
    bool isInterleave(string s1, string s2, string s3)
    {
        if (s1.size() + s2.size() != s3.size())
            return false;
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solve(0, 0, s1, s2, s3, dp);
    }
};