#include <bits/stdc++.h>
using namespace std;

/*
    Problem 217: Contains Duplicate
    Pattern: Hashmap
    Time: O(n), Space: O(n)
*/

class Solution
{
public:
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_set<int> s;
        for (auto el : nums)
        {
            if (s.count(el))
            {
                return true;
            }
            s.insert(el);
        }
        return false;
    }
};