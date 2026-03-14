#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1011: Capacity To Ship Packages Within D Days
    Pattern: Binary Search
    Time: O(nlogn), Space: O(1)
*/

/*
    Binary Search on Answer.

    The minimum ship capacity must lie between:
    - max(weights)  -> ship must carry the heaviest package
    - sum(weights)  -> ship carries everything in one day

    For a candidate capacity 'cap', simulate loading packages greedily.
    If adding a package exceeds 'cap', ship the current load and start a new day.

    Count the days required:
    - if days_required <= given days -> capacity works, try smaller
    - else -> capacity too small, increase it

    Time: O(N log(sum(weights)))
*/

class Solution
{
public:
    int shipWithinDays(vector<int> &weights, int days)
    {
        int n = weights.size();

        // bin search on weight capacity for minm weight
        //  int low = *max_element(weights.begin(),weights.end());
        //  int high = accumulate(weights.begin(),weights.end(),0);
        int max_el = 0, sum = 0;
        for (int w : weights)
        {
            max_el = max(max_el, w);
            sum += w;
        }
        int low = max_el, high = sum;
        int ans = high;
        /*my first check func
        auto isValid = [&](int cap){
            int dr = 0, w = 0, i = 0;
            while(i < n){
                if(weights[i] > cap) return false;
                int new_w = w + weights[i];
                if(new_w ==  cap){
                    dr++; w = 0; i++;

                } else if(new_w > cap){
                    dr++; w = 0;
                } else{
                    w += weights[i]; i++;
                }
            }
            if(w != 0) dr++;
            return dr <= days;
        };*/

        /*more readable one*/
        auto isValid = [&](int cap)
        {
            int days_req = 1;
            int curr = 0;
            for (int w : weights)
            {
                if (curr + w > cap)
                {
                    days_req++;
                    curr = 0;
                }
                curr += w;
            }
            return days_req <= days;
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