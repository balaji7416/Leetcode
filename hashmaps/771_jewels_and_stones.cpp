#include <bits/stdc++.h>
using namespace std;

/*
    Problem 771: Jewels and Stones
    Pattern: Hashmap / visited array
    Time: O(n), Space: O(n)
*/

/*
    idea:
        create visited array of size 128 to mark visited chars
            in c++ char are stored as integers 'a' = 97, 'A' = 65
            so 128 array size is safe bound for all chars

        you could also use a hashset but it adds hashing overhead and slower than visited array
        for each char in stones, if it is in jewels, add to ans
*/

class Solution
{
public:
    int numJewelsInStones(string jewels, string stones)
    {
        // unordered_set<int> st(jewels.begin(),jewels.end());
        int visited[128] = {0};
        for (auto c : jewels)
        {
            visited[c] = 1;
        }
        int ans = 0;
        for (auto el : stones)
        {
            if (visited[el])
            {
                ans++;
            }
        }
        return ans;
    }
};