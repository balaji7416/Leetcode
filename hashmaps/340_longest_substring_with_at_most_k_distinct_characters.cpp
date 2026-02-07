#include <bits/stdc++.h>
using namespace std;

/* #note: this problem is premium in leetcode so i refered to online for the problem
    Problem 340: Longest Substring with At Most K Distinct Characters
    Given a string s and an integer k, return the length of the longest
    substring of s that contains at most k distinct characters.

    Example 1:
    Input: s = "eceba", k = 2
    Output: 3
    Explanation: The substring is "ece" with length 3.

    Example 2:
    Input: s = "aa", k = 1
    Output: 2
    Explanation: The substring is "aa" with length 2.

    Constraints:
    1 <= s.length <= 5 * 104
    0 <= k <= 50

    #solution:
    1. we will use sliding window technique to solve this problem
    2. we will use hashmap to store the frequency of characters in the window
    3. we will expand the window by moving the right pointer
    4. if the size of the hashmap exceeds k and the curr char not in the window(hashmap) we will shrink the window from the left
    5. we will update the max length of the window when the size of the hashmap is less than or
*/
/*
    # this is the solution i came up with, but it involves a extra condition in the while loop,
        but it's equally efficient as stadard one i have given below this code
class Solution{
public:
    int lengthOfLongestSubstringDistinct(string s, int k)
    {
        if (k == 0)
            return 0;
        int n = s.size();
        unordered_map<char, int> mp;
        int l = 0;
        int ans = 0;
        for (int r = 0; r < n; r++)
        {
            while (mp.size() >= k && !mp.count(s[r]))
            {
                mp[s[l]]--;
                if (mp[s[l]] == 0)
                {
                    mp.erase(s[l]);
                }
                l++;
            }
            mp[s[r]]++;
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};
*/

/*
    #standard solution
    1. we will use sliding window technique to solve this problem
    2. we will use hashmap to store the frequency of characters in the window
    3. we will expand the window by moving the right pointer
    4. if the size of the hashmap exceeds k we will shrink the window from the left
    5. we will update the max length of the window when the size of the hashmap is less than or
*/
class Solution
{
public:
    int lengthOfLongestSubstringDistinct(string s, int k)
    {
        int left = 0;
        int n = s.size();
        unordered_map<char, int> mp;
        int ans = 0;

        if (k == 0)
        {
            return 0;
        }
        for (int right = 0; right < n; right++)
        {
            mp[s[right]]++;
            while (mp.size() > k)
            {
                mp[s[left]]--;
                if (mp[s[left]] == 0)
                {
                    mp.erase(s[left]);
                }
                left++;
            }
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
