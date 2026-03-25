#include <bits/stdc++.h>
using namespace std;

/*
    Problem 238: Product of Array Except Self
    Pattern: Prefix Sum, suffix sum
    Time: O(n), Space: O(1)
*/

/*
Build prefix and suffix products:
prefix[i] = product of elements before i
suffix[i] = product of elements after i
Answer[i] = prefix[i-1] * suffix[i+1]
→ avoids division, handles “product except self” in O(n)
*/

class Solution
{
public:
    vector<int> productExceptSelf(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> prefix(n, 1), suffix(n, 1);
        prefix[0] = nums[0], suffix[n - 1] = nums[n - 1];
        for (int i = 1; i < n; i++)
        {
            prefix[i] = prefix[i - 1] * nums[i];
        }
        for (int i = n - 2; i >= 0; i--)
        {
            suffix[i] = suffix[i + 1] * nums[i];
        }
        vector<int> ans(n, 1);
        for (int i = 0; i < n; i++)
        {
            ans[i] = (i > 0 ? prefix[i - 1] : 1) * (i < n - 1 ? suffix[i + 1] : 1);
        }
        return ans;
    }
};