#include <bits/stdc++.h>
using namespace std;

/*
    Problem 69: Sqrt(x)
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/

class Solution
{
public:
    int mySqrt(int x)
    {
        int low = 1, high = x, ans = 0;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (mid <= x / mid)
            {
                ans = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return ans;
    }
};