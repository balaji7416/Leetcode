#include <bits/stdc++.h>
using namespace std;

/*
    Took me 3day's to solve and that too after
    knowing the approach
*/

/*
    Problem 1203: Sort Items by Groups Respecting Dependencies
    Pattern: Topological Sort
    Time: O(V+E), Space: O(V+E)
*/

/*
Approach:

This problem requires ordering items such that:
1) All dependency constraints are satisfied.
2) Items belonging to the same group appear together.

To achieve this, we model the problem as TWO separate DAGs
and perform topological sort on both levels.

------------------------------------------------------------
STEP 1: Normalize Groups
------------------------------------------------------------
Some items have group = -1 (no group).
We assign each such item a unique new group ID.
This ensures every item belongs to exactly one group.

------------------------------------------------------------
STEP 2: Build Two Graphs
------------------------------------------------------------

1) Item-level graph:
   - Standard dependency graph.
   - If item A must come before item B,
     add edge A → B.

2) Group-level graph:
   - If an item from group X depends on
     an item from group Y (X != Y),
     add edge Y → X in the group graph.
   - Use unordered_set to avoid duplicate edges.

------------------------------------------------------------
STEP 3: Topological Sort on Items
------------------------------------------------------------
- Perform Kahn’s algorithm (BFS-based topo).
- If we cannot process all items,
  there is a cycle → return empty.

This gives a valid global order of items
that respects all item-level dependencies.

------------------------------------------------------------
STEP 4: Topological Sort on Groups
------------------------------------------------------------
- Perform topo sort on the group graph.
- If we cannot process all groups,
  there is a cycle between groups → return empty.

This gives a valid order of groups.

------------------------------------------------------------
STEP 5: Bucket Items by Group (Preserving Item Order)
------------------------------------------------------------
- Traverse itemTopo in order.
- Place each item into its group bucket.
- This ensures:
    • item dependency order is preserved
    • items of same group stay together

------------------------------------------------------------
STEP 6: Build Final Answer
------------------------------------------------------------
- Traverse groups in groupTopo order.
- Append items from each group bucket.
- This ensures:
    • group order is valid
    • item order inside group is valid

------------------------------------------------------------
Time Complexity:
O(n + dependencies)

Space Complexity:
O(n + dependencies)

------------------------------------------------------------
Key Insight:
We separate dependency resolution into two levels:
items and groups.

Item topo ensures dependency correctness.
Group topo ensures grouping constraint.
Bucketing merges both constraints cleanly.
*/

class Solution
{
public:
    vector<int> sortItems(int n, int m, vector<int> &group,
                          vector<vector<int>> &beforeItems)
    {
        // make items graph
        vector<vector<int>> items(n);

        // assign a diff group for each element of -1 group (el does't belng any grp)
        int grp = m;
        for (int i = 0; i < n; i++)
        {
            if (group[i] == -1)
            {
                group[i] = grp;
                grp++;
            }
        }
        // make a group graph (use set to avoid dupl edges)
        vector<unordered_set<int>> groups(grp);
        // vector<vector<bool>> added(grp,vector<bool>(grp,false));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < beforeItems[i].size(); j++)
            {
                items[beforeItems[i][j]].push_back(i);
                // add edge between groups if items belonging to diff groups
                // depends
                int grp1 = group[beforeItems[i][j]], grp2 = group[i];
                if (grp1 != grp2)
                {
                    groups[grp1].insert(grp2);
                }
            }
        }

        // find the topo order of items
        vector<int> inDegree(n, 0);
        queue<int> q;
        for (int i = 0; i < n; i++)
        {
            for (auto v : items[i])
            {
                inDegree[v]++;
            }
        }
        for (int i = 0; i < n; i++)
        {
            if (inDegree[i] == 0)
                q.push(i);
        }
        vector<int> itemTopo;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto v : items[u])
            {
                inDegree[v]--;
                if (inDegree[v] == 0)
                {
                    q.push(v);
                }
            }
            itemTopo.push_back(u);
        }

        // if there's a cycle in item order
        if (itemTopo.size() < n)
            return {};

        // now find topo of groups #Note: grp -> new size of groups
        inDegree = vector<int>(grp, 0);
        for (int i = 0; i < grp; i++)
        {
            for (auto v : groups[i])
            {
                inDegree[v]++;
            }
        }
        for (int i = 0; i < grp; i++)
        {
            if (inDegree[i] == 0)
            {
                q.push(i);
            }
        }
        vector<int> groupTopo;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto v : groups[u])
            {
                inDegree[v]--;
                if (inDegree[v] == 0)
                {
                    q.push(v);
                }
            }
            groupTopo.push_back(u);
        }

        // if there's a cycle in group topo
        if (groupTopo.size() < grp)
            return {};

        /** create a bucket for groups:items & place each topo ordered items in
        their buckets this ensure the order of items in groups is preserved**/

        /*we can also use unordered_map<int,vector<int>> bucket; but for this
         * prob      vector is acceptable*/
        vector<vector<int>> bucket(grp);
        for (int i = 0; i < n; i++)
        {
            int el = itemTopo[i];
            bucket[group[el]].push_back(el);
        }

        // now place the group buckets in group topo order
        vector<int> ans;
        for (int i = 0; i < grp; i++)
        {
            int cgrp = groupTopo[i];
            for (int j = 0; j < bucket[cgrp].size(); j++)
            {
                ans.push_back(bucket[cgrp][j]);
            }
        }
        return ans;
    }
};