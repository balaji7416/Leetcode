#include <bits/stdc++.h>
using namespace std;

/*
    Problem 132: Palindrome Partitioning II
    Pattern: dp
    Time: O(n^2), Space: O(n^2) + stack space O(n)
*/

/*
    f(i) = min cuts needed to make in s[i:] to make all it's substrs as
   palindromes base case: if(s[i:] is already a palindrome) return 0

    dp[i] = min cuts needed to make s[i:] to make all it's substrs as
   palindromes
*/

/*
    This is intutive but, O(n^3) approach to fill isPal table, a better approach
O(n^2) is   advised

bool is_palindrome(int l, int r, string& s) {
    if (l >= r)
        return true;
    if (s[l] != s[r])
        return false;
    return is_palindrome(l + 1, r - 1, s);
}

for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
        isPal[i][j] = is_palindrome(i, j, s);
    }
}
*/

class Solution
{
public:
    int solve(int i, string &s, vector<vector<bool>> &isPal, vector<int> &dp)
    {
        if (isPal[i][s.size() - 1])
        {
            return 0;
        }
        if (dp[i] != -1)
            return dp[i];
        int min_cuts = INT_MAX;
        for (int j = i; j < s.size(); j++)
        {
            if (isPal[i][j])
                min_cuts = min(min_cuts, 1 + solve(j + 1, s, isPal, dp));
        }
        return dp[i] = min_cuts;
    }

    int minCut(string s)
    {
        int n = s.size();

        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        // tells whether a substr of s is a palindrome or not in O(1)

        // O(n^2) approach to fill the isPal table
        for (int len = 1; len <= n; len++)
        {
            for (int i = 0; i + len - 1 < n; i++)
            {
                int j = i + len - 1;
                if (s[i] == s[j])
                {
                    if (len <= 2)
                    {
                        isPal[i][j] = true;
                    }
                    else
                    {
                        isPal[i][j] = isPal[i + 1][j - 1];
                    }
                }
            }
        }

        vector<int> dp(n, -1);
        return solve(0, s, isPal, dp);
    }
};
