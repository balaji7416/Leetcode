#include <bits/stdc++.h>
using namespace std;

/*
    #note: this problem is premium in leetcode so i refered to online for the problem
    Problem 325: Maximum Size Subarray Sum Equals k
    Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

    Note:
    The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

    Example 1:

    Input: nums = [1, -1, 5, -2, 3], k = 3
    Output: 4
    Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
    Example 2:

    Input: nums = [-2, -1, 2, 1], k = 1
    Output: 2
    Explanation: The subarray [-1, 2] sums to 1 and is the longest.
    Follow Up:
    Can you do it in O(n) time?

    #solution:
    1. we will use prefix sum and hashmap to solve this problem
    2. we will store the prefix sum in a hashmap and if we find the prefix sum in the hashmap then we will update the max length
*/

class Solution
{
public:
    int maxSubArrayLen(vector<int> &nums, int k)
    {

        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }

        unordered_map<int, int> firstIdx;
        int maxLen = 0;
        for (int i = 0; i <= n; i++)
        {
            int req = prefix[i] - k;
            if (firstIdx.count(req))
            {
                maxLen = max(maxLen, i - firstIdx[req]);
            }

            // add to firstIdx only if it's not added before to avoid overwriting
            if (!firstIdx.count(prefix[i]))
                firstIdx[prefix[i]] = i;
        }
        return maxLen;
    }
};
