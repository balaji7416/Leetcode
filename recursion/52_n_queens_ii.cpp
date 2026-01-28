#include <bits/stdc++.h>
using namespace std;

/*
    Problem 52: N-Queens II
    Pattern: Backtracking + Pruning
    Time: O(n!), Space: O(n)
*/

class Solution
{
public:
    void solve(int r, int &ans, vector<bool> &col, vector<bool> &pdiag, vector<bool> &sdiag)
    {
        // base case
        int n = col.size();
        if (r == n)
        {
            ans++;
            return;
        }
        for (int c = 0; c < n; c++)
        {

            // check col,primary diag, secondary diag
            if (col[c])
                continue;
            if (pdiag[r - c + n - 1])
                continue;
            if (sdiag[r + c])
                continue;

            col[c] = pdiag[r - c + n - 1] = sdiag[r + c] = true;
            solve(r + 1, ans, col, pdiag, sdiag);
            col[c] = pdiag[r - c + n - 1] = sdiag[r + c] = false;
        }
    }
    int totalNQueens(int n)
    {
        int ans = 0;

        vector<bool> col(n, false);
        vector<bool> pdiag(2 * n - 1, false);
        vector<bool> sdiag(2 * n - 1, false);

        solve(0, ans, col, pdiag, sdiag);
        return ans;
    }
};