#include <bits/stdc++.h>
using namespace std;

/*
    Problem 72: Edit Distance
    Pattern: dp + recursion
    Time: O(m*n), Space: O(m*n)
*/

/*
    idea:
        dp[i][j] = min operations needed to convert word1[0..i] to word2[0..j]
        edit distance = minimum number of operations needed to convert word1 to word2
        possible operations: insert, delete, replace
        insert -> solve(i,j-1) + 1;
            because lets say word1[i] != word2[j], then we insert
            word2[j] at end of word1[0..i] to make word1[0..i+1] = word2[0..j]
            then since word1[i+1] == word2[j], we recurse like for match case solve(i+1-1,j-1) => solve(i,j-1)
        delete -> solve(i-1,j) + 1
            because lets say word1[i] != word2[j], then we delete
            word1[i] from word1[0..i] and then recurse to find the edit distance between word1[0..i-1] and word2[0..j]
        replace -> solve(i-1,j-1) + 1
            because lets say word1[i] != word2[j], then we replace
            word1[i] with word2[j] and then recurse to find the edit distance between word1[0..i-1] and word2[0..j-1]
        i used top to bottom dp
*/

class Solution
{
public:
    int solve(int i, int j, string &word1, string &word2,
              vector<vector<int>> &dp)
    {
        // insert remaining all chars of word2[0..j]
        if (i < 0)
            return j + 1;

        // delete remaining all chars of word1[0..i]
        if (j < 0)
            return i + 1;

        // if memorized
        if (dp[i][j] != -1)
            return dp[i][j];

        // if match
        if (word1[i] == word2[j])
            return dp[i][j] = solve(i - 1, j - 1, word1, word2, dp);

        return dp[i][j] =
                   1 + min({
                           solve(i, j - 1, word1, word2, dp),     // insert
                           solve(i - 1, j, word1, word2, dp),     // delete
                           solve(i - 1, j - 1, word1, word2, dp), // replace
                       });
    }
    int minDistance(string word1, string word2)
    {
        int n = word1.size(), m = word2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solve(n - 1, m - 1, word1, word2, dp);
    }
};