#include <bits/stdc++.h>
using namespace std;

/*
    Problem 125: Valid Palindrome
    Pattern: Two Pointer
    Time: O(n), Space: O(1)
*/

class Solution
{
public:
    bool isPalindrome(string s)
    {
        // string new_s = "";
        // for(auto c: s){
        //     if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'){
        //         new_s += tolower(c);
        //     } else if(c >= '0' && c <= '9'){
        //         new_s += c;
        //     }
        // }
        for (char &c : s)
        {
            if (c >= 'A' && c <= 'Z')
                c = tolower(c);
        }
        auto valid = [&](char c)
        {
            return (c >= 'a' && c <= 'z') ||
                   (c >= '0' && c <= '9');
        };
        auto is_p = [&](auto &&self, int l, int r) -> bool
        {
            if (l >= r)
                return true;
            if (!valid(s[l]))
                return self(self, l + 1, r);
            if (!valid(s[r]))
                return self(self, l, r - 1);
            if (s[l] != s[r])
                return false;
            return self(self, l + 1, r - 1);
        };

        return is_p(is_p, 0, s.size() - 1);
    }
};