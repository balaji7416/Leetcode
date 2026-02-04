#include <bits/stdc++.h>
using namespace std;

/*
    Problem 128: Longest Consecutive Sequence
    Pattern: Hashmap / sort + two pointer
    Time: hashmap -> O(n), sort + two pointer -> O(nlogn),
    Space: hashmap -> O(n), sort + two pointer -> O(n)

    #note: although hashmap version is algorithmically O(n) and sort+two pointer version is O(nlogn)
            the sort method might beat in practical speed tests (eg. in leetcode tests)
*/

/* sort + two pointer
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        int ans = n > 0 ? 1 : 0;
        int l = 0, r = 1;
        while (r < n)
        {
            if (nums[r] == 1 + nums[r - 1])
            {
                ans = max(ans, r - l + 1);
                r++;
            }
            else if (nums[r] == nums[r - 1])
            {
                l++;
                r++;
            }
            else
            {
                l = r;
                r++;
            }
        }
        return ans;
    }
};
*/
/* hashmap*/
class Solution
{
public:
    int longestConsecutive(vector<int> &nums)
    {
        int n = nums.size();
        unordered_set<int> st(nums.begin(), nums.end());
        int ans = 0;

        for (auto el : st)
        {
            if (st.count(el - 1))
                continue;

            int len = 1;
            int curr = el;
            while (st.count(curr + 1))
            {
                curr++;
                len++;
            }

            ans = max(ans, len);
        }

        return ans;
    }
};