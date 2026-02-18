#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1926: Nearest Exit from Entrance in Maze
    Pattern: BFS
    Time: O(m*n), Space: O(m*n)
*/

/**
 * Logic: BFS from entrance to find shortest path to any exit
 * - Exit is an empty cell on boundary that is NOT the entrance
 * - BFS ensures first exit found is nearest (shortest path)
 * - Track visited cells to avoid revisiting and cycles
 * - Process level by level using queue size to count moves
 */

class Solution
{
public:
    int nearestExit(vector<vector<char>> &maze, vector<int> &entrance)
    {
        int n = maze.size();
        int m = maze[0].size();
        queue<pair<int, int>> q;
        vector<vector<int>> visited(n, vector<int>(m, false));
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};

        q.push({entrance[0], entrance[1]});
        visited[entrance[0]][entrance[1]] = true;

        int moves = 0;
        while (!q.empty())
        {
            int size = q.size();
            while (size--)
            {
                auto [x, y] = q.front();
                q.pop();
                if ((x == n - 1 || x == 0 || y == 0 || y == m - 1) && maze[x][y] == '.' &&
                    !(x == entrance[0] && y == entrance[1]))
                {
                    return moves;
                }
                for (int i = 0; i < 4; i++)
                {
                    int nr = x + dx[i];
                    int nc = y + dy[i];
                    if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                        maze[nr][nc] != '+' && !visited[nr][nc])
                    {
                        visited[nr][nc] = true;
                        q.push({nr, nc});
                    }
                }
            }
            moves++;
        }
        return -1;
    }
};