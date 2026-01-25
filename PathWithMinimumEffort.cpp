#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <climits>

using namespace std;

class Solution {
public:
    bool isValidCell(int row, int col, int N, int M) {
        return (row >= 0 && row < N && col >= 0 && col < M);
    }

    int minCostPath(vector<vector<int>>& mat) {
        using pii = pair<int, pair<int, int>>; // {effort, {row,col}}
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        int n = mat.size();
        int m = mat[0].size();

        vector<vector<int>> diff(n, vector<int>(m, INT_MAX));
        diff[0][0] = 0;

        pq.push({0, {0, 0}});

        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();

            int currEffort = it.first;
            int row = it.second.first;
            int col = it.second.second;

            if (currEffort > diff[row][col]) continue;

            if (row == n - 1 && col == m - 1) return currEffort;

            for (int i = 0; i < 4; i++) {
                int nrow = row + dr[i];
                int ncol = col + dc[i];

                if (isValidCell(nrow, ncol, n, m)) {
                    int newEffort = max(abs(mat[row][col] - mat[nrow][ncol]), currEffort);

                    if (newEffort < diff[nrow][ncol]) {
                        diff[nrow][ncol] = newEffort;
                        pq.push({newEffort, {nrow, ncol}});
                    }
                }
            }
        }

        return diff[n - 1][m - 1];
    }
};

int main() {
    int n, m;
    cout << "Enter rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));

    cout << "Enter matrix values:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    Solution obj;
    int result = obj.minCostPath(mat);

    cout << "Minimum Effort Path: " << result << endl;

    return 0;
}
