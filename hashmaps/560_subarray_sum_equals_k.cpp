#include <bits/stdc++.h>
using namespace std;

/*
    Problem 560: Subarray sum equals k

    Given an array of integers nums and an integer k, return the total number of subarrays whose sum equals to k.

    Example 1:
    Input: nums = [1,1,1], k = 2
    Output: 2

    Example 2:
    Input: nums = [1,2,3], k = 3
    Output: 2

    Solution:
    We use a hashmap to store the frequency of prefix sums. We iterate through the array, and for each element, we calculate the prefix sum. If the prefix sum minus k exists in the hashmap, we increment the count by the frequency of that prefix sum. We then update the hashmap with the current prefix sum.

    Time Complexity: O(n)
    Space Complexity: O(n)
*/

/*
    prefix[r+1]-prefix[l] = k => prefix[l] = prefix[r+1]-k;
    iterate over prefix array
    for every idx check how many req prefix sums already present in freq map
    add that many to ans
    add the count of current prefix to freq map
*/

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }

        unordered_map<int, int> freq;
        int ans = 0;
        for (int i = 0; i <= n; i++)
        {
            int req = prefix[i] - k;
            auto it = freq.find(req);
            if (it != freq.end())
            {
                ans += it->second;
            }
            freq[prefix[i]]++;
        }
        return ans;
    }
};