#include <bits/stdc++.h>
using namespace std;

/*
    Problem 202: Happy Number
    Pattern: Hashmap / floyd cycle detection
    Time: O(n), Space: O(n)
*/

/*
    idea1: hashmap
        use hashmap to store already visited numbers
        and if cycle is detected then return false

    idea2: floyd cycle detection
        use 2 pointers
        slow = nums[slow]
        fast = nums[nums[fast]]
        if cycle is detected then return false
*/

/* Solution 1
class Solution
{
public:
    bool isHappy(int n)
    {
        unordered_set<int> visited;
        while (n != 1)
        {
            if (visited.count(n))
            {
                return false;
            }
            visited.insert(n);
            int ref = 0;
            while (n > 0)
            {
                ref += (n % 10) * (n % 10);
                n /= 10;
            }
            n = ref;
        }
        return true;
    }
};
*/

/* Solution 2 */
class Solution
{
public:
    int next(int n)
    {
        int sum = 0;
        while (n > 0)
        {
            int r = n % 10;
            sum += r * r;
            n /= 10;
        }
        return sum;
    }
    bool isHappy(int n)
    {
        int slow = n, fast = n;
        do
        {
            slow = next(slow);
            fast = next(next(fast));
        } while (slow != fast);
        return slow == 1;
    }
};