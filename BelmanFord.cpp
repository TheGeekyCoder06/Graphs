#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> dist(V, 1e8);
        dist[src] = 0;

        // Relax edges V-1 times
        for(int i = 0; i < V - 1; i++) {
            for(auto it : edges) {
                int u = it[0];
                int v = it[1];
                int wt = it[2];

                if(dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Check for negative weight cycle
        for(auto it : edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            if(dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1}; // Negative cycle detected
            }
        }

        return dist;
    }
};

int main() {
    Solution obj;

    int V = 5; // number of vertices
    vector<vector<int>> edges = {
        {0, 1, 5},
        {1, 2, -2},
        {1, 3, 3},
        {2, 4, 3},
        {3, 4, -1}
    };

    int src = 0;

    vector<int> result = obj.bellmanFord(V, edges, src);

    if(result.size() == 1 && result[0] == -1) {
        cout << "Negative weight cycle detected\n";
    } else {
        cout << "Shortest distances from source " << src << ":\n";
        for(int i = 0; i < result.size(); i++) {
            cout << "Node " << i << " : " << result[i] << endl;
        }
    }

    return 0;
}
