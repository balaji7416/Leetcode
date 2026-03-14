#include <bits/stdc++.h>
using namespace std;

/*
    Problem 410: Split Array Largest Sum
    Pattern: Binary Search
    Time: O(nlogn), Space: O(1)
*/
/* Idea:
    Binary Search on Answer.

    We want to minimize the maximum subarray sum when splitting
    the array into k contiguous parts.

    Search range:
    low  = max element (a subarray must at least contain this)
    high = total sum   (whole array as one subarray)

    For a candidate max sum 'cap', greedily form subarrays:
    keep adding elements until the sum would exceed 'cap',
    then start a new subarray.

    This greedy process gives the minimum number of parts
    required with limit 'cap'.

    If parts <= k, the capacity works (extra splits are possible),
    so try to minimize it further with binary search.

    Time: O(n log(sum(nums))), Space: O(1)
*/

class Solution
{
public:
    int splitArray(vector<int> &nums, int k)
    {
        int n = nums.size();
        int low = 0, high = 0;
        for (int _ : nums)
        {
            low = max(low, _);
            high += _;
        }
        int ans = high;

        auto isValid = [&](int cap)
        {
            int parts = 0;
            int curr = 0;
            for (int _ : nums)
            {
                if (curr + _ > cap)
                {
                    parts++;
                    curr = 0;
                }
                curr += _;
            }
            if (curr != 0)
                parts++;
            return parts <= k;
        };
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isValid(mid))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};