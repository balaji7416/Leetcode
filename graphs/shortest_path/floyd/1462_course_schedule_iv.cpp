#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1462: Course Schedule IV
    Pattern: Floyd
    Time: O(n^3) space: O(n^2)
*/

/* Logic:
    - Build adjacency matrix.
    - Run floyd's algorithm.
    - For each query, check if u -> v
*/

class Solution
{
public:
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>> &prerequisites, vector<vector<int>> &queries)
    {
        int n = numCourses;
        vector<vector<int>> reachable(n, vector<int>(n, false));
        for (auto e : prerequisites)
        {
            int u = e[0], v = e[1];
            reachable[u][v] = true;
        }
        // for(int i=0; i<n; i++){
        //     reachable[i][i] = true;
        // }
        // run floyd
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    reachable[i][j] |= reachable[i][k] && reachable[k][j];
                }
            }
        }

        // ans the queries;
        int q = queries.size();
        vector<bool> ans(q, false);
        for (int i = 0; i < q; i++)
        {
            int u = queries[i][0], v = queries[i][1];
            ans[i] = reachable[u][v];
        }

        return ans;
    }
};