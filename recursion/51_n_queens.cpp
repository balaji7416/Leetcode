#include <bits/stdc++.h>
using namespace std;

/*
    Naive: is_safe -> O(n);

class Solution
{
public:
    bool is_safe(int r, int c, vector<string> board)
    {
        int n = board.size();
        // check col
        for (int i = 0; i < n; i++)
        {
            if (board[i][c] == 'Q')
                return false;
        }

        // check primary diagonal
        int i = r, j = c;
        while (i >= 0 && j >= 0)
        {
            if (board[i][j] == 'Q')
                return false;
            i--;
            j--;
        }

        // check secondary diagonal
        i = r, j = c;
        while (i >= 0 && j < n)
        {
            if (board[i][j] == 'Q')
                return false;
            i--;
            j++;
        }

        return true;
    }
    void solve(int r, vector<string> &board, vector<vector<string>> &ans)
    {
        // base case
        int n = board.size();
        if (r == n)
        {
            ans.push_back(board);
            return;
        }
        for (int c = 0; c < n; c++)
        {
            if (is_safe(r, c, board))
            {

                board[r][c] = 'Q';
                solve(r + 1, board, ans);
                board[r][c] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));

        solve(0, board, ans);
        return ans;
    }
};

*/

/*
    Optimised: is_safe -> O(1)
    Time: O(n!), Space: O(n)
    idea: backtracking + pruning
        col array -> keeps track of visited cols
        pdiag array -> keeps track of visited primary diagonal
            elements belonging to same primary diagonal have same row-col difference, n-1 is added to make it positive
        sdiag array -> keeps track of visited secondary diagonal
            elements belonging to same secondary diagonal have same row+col sum
*/

class Solution
{
public:
    void solve(int r, vector<string> &board, vector<vector<string>> &ans, vector<bool> &col, vector<bool> &pdiag, vector<bool> &sdiag)
    {
        // base case
        int n = board.size();
        if (r == n)
        {
            ans.push_back(board);
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

            board[r][c] = 'Q';
            solve(r + 1, board, ans, col, pdiag, sdiag);

            col[c] = pdiag[r - c + n - 1] = sdiag[r + c] = false;
            board[r][c] = '.';
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n, string(n, '.'));
        vector<bool> col(n, false);
        vector<bool> pdiag(2 * n - 1, false);
        vector<bool> sdiag(2 * n - 1, false);
        solve(0, board, ans, col, pdiag, sdiag);
        return ans;
    }
};