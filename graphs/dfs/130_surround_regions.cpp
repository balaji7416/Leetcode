#include <bits/stdc++.h>
using namespace std;

/*
    Problem 130: Surrounded Regions
    Pattern: DFS
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea:
        1. mark the 'O' cells reachable from borders as '#' meaning safe
        2. mark the remaining '0' cells as 'X'
        3. replace all '#' back to 'O'
*/

/*
    it can be optimised with iterative dfs
    or bfs, i will do it later
*/
class Solution
{
public:
    /* iterative dfs
    void dfs(int r, int c, vector<vector<char>> &board)
    {
        int n = board.size();    // rows
        int m = board[0].size(); // cols
        if (board[r][c] != 'O')
            return;
        stack<pair<int, int>> stk;
        stk.push({r, c});
        board[r][c] = '#';
        vector<int> dx = {1, -1, 0, 0};
        vector<int> dy = {0, 0, 1, -1};
        while (!stk.empty())
        {
            auto [currR, currC] = stk.top();
            stk.pop();
            for (int i = 0; i < 4; i++)
            {
                int nr = currR + dx[i];
                int nc = currC + dy[i];

                if (nr >= 0 && nc >= 0 && nr < n && nc < m && board[nr][nc] == 'O')
                {
                    board[nr][nc] = '#';
                    stk.push({nr, nc});
                }
            }
        }
    }
    */
    void dfs(int r, int c, vector<vector<char>> &board)
    {
        int n = board.size();
        int m = board[0].size();
        if (r >= n || r < 0 || c >= m || c < 0)
            return;
        if (board[r][c] != 'O')
            return;
        board[r][c] = '#';
        dfs(r + 1, c, board);
        dfs(r, c + 1, board);
        dfs(r - 1, c, board);
        dfs(r, c - 1, board);
    }
    void solve(vector<vector<char>> &board)
    {
        int n = board.size();
        int m = board[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        /*run dfs on the edge nodes and mark all the nodes reachable from edges
          as safe nodes, i.e., say # for the time being */
        for (int i = 0; i < n; i++)
        {
            dfs(i, 0, board);
            dfs(i, m - 1, board);
        }
        for (int j = 0; j < m; j++)
        {
            dfs(0, j, board);
            dfs(n - 1, j, board);
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == '#')
                {
                    board[i][j] = 'O';
                    continue;
                }
                if (board[i][j] == 'O')
                {
                    board[i][j] = 'X';
                }
            }
        }
    }
};