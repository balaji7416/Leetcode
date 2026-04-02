#include <bits/stdc++.h>
using namespace std;

/*
    Problem 29: Divide Two Integers
    Pattern: Math
    Time: O(logn*logn), Space: O(1)
*/

/* IDEA:
    Divide Two Integers (without /, *, %)

    IDEA:
    - Perform division using binary exponential subtraction.
    - Instead of subtracting divisor one-by-one, repeatedly subtract
      the largest power-of-2 multiple of divisor that fits into dividend.

    APPROACH:
    1. Handle overflow case:
        INT_MIN / -1 → exceeds INT_MAX → return INT_MAX.

    2. Convert dividend and divisor to positive long long values
       to avoid overflow (especially for INT_MIN).

    3. While dividend >= divisor:
        - Find largest k such that (divisor << k) <= dividend.
        - Subtract (divisor << k) from dividend.
        - Add (1 << k) to answer.
      (This mimics binary long division.)

    4. Apply sign at the end using XOR:
        result is negative if signs of inputs differ.

    5. Return result (fits in int due to constraints).

    TIME COMPLEXITY:
    - O(log^2 N) (outer loop + inner doubling loop)

    KEY LEARNINGS:
    - Always cast to long long BEFORE taking abs of INT_MIN.
    - Use long long for intermediate calculations to avoid overflow.
    - Bit shifting (<<) is equivalent to multiplying by powers of 2.
    - Greedy + bit manipulation can optimize repeated subtraction.
    - XOR is a clean way to determine sign difference.
    - Be careful: overflow can happen BEFORE final result is assigned.

    CORE INSIGHT:
    - This is essentially binary long division using bit manipulation.
*/

class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        if (dividend == INT_MIN && divisor == -1)
            return INT_MAX;
        long long dvd = llabs(dividend);
        long long div = llabs(divisor);
        long long ans = 0;
        while (dvd >= div)
        {
            long long temp = div, i = 0;
            while (dvd >= (temp << 1))
            {
                temp <<= 1;
                i++;
            }
            ans += (1 << i);
            dvd -= temp;
        }
        if ((divisor < 0) ^ (dividend < 0))
        {
            ans = -ans;
        }
        return ans;
    }
};