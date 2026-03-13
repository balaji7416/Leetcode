#include <bits/stdc++.h>
using namespace std;

/*
    Problem 875: Koko Eating Bananas
    Pattern: Binary Search
    Time: O(nlogn), Space: O(1)
*/
/*Idea:
Binary Search on Answer.

Search space: possible eating speeds [1, max(pile)].

Observation:
If Koko can finish all bananas with speed = k in ≤ h hours,
then any speed > k will also work. This creates a monotonic pattern:

speed →   1 2 3 4 5 ...
valid? →  F F F T T ...

So we binary search for the smallest speed k such that
total_hours_needed(k) ≤ h.

For a pile p, hours needed = ceil(p / k).
To avoid floating point:
ceil(p/k) = (p + k - 1) / k.

For each candidate speed (mid), compute total hours required.
If it's ≤ h, this speed works → try smaller speed.
Otherwise → increase speed.

Time Complexity: O(n log max(pile))
*/

class Solution
{
public:
    int minEatingSpeed(vector<int> &piles, int h)
    {
        int n = piles.size();
        int max_b = *max_element(piles.begin(), piles.end());
        int low = 1, high = max_b;
        int ans = high;
        auto isValid = [&](int k)
        {
            long long tr = 0; // time required to eat all bananas in all piles
            for (auto p : piles)
            {
                tr += (p + k - 1) / k;
                // if(tr > h) return false; //optimization
            }
            return tr <= h;
        };
        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (isValid(mid))
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