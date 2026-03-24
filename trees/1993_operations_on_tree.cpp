#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1993: Operations on Tree
    Pattern: DFS
    Time: O(n), Space: O(n)
    lock - O(1)
    unlock - O(1)
    upgrade - O(subtree size)
*/

/*
Approach 1 (Implemented - DFS based):

We maintain a map (node → user) to track locked nodes.

Operations:
1) lock(num, user):
   - Lock node if it's currently unlocked.

2) unlock(num, user):
   - Unlock only if the same user locked it.

3) upgrade(num, user):
   - Conditions:
     a) num must be unlocked
     b) no locked ancestor (walk up using parent[])
     c) at least one locked descendant (DFS check)
   - If valid:
     → DFS the subtree and unlock all descendants
     → lock the current node

Time:
- upgrade = O(subtree size) due to DFS


--------------------------------------------------

Approach 2 (Optimized - Euler Tour + Fenwick Tree) [Overkill]:

Idea:
- Flatten tree using Euler Tour:
    subtree of node u → contiguous range [tin[u], tout[u]]
- Use Fenwick Tree to store:
    1 → locked, 0 → unlocked

Then:
- Check locked descendants in O(log n) using range sum
- lock/unlock in O(log n)
- upgrade:
    → check conditions in O(log n)
    → unlock subtree by iterating range (or optimize further)

Insight:
- Converts tree problem → range query problem

Used when constraints are large / need faster subtree queries.
*/

class LockingTree
{
public:
    vector<int> parent;
    vector<int> child;
    vector<vector<int>> adj;
    int n;
    // vector<vector<int>> Locked(n,vector<int>)
    unordered_map<int, int> Lock;
    LockingTree(vector<int> &parent)
    {
        this->parent = parent;
        this->n = parent.size();
        adj.resize(n);
        for (int i = 1; i < n; i++)
        {
            adj[i].push_back(parent[i]);
            adj[parent[i]].push_back(i);
        }
    }

    bool lock(int num, int user)
    {
        if (!Lock.count(num))
        {
            Lock[num] = user;
            return true;
        }
        return false;
    }

    bool unlock(int num, int user)
    {
        if (Lock.count(num) && Lock[num] == user)
        {
            Lock.erase(num);
            return true;
        }
        return false;
    }

    bool upgrade(int num, int user)
    {
        // 1. node shouldn't be Locked
        if (Lock.count(num))
            return false;

        // 3. it doesn't have any Locked ancestors
        int u = num;
        while (u != -1)
        {
            if (Lock.count(u))
            {
                return false;
            }
            u = parent[u];
        }

        // 2. it has atleast one Locked descendant
        auto dfs = [&](auto &&self, int u, int p) -> bool
        {
            if (Lock.count(u))
            {
                return true;
            }
            for (int v : adj[u])
            {
                if (v == p)
                    continue;
                if (self(self, v, u))
                {
                    return true;
                }
            }
            return false;
        };

        if (!dfs(dfs, num, parent[num]))
        {
            return false;
        }

        // if 3 conditions met then, unLock all its descendants and Lock the node
        auto dfs_ = [&](auto &&self, int u, int p) -> void
        {
            for (int v : adj[u])
            {
                if (v == p)
                    continue;
                if (Lock.count(v))
                {
                    Lock.erase(v);
                }
                self(self, v, u);
            }
        };
        dfs_(dfs_, num, parent[num]);
        Lock[num] = user;
        return true;
    }
};

/**
 * Your LockingTree object will be instantiated and called as such:
 * LockingTree* obj = new LockingTree(parent);
 * bool param_1 = obj->Lock(num,user);
 * bool param_2 = obj->unLock(num,user);
 * bool param_3 = obj->upgrade(num,user);
 */