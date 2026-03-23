#include <bits/stdc++.h>
using namespace std;

/*
    Problem 307: Range Sum Query - Mutable
    Pattern: Segment Tree
    Time: O(logn), Space: O(n)
*/

/* Core idea (Fenwick Tree / BIT):

- BIT stores partial prefix sums in a compressed way.
- Each index i is responsible for a range of size (i & -i).

Operations:
1. Build:
   For each element, propagate its value to all responsible BIT nodes.

2. Update(index, val):
   - Compute diff = new_val - old_val
   - Add diff to all BIT nodes that cover this index

3. Prefix Sum (sum(i)):
   - Keep jumping to parent nodes (i -= i & -i)
   - Accumulate contributions → gives sum [0..i]

4. Range Sum:
   sum(l, r) = sum(r) - sum(l-1)

Time:
- update: O(log n)
- query: O(log n)
*/

class NumArray
{
public:
    vector<int> bit;
    int n;
    vector<int> nums;
    NumArray(vector<int> &nums)
    {
        this->nums = nums;
        this->n = nums.size();
        bit.assign(n + 1, 0);

        // build the bit (init)
        for (int i = 0; i < n; i++)
        {
            int idx = i + 1;
            while (idx <= n)
            {
                bit[idx] += nums[i];
                idx += (idx & -idx);
            }
        }
    }

    void update(int index, int val)
    {
        index++;
        int diff = val - nums[index - 1];
        nums[index - 1] = val;
        while (index <= n)
        {
            bit[index] += diff;
            index += (index & -index);
        }
    }

    int sum(int i)
    {
        i++;
        int s = 0;
        while (i > 0)
        {
            s += bit[i];
            i -= (i & -i);
        }
        return s;
    }

    int sumRange(int left, int right)
    {
        if (left > right)
            return 0;
        return sum(right) - (left ? sum(left - 1) : 0);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */