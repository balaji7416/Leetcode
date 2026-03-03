#include <bits/stdc++.h>
using namespace std;

/*
    Problem 721: Accounts Merge
    Pattern: DSU + hashmaps + graph modelling
    Time: O(V+E), Space: O(V+E)
*/
/*
 #NOTE: it's a real beast, took a lot of time to solve
        that too with hints, but the bug that
*/
/* EXPLANATION:

Modeling:
- Each account index (0 to n-1) is treated as a DSU node.
- Emails are NOT DSU nodes; they act as connectors between accounts.
- If two accounts share at least one email, they belong to the same person.

Approach:
1) Build a DSU of size n (number of accounts).
2) Maintain a map: email -> first account index where it appeared.
3) While iterating accounts:
   - For every email:
       • If email seen before → union(current_account, previous_account).
       • Otherwise store email -> current_account.
   → This merges all accounts that share at least one email.

4) After unions are complete:
   - For each account i:
       • Find its root = dsu.find(i).
       • Group all its emails into bucket[root].
       • Store name[root] = accounts[i][0] (same for all in component).

5) For each root component:
   - Sort emails.
   - Remove duplicates using:
       vec.erase(unique(vec.begin(), vec.end()), vec.end());
   - Insert the person's name at the beginning.
   - Add to final answer.

DSU Nodes:
- Nodes represent account indices.
- DSU components represent one real person.
- Emails are only used to determine connectivity between accounts.

Time Complexity:
- Union phase: O(E * α(N))
- Grouping: O(E)
- Sorting emails per component: O(E log E)

Core Idea:
Connected components of accounts via shared emails.
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
    vector<vector<string>> accountsMerge(vector<vector<string>> &accounts)
    {
        int n = accounts.size();
        DSU dsu(n);
        unordered_map<string, int> mp;
        for (int i = 0; i < n; i++)
        {
            auto vec = accounts[i];
            for (int j = 1; j < vec.size(); j++)
            {
                if (mp.count(vec[j]))
                {
                    dsu.unite(i, mp[vec[j]]);
                }
                mp[vec[j]] = i;
            }
        }
        unordered_map<int, vector<string>> bucket;
        unordered_map<int, string> name;
        for (int i = 0; i < n; i++)
        {
            auto vec = accounts[i];
            int p = dsu.find(i);
            name[p] = vec[0];
            for (int j = 1; j < vec.size(); j++)
            {
                bucket[p].push_back(vec[j]);
            }
        }

        vector<vector<string>> ans;
        for (auto &[idx, vec] : bucket)
        {
            sort(vec.begin(), vec.end());
            vec.erase(unique(vec.begin(), vec.end()), vec.end());
            vec.insert(vec.begin(), name[idx]);
            ans.push_back(vec);
        }
        return ans;
    }
};