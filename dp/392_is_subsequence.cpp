#include <bits/stdc++.h>
using namespace std;

/*
    Problem 392: Is Subsequence
    Pattern: normal traversal + two pointer
    Time: O(n), Space: O(1)
*/

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        int i = 0, j = 0;
        while (i < t.size())
        {
            if (t[i] == s[j])
                j++;
            i++;
        }
        return j == s.size();
    }
};