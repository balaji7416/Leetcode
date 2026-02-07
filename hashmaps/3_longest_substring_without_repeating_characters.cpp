#include <bits/stdc++.h>
using namespace std;

/*
    Problem 3: Longest Substring Without Repeating Characters
    Pattern: Hashmap/Hashset + Sliding Window
    Time: O(n), Space: O(n)
*/

/*
    idea:
        maintain a hashmap/hashset to store chars in window
        expand right
        shrink left when window invalid (duplicate char found)
        consider the window when it is valid
        update len of longest window

    note: we can also use hashset instead of hashmap since we
          don't care about char freq
*/

/*
    for hashmap:
    unordered_map<char,int> mp;

for r = l to r = n-1:
    if(mp.count(s[r])){
        mp[s[l]]--;

        // important while using hashmap
        if(mp[s[l]]==0){
            mp.erase(s[l]);
        }

        l++; // important
    }

    mp[s[r]]++;
    ans = max(ans, r-l+1);
*/
class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int n = s.size();
        unordered_set<int> st;
        int l = 0;
        int max_len = 0;
        for (int r = 0; r < n; r++)
        {

            // if window is invalid shrink until it's valid
            while (st.count(s[r]))
            {
                st.erase(s[l]);
                l++;
            }

            // insert the current char in window
            st.insert(s[r]);

            // update the max_len
            max_len = max(max_len, r - l + 1);
        }
        return max_len;
    }
};