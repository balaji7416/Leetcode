#include <bits/stdc++.h>
using namespace std;

/*
    Problem 583: Delete Operation for Two Strings
    Pattern: dp
    Time: O(m*n), Space: O(m*n)
*/

/*
    f(i,j) => min del operaions needed to make string word1[i:] equal to word2[j:]
    base cases:
        if(word1 empty) return size of word2
        if(word2 empty) return size of word1
    dp[i][j] = min del operations needed to make string word1[i:] equal to word2[j:]

    similar to edit distance problem
*/
class Solution
{
public:
    int solve(int i, int j, string &word1, string &word2, vector<vector<int>> &dp)
    {
        if (i == word1.size())
        {
            return word2.size() - j;
        }
        if (j == word2.size())
        {
            return word1.size() - i;
        }
        // if memorized
        if (dp[i][j] != -1)
            return dp[i][j];

        if (word1[i] == word2[j])
        {
            return dp[i][j] = solve(i + 1, j + 1, word1, word2, dp);
        }
        return dp[i][j] = 1 + min(
                                  solve(i + 1, j, word1, word2, dp),  // delete char in word1
                                  solve(i, j + 1, word1, word2, dp)); // delete char in word2
    }
    int minDistance(string word1, string word2)
    {
        int n = word1.size();
        int m = word2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(0, 0, word1, word2, dp);
    }
};