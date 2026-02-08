#include <bits/stdc++.h>
using namespace std;

/*
    Problem 205: Isomorphic Strings
    Pattern: Hashmap as memory
    Time: O(n), Space: O(n)
*/

/*
Logic:
- mp stores s → t mapping (memory of decisions)
- used ensures no two s chars map to same t char

For each index i:
1) If s[i] already mapped:
      if mp[s[i]] != t[i] → return false
2) Else (new mapping):
      if t[i] already in used → return false
      create mp[s[i]] = t[i], mark t[i] as used

If all indices pass → return true
*/

/*
Logic:
- mp1 stores s → t
- mp2 stores t → s (reverse constraint)

For each index i:
1) If s[i] mapped and mp1[s[i]] != t[i] → return false
2) If t[i] mapped and mp2[t[i]] != s[i] → return false
3) Otherwise create both mappings

If all indices pass → return true
*/

class Solution
{
public:
    bool isIsomorphic(string s, string t)
    {
        int n = s.size();
        unordered_map<char, char> mp;
        unordered_set<char> used;
        for (int i = 0; i < n; i++)
        {
            if (mp.count(s[i]))
            {
                if (mp[s[i]] != t[i])
                {
                    return false;
                }
            }
            else
            {
                if (used.count(t[i]))
                {
                    return false;
                }
                mp[s[i]] = t[i];
                used.insert(t[i]);
            }
        }
        return true;
    }
};