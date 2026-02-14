#include <bits/stdc++.h>
using namespace std;

/*
    Problem 733: Flood Fill
    Pattern: DFS
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea:
        dfs + 2d grid
        run dfs/bfs from the given sr, sc and change all the nodes reachable from sr, sc
        having same color as starting node to color
*/

class Solution
{
public:
    void dfs(int r, int c, int org_col, int new_col, vector<vector<int>> &image, vector<vector<bool>> &visited)
    {
        int n = image.size();
        int m = image[0].size();
        if (r >= n || r < 0 || c >= m || c < 0)
            return;
        if (visited[r][c] || image[r][c] != org_col)
            return;
        visited[r][c] = true;
        image[r][c] = new_col;
        vector<int> dx = {1, -1, 0, 0};
        vector<int> dy = {0, 0, 1, -1};
        for (int i = 0; i < 4; i++)
        {
            dfs(r + dx[i], c + dy[i], org_col, new_col, image, visited);
        }
    }
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int n = image.size();    // rows
        int m = image[0].size(); // cols
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        dfs(sr, sc, image[sr][sc], color, image, visited);
        return image;
    }
};