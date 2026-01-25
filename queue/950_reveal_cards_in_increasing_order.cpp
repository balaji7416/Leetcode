#include <bits/stdc++.h>
using namespace std;

/*
    Problem 950: Reveal Cards In Increasing Order
    data structure: deque
    Time: O(n), Space: O(n)
*/

/*
    idea: deque + reverse simulation
*/

class Solution
{
public:
    vector<int> deckRevealedIncreasing(vector<int> &deck)
    {
        deque<int> dq1, dq2;
        sort(deck.begin(), deck.end());
        for (auto i : deck)
        {
            dq2.push_back(i);
        }
        while (!dq2.empty())
        {
            if (!dq1.empty())
            {
                int b = dq1.back();
                dq1.pop_back();
                dq1.push_front(b);
            }
            int b = dq2.back();
            dq2.pop_back();
            dq1.push_front(b);
        }
        vector<int> ans;
        while (!dq1.empty())
        {
            ans.push_back(dq1.front());
            dq1.pop_front();
        }
        return ans;
    }
};
