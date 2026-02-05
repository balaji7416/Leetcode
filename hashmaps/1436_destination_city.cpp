#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1436: Destination City
    Pattern: Hashset
    Time: O(n), Space: O(n)
*/

/*
    idea:
        create hashset of sources
        for each path, if path[1] (which is destination) is not in hashset, return path[1]
*/

class Solution
{
public:
    string destCity(vector<vector<string>> &paths)
    {
        unordered_set<string> sources;
        for (auto path : paths)
        {
            sources.insert(path[0]);
        }
        string ans;
        for (auto path : paths)
        {
            if (!sources.count(path[1]))
            {
                ans = path[1];
            }
        }
        return ans;
    }
};