#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        unordered_map<int, int> mp;
        for (auto _ : nums1)
        {
            mp[_]++;
        }
        vector<int> ans;
        for (int el : nums2)
        {
            if (mp[el] > 0)
            {
                ans.push_back(el);
                mp[el]--;
            }
        }
        return ans;
    }
};