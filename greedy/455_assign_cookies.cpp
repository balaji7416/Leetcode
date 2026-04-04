#include <bits/stdc++.h>
using namespace std;

/*
    Problem 455: Assign Cookies
    Pattern: Greedy
    Time: O(nlogn + mlogm), Space: O(1)
*/
/* IDEA: Greedy
Sort both arrays. Try to satisfy the greediest child using the largest available cookie.
If the largest cookie can satisfy the current child, assign it and move both pointers.
Otherwise, skip the child (since no smaller cookie can satisfy them).
Maximizes number of satisfied children.
*/

class Solution
{
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        int cnt = 0, i = g.size() - 1, j = s.size() - 1;
        while (i >= 0 && j >= 0)
        {
            if (s[j] >= g[i])
            {
                cnt++;
                i--;
                j--;
            }
            else
            {
                i--;
            }
        }
        return cnt;
    }
};