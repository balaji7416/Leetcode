#include <bits/stdc++.h>
using namespace std;

/*
    Problem 22: Generate Parentheses
    Pattern: Backtracking
    Time: O(4^n), Space: O(n)
*/

class Solution
{
public:
    void generate(string &curr, int &open, int &close, int n,
                  vector<string> &ans)
    {

        if (open > n || close > open)
        {
            return;
        }
        if (curr.size() == 2 * n)
        {
            ans.push_back(curr);
            return;
        }

        if (open < n)
        {
            curr += "(";
            open += 1;
            generate(curr, open, close, n, ans);

            curr.pop_back();
            open -= 1;
        }

        if (close < open)
        {
            curr += ")";
            close += 1;
            generate(curr, open, close, n, ans);
            curr.pop_back();
            close -= 1;
        }
    }
    vector<string> generateParenthesis(int n)
    {
        vector<string> ans;
        string curr;
        int open = 0, close = 0;
        generate(curr, open, close, n, ans);
        return ans;
    }
};