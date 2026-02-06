#include <bits/stdc++.h>
using namespace std;

/*
    Problem 523: continuous subarray sum
    Pattern: Hashmap
    Time: O(n), Space: O(n)
*/

/*
  Idea:
  Use prefix sum modulo k.
  If two prefix sums have the same remainder mod k,
  their difference (subarray sum) is divisible by k.
  Store the first index of each remainder.
  When the same remainder appears again with index difference >= 2,
  a valid subarray exists.
  Constraints guarantee non-negative values, so modulo is safe.
*/

class Solution
{
public:
    bool checkSubarraySum(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prefix(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }

        unordered_map<int, int> firstIdx;
        for (int i = 0; i <= n; i++)
        {
            int req = prefix[i] % k;
            if (firstIdx.count(req))
            {
                if (i - firstIdx[req] >= 2)
                {
                    return true;
                }
            }
            if (!firstIdx.count(req))
            {
                firstIdx[req] = i;
            }
        }
        return false;
    }
};