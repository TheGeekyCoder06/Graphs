#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) {

        int n = grid.size();
        int m = grid[0].size();

        // If source or destination is blocked
        if (grid[source.first][source.second] == 0 ||
            grid[destination.first][destination.second] == 0)
            return -1;

        // If source is the same as destination
        if (source == destination) return 0;

        queue<pair<int, pair<int, int>>> q;
        vector<vector<int>> dist(n, vector<int>(m, 1e9));

        dist[source.first][source.second] = 0;
        q.push({0, {source.first, source.second}});

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!q.empty()) {
            auto it = q.front();
            q.pop();

            int dis = it.first;
            int row = it.second.first;
            int col = it.second.second;

            for (int i = 0; i < 4; i++) {
                int nrow = row + dr[i];
                int ncol = col + dc[i];

                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m &&
                    grid[nrow][ncol] == 1 && dis + 1 < dist[nrow][ncol]) {

                    if (nrow == destination.first && ncol == destination.second)
                        return dis + 1;

                    dist[nrow][ncol] = dis + 1;
                    q.push({dis + 1, {nrow, ncol}});
                }
            }
        }

        return -1;
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    int sx, sy, dx, dy;
    cin >> sx >> sy;
    cin >> dx >> dy;

    Solution obj;
    int ans = obj.shortestPath(grid, {sx, sy}, {dx, dy});

    cout << ans << endl;

    return 0;
}
