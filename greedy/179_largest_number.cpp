#include <bits/stdc++.h>
using namespace std;

/*
    Problem 179: Largest Number
    Pattern: Greedy
    Time: O(nlogn), Space: O(n)
*/

/** Idea: Greedy
 * To form the largest number from an array of integers,
 * treat each number as a string and sort them such that for any two numbers a and b,
 * the order a before b is chosen if concatenating a+b is larger than b+a.
 * This ensures that the final concatenated string is maximized.
 */

class Solution
{
public:
    string largestNumber(vector<int> &nums)
    {
        int n = nums.size();
        vector<string> nums_;
        for (auto num : nums)
        {
            nums_.push_back(to_string(num));
        }
        sort(nums_.begin(), nums_.end(), [&](string &a, string &b)
             { return a + b > b + a; });
        string ans = "";
        for (auto _ : nums_)
        {
            ans += _;
        }

        return ans[0] == '0' ? "0" : ans;
    }
};