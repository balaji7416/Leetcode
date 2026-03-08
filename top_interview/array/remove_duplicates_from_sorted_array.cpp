#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int n = nums.size();
        int k = 0;
        int prev = nums[0];
        for (int i = 1; i < n; i++)
        {
            while (i < n && nums[i] == prev)
            {
                i++;
            }
            if (i < n)
            {
                prev = nums[i];
                k++;
            }

            if (i < n && i > k)
            {
                swap(nums[i], nums[k]);
            }
        }
        return k;
    }
};