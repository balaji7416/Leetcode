#include <bits/stdc++.h>
using namespace std;

/*
    Problem 84: Largest Rectangle in Histogram
    Pattern: Monotonic Stack
    Time: O(n), Space: O(n)
*/

/*
    idea:
    finding the left and right bounds for every bar where the bar is the smallest,
    optimise using stack, use sentinal value (pushing 0) for handling the edge cases
*/

class Solution
{
public:
    int largestRectangleArea(vector<int> &heights)
    {
        stack<int> s;
        int max_area = 0;
        heights.push_back(0);
        for (int i = 0; i < heights.size(); i++)
        {
            while (!s.empty() && heights[i] < heights[s.top()])
            {
                int height = heights[s.top()];
                s.pop();
                int width = i - (s.empty() ? -1 : s.top()) - 1;
                max_area = max(max_area, height * width);
            }
            s.push(i);
        }
        return max_area;
    }
};