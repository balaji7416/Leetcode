#include <bits/stdc++.h>
using namespace std;

/*
    Problem 11: Container With Most Water
    Pattern: Two Pointer
    Time: O(n), Space: O(1)
*/
/* IDEA:
Two pointers from both ends:
area = width * min(height[l], height[r])
Move the pointer with smaller height (only chance to improve area)
→ greedy + two pointers, O(n)
*/

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int ans = 0;
        int n = height.size();
        int l = 0, r = n - 1;

        while (l <= r)
        {
            ans = max(ans, (r - l) * min(height[l], height[r]));
            if (height[l] < height[r])
                l++;
            else
                r--;
        }
        return ans;
    }
};