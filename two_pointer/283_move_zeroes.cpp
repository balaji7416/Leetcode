#include <bits/stdc++.h>
using namespace std;

/*
    Problem 283: Move Zeroes
    Pattern: Two Pointer
    Time: O(n), Space: O(1)
*/

/* IDEA:
Two pointers (compaction):
ptr2 scans array, ptr1 tracks next position for non-zero
Swap non-zero forward, zeros shift back naturally
→ in-place, O(n), stable
*/

class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        int n = nums.size();
        int ptr1 = 0, ptr2 = 0;
        while (ptr2 < n)
        {
            if (nums[ptr2] != 0)
            {
                swap(nums[ptr1], nums[ptr2]);
                ptr1++;
            }
            ptr2++;
        }
    }
};