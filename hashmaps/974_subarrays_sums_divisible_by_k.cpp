#include <bits/stdc++.h>
using namespace std;

/*
    Problem 974: subarrays sum divisible by k
    Pattern: Hashmap
    Time: O(n), Space: O(n)
*/

/*

    sum(l,r) = prefix[r] - prefix[l-1] = subarray sum
    sum(l,r) % k == 0
    => (prefix[r] - prefix[l-1]) % k == 0
    => prefix[r] % k == prefix[l-1] % k
    => prefix[r] % k == req
    => req = prefix[r] % k
    => req = (prefix[r] % k + k) % k // for handling negative numbers

    iterate over prefix array and find req in hashmap and add it to ans
        i.e., add count of req in hashmap to ans
*/

class Solution
{
public:
    int subarraysDivByK(vector<int> &nums, int k)
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
            int req = ((prefix[i] % k) + k) % k;
            if (freq.count(req))
            {
                ans += freq[req];
            }
            freq[req]++;
        }
        return ans;
    }
};