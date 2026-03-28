#include <bits/stdc++.h>
using namespace std;

/*
    Problem 852: Peak Index in a Mountain Array
    Pattern: Binary Search
    Time: O(logn), Space: O(1)
*/

class Solution
{
public:
    int peakIndexInMountainArray(vector<int> &arr)
    {
        int n = arr.size();
        int low = 0, high = n - 1;
        while (low < high)
        {
            int mid = low + (high - low) / 2;
            if (arr[mid] > arr[mid + 1])
            {
                // peak in left
                high = mid;
            }
            else
            {
                // peak in right
                low = mid + 1;
            }
        }
        return low;
    }
};