#include <bits/stdc++.h>
using namespace std;

/*
    Problem 55: Jump Game
    Pattern: Greedy
    Time: O(n), Space: O(1)
*/

/* Idea:
Work backwards and maintain the leftmost "safe" index that can reach the end.

Initialize safe = n-1 (last index is always reachable from itself).

For each index i from n-2 → 0:
    if i + nums[i] >= safe:
        update safe = i   // i can reach a safe position, so it becomes safe

At the end:
    if safe == 0 → start can reach a safe node -> which inturn reach the end → return true
    else → return false

Time: O(n)
Space: O(1)

Key Insight:
Instead of checking all forward jumps, shrink the goal backwards.
*/

class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int n = nums.size();
        bool pos = false;
        int safe = n - 1;
        for (int i = n - 2; i >= 0; i--)
        {
            if (i + nums[i] >= safe)
            {
                safe = i;
            }
        }
        return safe == 0;
    }
};