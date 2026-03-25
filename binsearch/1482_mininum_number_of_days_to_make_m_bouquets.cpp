#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1482: Minimum Number of Days to Make m Bouquets
    Pattern: Binary Search
    Time: O(nlogn), Space: O(1)
*/

/* IDEA:
Binary search on answer (day):

- Search the minimum day such that we can form >= m bouquets.
- For a given day (mid), greedily scan bloomDay:
    - Count consecutive flowers with bloomDay[i] <= mid.
    - Each time count reaches k, form one bouquet and reset count.
    - If a flower > mid appears, reset count (break in continuity).
- If we can form >= m bouquets → mid is valid, try smaller day.
- Else → need more days, move right.

Time: O(n * log(max_day))
*/
class Solution
{
public:
    int minDays(vector<int> &bloomDay, int m, int k)
    {
        int n = bloomDay.size();
        int min_el = INT_MAX, max_el = INT_MIN;
        for (int _ : bloomDay)
        {
            min_el = min(min_el, _);
            max_el = max(max_el, _);
        }
        int low = min_el, high = max_el;
        int ans = -1;

        auto is_valid = [&](int mid)
        {
            int bq = 0;
            int cnt = 0;
            for (int i = 0; i < n; i++)
            {
                if (bloomDay[i] <= mid)
                {
                    cnt++;
                    if (cnt == k)
                    {
                        bq++;
                        cnt = 0;
                    }
                }
                else
                {
                    cnt = 0;
                }
            }
            return bq >= m;
        };

        while (low <= high)
        {
            int mid = low + (high - low) / 2;
            if (is_valid(mid))
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