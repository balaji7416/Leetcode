#include <bits/stdc++.h>
using namespace std;

/*
    Problem 1334: Find the City With the Smallest Number of Neighbors at a Threshold Distance
    Pattern: Floyd Warshall
    Time: O(n^3) space: O(n^2)
*/

/* Logic:
    - Build adjacency matrix.
    - Run floyd's algorithm.
    - check how many cities have distance <= threshold. take the smallest one.
*/

class Solution
{
public:
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
    {
        const int inf = INT_MAX;
        vector<vector<int>> dist(n, vector<int>(n, inf));
        for (int i = 0; i < n; i++)
        {
            dist[i][i] = 0;
        }
        for (auto e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            dist[u][v] = min(dist[u][v], w);
            dist[v][u] = min(dist[v][u], w);
        }

        // run floyd warshall
        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (dist[i][k] == inf || dist[k][j] == inf)
                        continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        // now count the no.of valid cities each city can reach
        int min_cities = INT_MAX;
        int city = -1;
        for (int i = 0; i < n; i++)
        {
            int c = 0;
            for (int j = 0; j < n; j++)
            {
                if (i != j && dist[i][j] <= distanceThreshold)
                    c++;
            }
            if (c <= min_cities)
            {
                min_cities = c;
                city = i;
            }
        }
        return city;
    }
};