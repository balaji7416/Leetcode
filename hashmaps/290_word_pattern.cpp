#include <bits/stdc++.h>
using namespace std;

/*
    Problem 290: word pattern
    Pattern: Hashmap as memory
    Time: O(n), Space: O(n)
*/

/*
LC 290 - Word Pattern (Map + Map logic)

- mp1 stores pattern char → word
- mp2 stores word → pattern char
- Both maps enforce a one-to-one, consistent mapping

Steps:
1) Split string s into words by spaces
2) If words count ≠ pattern length → return false
3) For each index i:
   - If pattern[i] exists in mp1 and mp1[pattern[i]] ≠ words[i] → return false
   - If words[i] exists in mp2 and mp2[words[i]] ≠ pattern[i] → return false
   - If neither exists, create both mappings
4) If all checks pass → return true

Invariant:
- Once a mapping is created, it never changes
- No two pattern chars map to the same word
*/

class Solution
{
public:
    bool wordPattern(string pattern, string s)
    {
        unordered_map<char, string> mp1;
        unordered_map<string, char> mp2;

        vector<string> words;
        for (int i = 0; i < s.size(); i++)
        {
            string temp = "";
            while (i < s.size() && s[i] != ' ')
            {
                temp += s[i++];
            }
            words.push_back(temp);
        }
        if (words.size() != pattern.size())
            return false;
        for (int i = 0; i < words.size(); i++)
        {
            if (mp1.count(pattern[i]) && mp1[pattern[i]] != words[i])
            {
                return false;
            }
            if (mp2.count(words[i]) && mp2[words[i]] != pattern[i])
            {
                return false;
            }
            if (!mp1.count(pattern[i]) && !mp2.count(words[i]))
            {
                mp1[pattern[i]] = words[i];
                mp2[words[i]] = pattern[i];
            }
        }
        return true;
    }
};