#include <bits/stdc++.h>
using namespace std;

/*
    Problem 752: Open the Lock
    Pattern: BFS
    Time: O(10^4), Space: O(10^4)
*/

/* idea
We treat each 4-digit lock state as a node in a graph.
From each state, we can generate 8 neighbors
(rotate each of the 4 wheels forward or backward).

We perform BFS starting from "0000":
- Use a queue to explore states level by level.
- Use `dist` map to track visited states and their distance.
- Skip states that are deadends or already visited.
- If we reach the target, return its distance.
- If BFS finishes without reaching target, return -1.

Since BFS explores in increasing order of moves,
the first time we reach target gives minimum moves.
*/

class Solution
{
public:
    int bfs(string target, unordered_set<string> &deadends, unordered_map<string, int> &dist)
    {
        queue<string> q;
        q.push("0000");
        dist["0000"] = 0;

        while (!q.empty())
        {
            string s = q.front();
            q.pop();
            if (s == target)
            {
                return dist[s];
            }
            for (int i = 0; i < 4; i++)
            {
                string temp = s;
                temp[i] = (s[i] - '0' + 1) % 10 + '0'; // increment
                // if it's not visited and not a deadend
                if (!dist.count(temp) && !deadends.count(temp))
                {
                    dist[temp] = dist[s] + 1;
                    q.push(temp);
                }
                temp[i] = (s[i] - '0' - 1 + 10) % 10 + '0';
                if (!dist.count(temp) && !deadends.count(temp))
                {
                    dist[temp] = dist[s] + 1;
                    q.push(temp);
                }
            }
        }
        return -1;
    }
    int openLock(vector<string> &deadends, string target)
    {
        unordered_map<string, int> dist;
        unordered_set<string> ends(deadends.begin(), deadends.end());

        if (ends.count("0000") || ends.count(target))
            return -1;
        return bfs(target, ends, dist);
    }
};