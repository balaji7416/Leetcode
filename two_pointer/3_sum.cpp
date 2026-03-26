#include <bits/stdc++.h>
using namespace std;

/*
    Problem 3: 3Sum
    Pattern: Two Pointer
    Time: O(n^2), Space: O(n)(for building ans)
*/
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> ans;

        sort(nums.begin(), nums.end());
        for (int i = 0; i < n; i++)
        {
            // for skipping duplicate
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            int n1 = nums[i];
            int l = i + 1, r = n - 1;
            while (l < r)
            {
                int n2 = nums[l], n3 = nums[r];
                int s = n1 + n2 + n3;
                if (s == 0)
                {
                    ans.push_back({n1, n2, n3});
                    l++;
                    r--;
                    // skip duplicates
                    while (l < r && nums[l] == nums[l - 1])
                        l++;
                    while (l < r && nums[r] == nums[r + 1])
                        r--;
                }
                else if (s < 0)
                {
                    l++;
                }
                else
                {
                    r--;
                }
            }
        }
        return ans;
    }
};