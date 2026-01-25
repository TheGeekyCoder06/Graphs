#include <iostream>
#include <vector>
using namespace std;

const long long INF = 1e15;

void floydWarshall(vector<vector<long long>> &dist) {
    int n = dist.size();

    // Floyd–Warshall Algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] < INF && dist[k][j] < INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Negative cycle detection
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            cout << "Graph contains a negative weight cycle\n";
            return;
        }
    }

    cout << "Shortest distance matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int n = 4; // number of vertices

    vector<vector<long long>> dist = {
        {0,   3,   INF, 5},
        {2,   0,   INF, 4},
        {INF, 1,   0,   INF},
        {INF, INF, 2,   0}
    };

    floydWarshall(dist);

    return 0;
}
