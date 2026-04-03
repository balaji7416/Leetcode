#include <bits/stdc++.h>
using namespace std;

/*
    Problem 134: Gas Station
    Pattern: Greedy
    Time: O(n), Space: O(1)
*/
/*
Greedy idea:

Treat each station as net gain: diff = gas[i] - cost[i].

1) If total sum of diff < 0 → impossible to complete the circle (return -1).

2) Traverse once, maintaining current tank (curr).
 - If curr becomes negative at index i, it means starting from current 'start'
   cannot reach i.
 - Moreover, any station between start and i also cannot be a valid start
   (they would start with even less fuel).
 - So, reset:
      start = i + 1
      curr = 0

3) After one pass, if total >= 0, 'start' is the valid starting index.

Time: O(n), Space: O(1)
*/

class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int n = gas.size();
        int curr = 0, total = 0, start = 0;
        for (int i = 0; i < n; i++)
        {
            int diff = gas[i] - cost[i];
            total += diff;
            curr += diff;
            if (curr < 0)
            {
                start = i + 1;
                curr = 0;
            }
        }
        return total < 0 ? -1 : start;
    }
};