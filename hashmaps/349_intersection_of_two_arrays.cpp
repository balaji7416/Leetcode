#include <bits/stdc++.h>
using namespace std;

/*
    Problem 349: Intersection of Two Arrays
    Pattern: Hashset
    Time: O(n), Space: O(n)
*/

class Solution
{
public:
    vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> ans;

        // hashset for faster comparision
        unordered_set<int> st(nums1.begin(), nums1.end());

        // if el in mus2 present in set include and remove el from set to avoid duplicates
        for (int el : nums2)
        {
            if (st.count(el))
            {
                ans.push_back(el);
                st.erase(el);
            }
        }
        return ans;
    }
};