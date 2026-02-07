#include <bits/stdc++.h>
using namespace std;

/*
    Problem 424: Longest Repeating Character Replacement
    Pattern: Sliding Window
    Time: O(n)
*/

/*
====================================================
MY INITIAL (INTUITIVE) LOGIC
====================================================

Idea:
- Expand right pointer.
- Track frequency of characters in current window.
- For each window:
    - Find the character with maximum frequency (true max).
    - All other characters need replacement.
    - replacements = window_size - true_max_freq
- If replacements > k:
    - Window is invalid
    - Shrink from the left
    - Update frequencies and recompute max frequency
- Only consider window when it is truly valid.

Problem with this logic:
- Recomputing max frequency on shrink requires full map traversal.
- This breaks the intended O(n) sliding window optimization.
- Also, this level of exactness is unnecessary for this problem.


====================================================
ACTUAL LOGIC USED IN LC 424
====================================================

Key Insight:
- We are solving a MAXIMUM window problem.
- We do NOT need the window to be perfectly valid at every step.
- We only need to ensure that a window size is ACHIEVABLE somewhere.

Actual Invariant:
- maxFreq = maximum frequency EVER seen while expanding the window.
- maxFreq is updated ONLY when expanding (right++).
- maxFreq is NEVER decreased when shrinking.

Why this works:
- Condition checked:
      window_size - maxFreq <= k
- If maxFreq is stale (too large), this condition becomes looser.
- This may allow a slightly invalid window,
  but it can NEVER create an impossible window length.
- Any accepted window length corresponds to a valid configuration
  that existed at some earlier point.

Result:
- No full map traversal needed.
- O(n) time.
- Correct because we are maximizing length, not validating exact windows.

Mental one-liner:
- "LC 424 checks if a window length is possible, not if the current window is perfect."
====================================================
*/

class Solution
{
public:
    // not needed for standard alogo (not understood why yet)
    // int update_maxm(int maxm, unordered_map<char, int> &mp)
    // {
    //     for (auto [key, val] : mp)
    //     {
    //         maxm = max(maxm, val);
    //     }
    //     return maxm;
    // }
    int characterReplacement(string s, int k)
    {
        int n = s.size();
        unordered_map<char, int> mp;
        int maxm = 0;
        // char maxChar;
        int l = 0;
        int ans = 0;
        for (int r = 0; r < n; r++)
        {
            mp[s[r]]++;
            if (mp[s[r]] > maxm)
            {
                // maxChar = s[r];
                maxm = mp[s[r]];
            }
            while (r - l + 1 - maxm > k)
            {
                mp[s[l]]--;
                maxm = max(maxm, mp[s[l]]);
                // not needed for standard alogo (not understood why yet)
                //  if (s[l] == maxChar)
                //  {
                //      maxm--;
                //      maxm = update_maxm(maxm, mp);
                //  }
                if (mp[s[l]] == 0)
                {
                    mp.erase(s[l]);
                }
                l++;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};