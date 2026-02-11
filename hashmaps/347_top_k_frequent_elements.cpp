#include <bits/stdc++.h>
using namespace std;

/*
    Problem 347: Top K Frequent Elements
    Pattern: Hashmap + Bucket Sort/ Priority Queue
             or Hashmap + full sort
    Time: O(n), Space: O(n)
*/

/*
Top K Frequent Elements – Current Approach

1. Use a HashMap to count frequency of each number.
   (number -> frequency)

2. Transfer map entries into a vector of (number, frequency) pairs.

3. Sort the vector in descending order based on frequency.

4. Take the first k elements from the sorted vector.

Core Idea:
- HashMap stores frequency memory.
- Sorting arranges elements by importance (frequency).
- First k elements after sorting are the top k frequent.
*/

class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> count;
        for (auto el : nums)
        {
            count[el]++;
        }
        vector<pair<int, int>> store;
        for (auto [key, val] : count)
        {
            store.push_back({key, val});
        }
        sort(store.begin(), store.end(), [](pair<int, int> &p1, pair<int, int> &p2)
             { return p1.second > p2.second; });
        vector<int> ans;
        for (int i = 0; i < k; i++)
        {
            ans.push_back(store[i].first);
        }
        return ans;
    }
};