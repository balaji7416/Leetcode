#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1: Two Sum
    Pattern: Hashmap
    Time: O(n), Space: O(n)
*/

/*
    idea:
        create hashset of nums
        for each num, check if target - num is in hashset
*/
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> mp;
        for (int i = 0; i < nums.size(); i++)
        {
            int comp = target - nums[i];
            auto it = mp.find(comp);
            if (it != mp.end())
            {
                return {it->second, i};
            }
            mp.insert({nums[i], i});
        }
        return {};
    }
};