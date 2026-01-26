#include <bits/stdc++.h>
using namespace std;

/*
    Problem 258: Add Digits
    Pattern: Recursion
    Time: O(logn), Space: O(logn)
*/

/*
    idea: recursion
*/
class Solution
{
public:
    int addDigits(int num)
    {
        if (num % 10 == num)
            return num;
        return addDigits(num % 10 + addDigits(num / 10));
    }
};