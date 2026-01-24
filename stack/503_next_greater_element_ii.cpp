#include <bits/stdc++.h>
using namespace std;

// LeetCode 503 - Next Greater Element II
// Pattern: Monotonic Stack, Circular Array
// Final Time: O(n), Space: O(n)

/*
Approach 1: Brute Force
Time: O(n^2), Space: O(1)
Idea:

  For each element, scan forward circularly to find next greater.

class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        stack<int> s;
        vector<int> ans(n, -1);
        for (int i = 0; i < n; i++)
        {
            for (int j = (i + 1) % n; j != i; j = (j + 1) % n)
            {
                if (nums[j] > nums[i])
                {
                    ans[i] = nums[j];
                    break;
                }
            }
        }
        return ans;
    }
};
*/

/*
Approach 2: Forward traversal + index stack
Time: O(n), Space: O(n)
Idea:
  Traverse twice, stack stores indices.

class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        stack<int> s;
        vector<int> ans(n, -1);
        for (int i = 0; i < 2 * n; i++)
        {
            int j = i % n;
            while (!s.empty() && nums[j] > nums[s.top()])
            {
                ans[s.top()] = nums[j];
                s.pop();
            }
            s.push(j);
        }
        return ans;
    }
};
*/

/*

Approach 3: Reverse traversal + value stack (final)
Time: O(n), Space: O(n)
Idea:
  Traverse from 2n-1 to 0, stack stores values.
*/
class Solution
{
public:
    vector<int> nextGreaterElements(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> ans(n, -1);
        stack<int> s;
        for (int i = 2 * n - 1; i >= 0; i--)
        {
            int j = i % n;
            while (!s.empty() && nums[j] >= s.top())
            {
                s.pop();
            }
            if (!s.empty())
            {
                ans[j] = s.top();
            }
            s.push(nums[j]);
        }
        return ans;
    }
};