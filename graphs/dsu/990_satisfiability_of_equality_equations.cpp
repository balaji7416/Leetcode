#include <bits/stdc++.h>
using namespace std;

/*
    Problem 547: Number of Provinces
    Pattern: DSU / BFS / DFS
    Time: O(N), Space: O(26)
*/

/*
    Logic:
    - Use DSU to group variables connected by '=='.
    - Then check all '!=' equations:
        * If both variables are in same component → contradiction.
    - Return true if no contradiction.
*/

struct DSU
{
    int components;
    vector<int> parent, size;
    DSU(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        components = n;
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
        {
            swap(rootA, rootB);
        }
        parent[rootB] = rootA;
        size[rootA] += size[rootB];
        components--;
        return true;
    }
};
class Solution
{
public:
    bool equationsPossible(vector<string> &equations)
    {
        DSU dsu(26);
        for (auto s : equations)
        {
            int a = s[0] - 'a', b = s[3] - 'a';
            char op = s[1];
            if (op == '=')
            {
                dsu.unite(a, b);
            }
        }
        for (auto s : equations)
        {
            int a = s[0] - 'a', b = s[3] - 'a';
            char op = s[1];
            bool found = dsu.find(a) == dsu.find(b); // are they related by equality
            if (op == '!' && found)
            {
                return false;
            }
        }
        return true;
    }
};