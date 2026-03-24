#include <bits/stdc++.h>
using namespace std;

/*
    Problem 34: Find First and Last Position of Element in Sorted Array
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/

class Solution
{
public:
    vector<int> searchRange(vector<int> &nums, int target)
    {
        auto l = lower_bound(nums.begin(), nums.end(), target);
        auto r = upper_bound(nums.begin(), nums.end(), target);

        if (l == nums.end() || *l != target)
        {
            return {-1, -1};
        }
        int left = l - nums.begin();
        int right = r - nums.begin() - 1;
        return {left, right};
    }
};