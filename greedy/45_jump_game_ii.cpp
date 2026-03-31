#include <bits/stdc++.h>
using namespace std;

/*
    Problem 45: Jump Game II
    Pattern: DP / greedy
    Time: O(n^2) with dp, O(n) with greedy
    Space: O(n)
*/
/* IDEA:
Greedy / BFS-layer idea:

We treat the array like levels:
- currEnd = end of current "range" (all positions reachable with current number of jumps)
- farthest = farthest index we can reach from this range

We iterate through the current range and keep updating farthest.
When we reach currEnd, it means we've explored all positions for this jump,
so we must take a jump:
    jumps++
    currEnd = farthest (move to next range)

This ensures minimum jumps because each jump expands to the maximum possible range.
Time: O(n), Space: O(1)
*/

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int n = nums.size();
        int farthest = 0, currEnd = 0, jumps = 0;
        for (int i = 0; i < n - 1; i++)
        {
            farthest = max(farthest, i + nums[i]);
            if (i == currEnd)
            {
                jumps++;
                currEnd = farthest;
            }
        }
        return jumps;
    }
};