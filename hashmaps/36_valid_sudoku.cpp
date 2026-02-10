#include <bits/stdc++.h>
using namespace std;

/*
    Problem 36: Valid Sudoku
    Pattern: Hashmap
    Time: O(n^2), Space: O(n)
*/
/*
Sudoku = constraint validation, not solving.

Invariant:
- A digit may appear only once in any row, column, or 3x3 box.

Method:
- Use sets to remember digits seen in each row, column, and box.
- For each non-empty cell:
  - Compute box index: (r/3)*3 + (c/3)
  - If digit already exists in row/col/box → invalid
  - Else, record digit in all three

Idea:
- Sets act as memory of past decisions
- Any repeat = history violation
- O(81), no backtracking
*/

class Solution
{
public:
    bool isValid(vector<vector<char>> &board)
    {
        vector<unordered_set<char>> row(9);
        vector<unordered_set<char>> col(9);
        vector<unordered_set<char>> sq(9);

        for (int r = 0; r < 9; r++)
        {
            for (int c = 0; c < 9; c++)
            {
                if (board[r][c] == '.')
                    continue;
                char el = board[r][c];
                int sq_idx = r / 3 * 3 + c / 3;
                if (row[r].count(el))
                {
                    return false;
                }
                if (col[c].count(el))
                {
                    return false;
                }
                if (sq[sq_idx].count(el))
                {
                    return false;
                }
                row[r].insert(el);
                col[c].insert(el);
                sq[sq_idx].insert(el);
            }
        }
        return true;
    }
    bool isValidSudoku(vector<vector<char>> &board)
    {
        return isValid(board);
    }
};