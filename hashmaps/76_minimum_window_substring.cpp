#include <bits/stdc++.h>
using namespace std;

/*
    Problem 76: Minimum Window Substring
    Pattern: Sliding Window
    Time: O(n), Space: O(n)
*/
/* The First Approach i came up with
    Sliding Window with full validation check

    - Maintain two hashmaps:
        mp2 -> required character frequencies from t
        mp1 -> current window frequencies from s

    - Expand the window by moving right pointer
      and update mp1 when the character is required.

    - While the current window is valid:
        (i.e., mp1 contains at least required frequency
         of every character in mp2)
        -> try shrinking from the left to minimize window.

    - Validity is checked by iterating over mp2
      and comparing frequencies with mp1.

    Time Complexity:
        O(n * k), where k = distinct characters in t
        (validation loop runs repeatedly)

    Space Complexity:
        O(k)

    Note:
        Works because k is small, but validation
        scan is the bottleneck.
*/

/* Optimized Sliding Window with incremental validity tracking

    - Store required character frequencies in needMap.
    - Maintain window frequencies in windowMap.

    - need = number of distinct required characters
    - have = number of characters currently satisfying
             required frequency in the window

    - Expand window by moving right pointer:
        -> when a character's frequency matches exactly,
           increment have.

    - Window is valid when:
        have == need

    - Shrink window from the left while valid:
        -> update answer
        -> if a required character drops below needed
           frequency, decrement have.

    Time Complexity:
        O(n) (each character processed once)

    Space Complexity:
        O(k)

    Key Insight:
        Avoid repeated full-map validation by tracking
        validity incrementally.
*/

/* The First Approach i came up with
    Sliding Window with full validation check


class Solution
{
public:
    bool valid(unordered_map<char, int> &mp1, unordered_map<char, int> &mp2)
    {
        for (auto [key, val] : mp2)
        {
            if (mp1[key] < val)
            {
                return false;
            }
        }
        return true;
    }
    string minWindow(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        unordered_map<char, int> mp2;
        unordered_map<char, int> mp1;
        for (auto c : t)
        {
            mp2[c]++;
        }

        int ans_l = 0, ans_r = -1, l = 0;
        int minLen = INT_MAX;

        for (int r = 0; r < n; r++)
        {
            if (mp2.count(s[r]))
            {
                mp1[s[r]]++;
            }

            while (valid(mp1, mp2))
            {
                if (r - l + 1 < minLen)
                {
                    minLen = r - l + 1;
                    ans_l = l;
                    ans_r = r;
                }
                mp1[s[l]]--;
                if (mp1[s[l]] == 0)
                {
                    mp1.erase(s[l]);
                }
                l++;
            }
        }
        string ans = "";
        for (int i = ans_l; i <= ans_r; i++)
        {
            ans += s[i];
        }
        return ans;
    }
};
*/

/* Optimized Sliding Window with incremental validity tracking*/
class Solution
{
public:
    string minWindow(string s, string t)
    {
        int n = s.size();
        unordered_map<char, int> needMap, window;
        for (auto c : t)
        {
            needMap[c]++;
        }
        int need = needMap.size();
        int have = 0;
        int l = 0;
        int start = 0, minLen = INT_MAX;
        for (int r = 0; r < n; r++)
        {
            window[s[r]]++;

            // if the s[r] in needMap and it's count matches with needMap increase have
            if (needMap.count(s[r]) && needMap[s[r]] == window[s[r]])
            {
                have++;
            }

            // if a valid window reached decrease the window until invalid
            while (have == need)
            {
                window[s[l]]--;
                if (r - l + 1 < minLen)
                {
                    minLen = r - l + 1;
                    start = l;
                }
                if (needMap.count(s[l]) && needMap[s[l]] > window[s[l]])
                {
                    have--;
                }
                l++;
            }
        }

        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};