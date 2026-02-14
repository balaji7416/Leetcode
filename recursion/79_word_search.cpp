#include <bits/stdc++.h>
using namespace std;
/*
    This is both DFS/Recursion+backtracking
    so i kept in in recursion folder
*/

/*
    Problem 79: Word Search
    Pattern: DFS + Backtracking
    Time Complexity: O(n * m * 4^L)
        - n * m → possible starting cells
        - 4^L → branching factor for each character in the word (L = word length)

    Space Complexity: O(L + n * m)
        - O(L) → recursion stack depth (path length)
        - O(n * m) → visited matrix
*/

/*
    Word Search (LC 79)

    Idea:
    - Treat this as a path-construction problem, not a flood-fill.
    - For every cell matching word[0], start DFS from there.
    - DFS state = (row, col, index in word).

    DFS Logic:
    - If idx == word.length → entire word matched → return true.
    - If out of bounds OR already visited → return false.
    - Mark current cell as visited.
    - Explore 4 directions:
        - Only move to neighbor if:
            1) In bounds
            2) Not visited
            3) board[nr][nc] == word[idx]
        - Recurse with idx + 1.
    - If none succeed → backtrack (unmark visited) and return false.

    Key Insight:
    - We are validating a single path step-by-step.
    - No wandering on mismatch.
    - Each recursive call must strictly progress in the word.
*/

class Solution
{
public:
    bool dfs(int r, int c, int idx, string &word, vector<vector<char>> &board,
             vector<vector<bool>> &visited)
    {
        if (idx >= word.size())
            return true;
        int n = board.size();
        int m = board[0].size();
        if (r < 0 || c < 0 || r >= n || c >= m)
        {
            return false;
        }
        if (visited[r][c])
            return false;
        visited[r][c] = true;

        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dx[i];
            int nc = c + dy[i];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m && !visited[nr][nc] && board[nr][nc] == word[idx])
            {
                if (dfs(nr, nc, idx + 1, word, board, visited))
                {
                    return true;
                }
            }
        }
        visited[r][c] = false;
        return false;
    }
    bool exist(vector<vector<char>> &board, string word)
    {
        int n = board.size();
        int m = board[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (board[i][j] == word[0])
                {
                    if (dfs(i, j, 1, word, board, visited))
                    {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};
