#include <bits/stdc++.h>
using namespace std;

/*
    Problem 20: Valid Parentheses
    Pattern: Stack
    Time: O(n), Space: O(n)
*/

/*
    idea: stack
*/

class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> stk;
        for (auto c : s)
        {
            if (c == '(' or c == '[' or c == '{')
            {
                stk.push(c);
            }
            else
            {
                if (stk.empty())
                    return false;
                char t = stk.top();
                stk.pop();
                if ((c == ')' and t != '(') or (c == ']' and t != '[') or (c == '}' and t != '{'))
                {
                    return false;
                }
            }
        }
        return stk.empty();
    }
};