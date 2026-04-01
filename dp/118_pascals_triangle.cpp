#include <bits/stdc++.h>
using namespace std;

/*
    Problem 118: Pascal's Triangle
    Pattern: DP
    Time: O(n^2), Space: O(n^2)
*/

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        int n = numRows;
        vector<vector<int>> ans;
        ans.push_back({1});

        for (int _ = 1; _ < n; _++)
        {
            vector<int> temp;
            vector<int> prev = ans.back();
            for (int i = 0; i < _ + 1; i++)
            {
                int el =
                    (i - 1 < 0 ? 0 : prev[i - 1]) +
                    (i >= prev.size() ? 0 : prev[i]);
                temp.push_back(el);
            }
            ans.push_back(temp);
        }
        return ans;
    }
};