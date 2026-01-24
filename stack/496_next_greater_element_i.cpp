#include <bits/stdc++.h>
using namespace std;

/*
    Leetcode probelem 496: Next Greater Element I
    Pattern: Monotonic Stack
    Time: O(n), Space: O(n)
*/

/*
    idea: reverse traversal + value stack + unordered map for O(1) lookup
*/
class Solution
{
public:
    vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
    {
        int n = nums2.size();
        vector<int> ans(n, -1);
        stack<int> s;
        for (int i = n - 1; i >= 0; i--)
        {
            while (!s.empty() && nums2[i] >= s.top())
            {
                s.pop();
            }
            if (!s.empty())
                ans[i] = s.top();
            s.push(nums2[i]);
        }
        unordered_map<int, int> m;
        for (int i = 0; i < n; i++)
        {
            m[nums2[i]] = ans[i];
        }
        vector<int> result;
        for (auto i : nums1)
        {
            result.push_back(m[i]);
        }
        return result;
    }
};