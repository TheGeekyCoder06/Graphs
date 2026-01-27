#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Solution {
public:
    int findCity(int n, int m, vector<vector<int>>& edges, int distanceThreshold) {
        
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

        // Build graph
        for (auto &it : edges) {
            int u = it[0];
            int v = it[1];
            int w = it[2];
            dist[u][v] = w;
            dist[v][u] = w;
        }

        for (int i = 0; i < n; i++) 
            dist[i][i] = 0;

        // Floyd Warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        int cntCity = INT_MAX;
        int cityNo = -1;

        for (int city = 0; city < n; city++) {
            int cnt = 0;
            for (int adjCity = 0; adjCity < n; adjCity++) {
                if (city != adjCity && dist[city][adjCity] <= distanceThreshold) {
                    cnt++;
                }
            }
            // If tie, we pick the city with greater index
            if (cnt <= cntCity) {
                cntCity = cnt;
                cityNo = city;
            }
        }

        return cityNo;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> edges(m, vector<int>(3));
    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    int distanceThreshold;
    cin >> distanceThreshold;

    Solution obj;
    int ans = obj.findCity(n, m, edges, distanceThreshold);

    cout << "City with smallest reachable neighbors: " << ans << endl;

    return 0;
}
