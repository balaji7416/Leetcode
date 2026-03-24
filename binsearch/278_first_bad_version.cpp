#include <bits/stdc++.h>
using namespace std;

/*
    Problem 278: First Bad Version
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/
/*IDEA:
    classic lower bound
*/
// The API isBadVersion is defined for you.
bool isBadVersion(int version) {};

class Solution
{
public:
    int firstBadVersion(int n)
    {
        int low = 0, high = n, ans = n;
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isBadVersion(mid))
            {
                ans = mid;
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return ans;
    }
};