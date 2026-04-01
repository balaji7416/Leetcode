#include <bits/stdc++.h>
using namespace std;

/*
    Problem 119: Pascal's Triangle II
    Pattern: DP
    Time: O(n) if used combinatorics identity,
          O(n^2) if followed the algorithm
    Space: O(n)
*/

/*
    algorithm
*/
class Solution
{
public:
    vector<int> getRow(int rowIndex)
    {
        int n = rowIndex;
        vector<int> prev = {1};
        for (int _ = 1; _ <= n; _++)
        {
            vector<int> temp;
            for (int i = 0; i < _ + 1; i++)
            {
                int val = (i - 1 < 0 ? 0 : prev[i - 1]) +
                          (i >= prev.size() ? 0 : prev[i]);
                temp.push_back(val);
            }
            prev = temp;
        }
        return prev;
    }
};

/*
    combinatorics:
    C(n,k) = C(n,k-1) * (n-k+1) / k
*/
class Solution
{
public:
    vector<int> getRow(int rowIndex)
    {
        int n = rowIndex;
        vector<int> ans(n + 1);
        ans[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            ans[i] = (long long)ans[i - 1] * (n - i + 1) / i; // to avoid overflow
        }
        return ans;
    }
};