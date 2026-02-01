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

    consider the example [2,1,3,4]

    stack after first iteration :
    |   |
    |---|
    |   |
    |---|
    |   |
    |_0_|

    stack in second iteration :
    here i = 1 and arr[i] = 1 < arr[i-1] = 2; so the height for the bar will be arr[s.top()] = 2;
    and it's width will be the difference between the current index and the next smaller index than
    s.top(). if the stack is empty, then the index we consider will be -1 which aligns with the
    correctness of the algorithm.

    |   |
    |---|
    |   |
    |---|
    |   |
    |___|
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