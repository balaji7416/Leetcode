#include <bits/stdc++.h>
using namespace std;

/*
    Problem 32: Longest Valid Parentheses
    Pattern: DP
    Time: O(n), Space: O(n)
*/

/* DP solution IDEA
dp[i] = length of longest valid parentheses substring ending at index i

We only update when s[i] == ')', since valid substrings must end with ')'.

Case 1: "...()"
If s[i-1] == '(':
    dp[i] = dp[i-2] + 2
    (extend any valid substring before this pair)

Case 2: "...))"
If s[i-1] == ')':
    Let j = i - dp[i-1] - 1 → possible matching '('
    If j >= 0 and s[j] == '(':
        dp[i] = dp[i-1] + 2 + dp[j-1]
        (extend previous valid block and connect to earlier one)

Track maximum over all dp[i].

Time: O(n), Space: O(n)
*/

/* STACK solution IDEA
Stack-based idea:

Use stack to store indices of unmatched '('.
Initialize with -1 to act as a base (last invalid position).

Traverse string:
- If s[i] == '(', push index i.
- If s[i] == ')':
    - Pop one element (try to match a '(').
    - If stack becomes empty:
        → push current index i as new base (invalid boundary).
    - Else:
        → valid substring exists ending at i
        → length = i - stack.top()
        → update maxLen

Key intuition:
Stack always keeps track of the last unmatched index,
so we can compute length of valid substring ending at current position.

Time: O(n), Space: O(n)
*/

/* GREEDY solution IDEA
Two-pass (greedy counting) idea:

We scan the string twice while counting:
left = number of '('
right = number of ')'

Pass 1: Left → Right
- Increment counters based on character
- If left == right:
    → valid substring found → length = 2 * right
- If right > left:
    → too many ')' → invalid → reset both counters

Pass 2: Right → Left
- Same logic, but reversed
- This handles cases with extra '(' that were missed in first pass
- If left == right:
    → valid substring → length = 2 * left
- If left > right:
    → too many '(' → reset

Key intuition:
We track balance instead of positions.
Reset when invalid, and scan both directions to handle
extra ')' (forward) and extra '(' (backward).

Time: O(n), Space: O(1)
*/

/*dp solution*/
class Solution_dp
{
public:
    int longestValidParentheses(string s)
    {
        int n = s.size();
        vector<int> dp(n, 0);
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == ')')
            {
                if (i - 1 >= 0 && s[i - 1] == '(')
                {
                    dp[i] = (i - 2 < 0 ? 0 : dp[i - 2]) + 2;
                }
                else if (i - 1 >= 0 && s[i - 1] == ')')
                {
                    int j = i - dp[i - 1] - 1;
                    if (j >= 0 && s[j] == '(')
                    {
                        dp[i] = (j - 1 < 0 ? 0 : dp[j - 1]) + dp[i - 1] + 2;
                    }
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};

/*stack solution*/
class Solution_stack
{
public:
    int longestValidParentheses(string s)
    {
        int n = s.size();
        stack<int> stk;
        stk.push(-1);
        int maxLen = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
            {
                stk.push(i);
            }
            else
            {
                stk.pop();
                if (stk.empty())
                    stk.push(i);
                maxLen = max(maxLen, i - stk.top());
            }
        }
        return maxLen;
    }
};

class Solution_greedy
{
public:
    int longestValidParentheses(string s)
    {
        int n = s.size();
        int left = 0, right = 0;
        int maxLen = 0;

        // first pass left -> right
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(')
                left++;
            else
                right++;

            if (left == right)
            {
                maxLen = max(maxLen, 2 * right);
            }
            else if (right > left)
            {
                left = right = 0;
            }
        }

        left = right = 0;
        // second pass right->left
        for (int i = n - 1; i >= 0; i--)
        {
            if (s[i] == '(')
                left++;
            else
                right++;

            if (left == right)
            {
                maxLen = max(maxLen, 2 * left);
            }
            else if (left > right)
            {
                left = right = 0;
            }
        }

        return maxLen;
    }
};