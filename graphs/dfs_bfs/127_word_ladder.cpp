#include <bits/stdc++.h>
using namespace std;

/*
    Problem 127: Word Ladder
    Pattern: BFS
    Time: O(N*L*26), Space: O(N)
*/

/* idea: first idea of mine
    same as bfs
    but is_neighbor function is used to check
    all the words in wordList whether they are neighbors
    which is O(N), N -> no.of words in WordList
    which is done in O(26*L) in efficient method
    L -> len of each word
*/

/** idea: optimal O(N*L*26)
     LOGIC:
     BFS shortest path in unweighted graph where:
     - Nodes: words (beginWord + all words in wordList)
     - Edges: between words that differ by exactly 1 character
     - BFS ensures first time we reach endWord is minimum steps

     Instead of pre-building graph, generate neighbors on-the-fly:
     For current word, try changing each position to every letter 'a'-'z'
     If generated word exists in dictionary & unvisited, add to queue

     - BFS visits each word once: O(N) where N = number of words
     - For each word, try 26 × L neighbors (L = word length)
     - Each neighbor check is O(1) hash lookup
     - is_neighbor function NOT used in main BFS! (it's leftover)

     ACTUAL TIME: O(N × 26 × L) ≈ O(N × L) since 26 constant
     - N = number of words in wordList
     - L = length of each word

     SPACE: O(N) for queue + hash sets/maps
**/

class Solution
{
public:
    // bool is_neighbor(string &a, string &b)
    // {
    //     int diff = 0;
    //     for (int i = 0; i < a.size(); i++)
    //     {
    //         if (a[i] != b[i])
    //             diff++;
    //         if (diff > 1)
    //             return false;
    //     }
    //     return diff == 1;
    // }
    int ladderLength(string beginWord, string endWord,
                     vector<string> &wordList)
    {
        unordered_set<string> words(wordList.begin(), wordList.end());
        unordered_map<string, int> dist;

        if (!words.count(endWord))
            return 0;

        queue<string> q;
        q.push(beginWord);
        dist[beginWord] = 1;
        while (!q.empty())
        {
            string s = q.front();
            q.pop();
            if (s == endWord)
                return dist[s];
            for (int i = 0; i < s.size(); i++)
            {
                char original = s[i];
                for (char c = 'a'; c <= 'z'; c++)
                {
                    if (c == original)
                        continue;
                    string neighbor = s;
                    neighbor[i] = c;
                    if (!dist.count(neighbor) && words.count(neighbor))
                    {
                        dist[neighbor] = 1 + dist[s];
                        // if(neighbor == endWord) return dist[neighbor]; (early return)
                        q.push(neighbor);
                    }
                }
            }
        }
        return 0;
    }
};