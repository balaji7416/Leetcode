#include <bits/stdc++.h>
using namespace std;

/*
    Problem 409: Longest Palindrome
    Pattern: Hashmap
    Time: O(n), Space: O(n)
*/

/*
    idea:
        count freq of all chars
        take all chars with even freq into len
        for odd freq chars, take freq-1 and add 1 to len at end if odd len is possible
*/

class Solution
{
public:
    int longestPalindrome(string s)
    {
        unordered_map<char, int> mp;
        for (auto c : s)
        {
            mp[c]++;
        }
        int len = 0;
        bool odd_found = false;
        for (auto &[key, val] : mp)
        {
            if (val % 2 == 0)
            {
                len += val;
            }
            else
            {
                odd_found = true;
                len += val - 1;
            }
        }
        return len + (odd_found ? 1 : 0);
    }
};