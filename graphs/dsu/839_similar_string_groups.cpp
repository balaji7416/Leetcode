#include <bits/stdc++.h>
using namespace std;

/*
    Problem 839: Similar String Groups
    Pattern: DSU
    Time: O(n^2 * m), Space: O(n)
*/
/*
Modeling:
- Each string index (0 to n-1) is treated as a DSU node.
- If two strings are similar, we connect their indices.
- Final answer = number of connected components in DSU.

Similarity Logic:
- Two strings are similar if:
    • They are identical (0 mismatches), OR
    • They differ in exactly 2 positions (one swap makes them equal).
- Since all strings are anagrams (problem guarantee),
  checking mismatch count <= 2 is sufficient.

Approach:
1) Initialize DSU with n nodes (one per string).
2) For every pair (i, j), i < j:
    - Check if strs[i] and strs[j] are similar.
    - If yes → dsu.unite(i, j).
3) After processing all pairs,
   DSU.components represents number of similar groups.

DSU Nodes:
- Each node represents one string.
- Each DSU component represents one connected group of similar strings.

Time Complexity:
- Pairwise comparison: O(n^2)
- Similarity check per pair: O(m)
- Overall: O(n^2 * m)

Core Idea:
Build an implicit graph where edges exist between similar strings.
Then count connected components using DSU.
*/
struct DSU
{
    int components;
    vector<int> parent, size;
    DSU(int n)
    {
        components = n;
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = find(parent[x]);
    }
    bool unite(int x, int y)
    {
        int rootA = find(x), rootB = find(y);
        if (rootA == rootB)
            return false;
        if (size[rootA] < size[rootB])
            swap(rootA, rootB);
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
        components--;
        return true;
    }
};
class Solution
{
public:
    int numSimilarGroups(vector<string> &strs)
    {
        int n = strs.size();
        DSU dsu(n);
        auto areSimilar = [&](string &a, string &b)
        {
            int c = 0;
            for (int i = 0; i < a.size(); i++)
            {
                if (a[i] != b[i])
                    c++;
            }
            return c <= 2;
        };
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (areSimilar(strs[i], strs[j]))
                {
                    dsu.unite(i, j);
                }
            }
        }
        return dsu.components;
    }
};