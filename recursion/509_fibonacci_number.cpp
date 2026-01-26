#include <bits/stdc++.h>
using namespace std;

/*
    Problem 509: Fibonacci Number
    Pattern: Recursion + dp
    Time: O(n), Space: O(n)
*/

/*
    idea: dp + recursion
          fib(n) = fib(n-1) + fib(n-2)
*/

class Solution
{
public:
    int calc(int n, unordered_map<int, int> &dp)
    {
        if (n <= 1)
            return n;
        if (dp.count(n))
            return dp[n];
        return dp[n] = calc(n - 1, dp) + calc(n - 2, dp);
    }
    int fib(int n)
    {
        unordered_map<int, int> dp;
        return calc(n, dp);
    }
};