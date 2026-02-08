#include <bits/stdc++.h>
using namespace std;

/*
    Problem 525: Contiguous Array
    Pattern: Hashmap
    Time: O(n), Space: O(n)
*/

/*
    idea:

    stadard prefix sum + hashmap solution:
        encode 0 -> +1 and 1 -> -1
        now calculate prefix sum array
        now derive the required equation i.e., prefix[r+1]-prefix[l] = 0
            => prefix[r+1] = prefix[l]
            i.e., if we see the same prefix sum again, the subarray between the two indices has sum 0.
        make sure only use the first occurence of the prefix sum, don't overwrite it to ensure max length
        now track the maximum length found.


    Convert the problem:
        Treat 0 as -1 and 1 as +1.

        Now the task becomes:
        Find the longest subarray with sum = 0.

        Use a prefix sum while traversing the array.

        Store the first index where each prefix sum appears in a hashmap.

        If the same prefix sum appears again at index i,
        the subarray between the two indices has sum 0.

        Track the maximum length found.

        Key base case

        Store sum = 0 at index -1 to handle subarrays starting from index 0.
*/

/* Brute force solution:
        Time -> O(n^2)

class Solution
{
public:
    int findMaxLength(vector<int> &nums)
    {
        int n = nums.size();
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int zeroes = 0;
            int ones = 0;
            for (int j = i; j < n; j++)
            {
                if (nums[j] == 0)
                {
                    zeroes++;
                }
                else
                {
                    ones++;
                }
                if (zeroes == ones)
                {
                    ans = max(ans, j - i + 1);
                }
            }
        }
        return ans;
    }
};
*/
/*Hashmap + prefix sum*/
class Solution
{
public:
    int findMaxLength(vector<int> &nums)
    {
        int n = nums.size();
        unordered_map<int, int> mp;
        int sum = 0;
        int ans = 0;
        mp[0] = -1;
        for (int i = 0; i < n; i++)
        {
            sum += nums[i] == 1 ? -1 : 1;
            auto it = mp.find(sum);
            if (it != mp.end())
            {
                ans = max(ans, i - it->second);
                continue;
            }
            mp[sum] = i;
        }
        return ans;
    }
};