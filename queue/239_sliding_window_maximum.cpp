#include <bits/stdc++.h>
using namespace std;

/*
    Problem 239: Sliding Window Maximum
    Pattern: deque, monotonic queue(decreasing order from front to back)
    Time: O(n), Space: O(n)
*/

/*
    idea: monotonic decreasing queue
    1. remove out of window indexes to make sure all elements present are in current window
    2. remove those indexes which can never be the maximum of current window
    3. record valid answers after k-1 iterations(window starts)
*/

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        deque<int> dq;
        vector<int> ans;
        for (int i = 0; i < n; i++)
        {
            // remove out of window indexes to make sure all elements present are in current window
            if (!dq.empty() && dq.front() <= i - k)
            {
                dq.pop_front();
            }

            // remove invalid candidates
            while (!dq.empty() && nums[dq.back()] < nums[i])
            {
                dq.pop_back();
            }
            dq.push_back(i);

            // record valid answers
            if (i >= k - 1)
            {
                ans.push_back(nums[dq.front()]);
            }
        }
        return ans;
    }
};