#include <bits/stdc++.h>
using namespace std;

/*
    Problem 862: Shortest Subarray with Sum at Least K
    Pattern: deque, prefixsum
    Time: O(n), Space: O(n)
*/

/*
    idea: prefixsum + deque
    prefix[r+1]-prefix[l] >= k
    1.iterate r from 0 to n
    2.keep track of min l in queue
    3.check if prefix[r+1]-prefix[l] >= k
*/

class Solution
{
public:
    int shortestSubarray(vector<int> &nums, int k)
    {
        int ans = INT_MAX;
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);

        for (int i = 1; i <= n; i++)
        {
            prefix[i] = prefix[i - 1] + nums[i - 1];
        }
        deque<int> dq;
        for (int i = 0; i <= n; i++)
        {
            while (!dq.empty() && prefix[i] - prefix[dq.front()] >= k)
            {
                ans = min(ans, i - dq.front());
                dq.pop_front();
            }
            while (!dq.empty() && prefix[i] <= prefix[dq.back()])
            {
                dq.pop_back();
            }
            dq.push_back(i);
        }
        return (ans == INT_MAX ? -1 : ans);
    }
};