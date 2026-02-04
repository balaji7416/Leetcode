#include <bits/stdc++.h>
using namespace std;

/*
    Problem 219: Contains Duplicate II
    Pattern: Hashmap
    Time: O(n), Space: O(n)
*/

class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++)
        {
            auto it = mp.find(nums[i]);
            if (it != mp.end())
            {
                if (i - it->second <= k)
                {
                    return true;
                }
            }
            mp[nums[i]] = i;
        }
        return false;
    }
};