#include <bits/stdc++.h>
using namespace std;

/*
    Problem 135: Candy
    Pattern: Greedy
    Time: O(n), Space: O(n)
*/

/* INSIGHT: constraints from both sides → solve in two passes
Greedy idea:

Each child must have:
1) At least 1 candy
2) More candies than neighbors with lower rating

We handle constraints in two passes:

1) Left → Right:
   If ratings[i] > ratings[i-1],
   ensure candies[i] = candies[i-1] + 1
   (satisfies left neighbor condition)

2) Right → Left:
   If ratings[i] > ratings[i+1],
   ensure candies[i] = max(current, candies[i+1] + 1)
   (satisfies right neighbor condition without breaking left)

Finally, sum all candies.

Time: O(n), Space: O(n)
*/

class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        int n = ratings.size();
        vector<int> candies(n, 1);

        // assingn for left->right
        for (int i = 1; i < n; i++)
        {
            if (ratings[i] > ratings[i - 1])
            {
                candies[i] = candies[i - 1] + 1;
            }
        }

        // assign for right->left
        for (int i = n - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                candies[i] = max(candies[i], candies[i + 1] + 1);
            }
        }

        return accumulate(candies.begin(), candies.end(), 0);
    }
};