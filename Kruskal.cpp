#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class DSU {
    vector<int> parent, size;

public:
    DSU(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]); // Path compression
    }

    void unionBySize(int u, int v) {
        int pu = findUPar(u);
        int pv = findUPar(v);

        if (pu == pv) return;

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

int main() {
    int n = 6; // number of nodes (0 to 5)

    // edges format: {weight, u, v}
    vector<vector<int>> edges = {
        {4, 0, 1},
        {4, 0, 2},
        {6, 1, 2},
        {6, 2, 3},
        {3, 2, 4},
        {2, 3, 4},
        {5, 3, 5},
        {7, 4, 5}
    };

    // Step 1: Sort edges by weight
    sort(edges.begin(), edges.end());

    DSU dsu(n);
    int mstWeight = 0;
    vector<pair<int,int>> mstEdges;

    // Step 2: Process edges
    for (auto &e : edges) {
        int wt = e[0];
        int u = e[1];
        int v = e[2];

        // Step 3: Check if adding this edge forms a cycle
        if (dsu.findUPar(u) != dsu.findUPar(v)) {
            mstWeight += wt;
            mstEdges.push_back({u, v});
            dsu.unionBySize(u, v);
        }
    }

    cout << "Total Weight of MST: " << mstWeight << "\n";
    cout << "Edges in MST:\n";
    for (auto &p : mstEdges) {
        cout << p.first << " - " << p.second << "\n";
    }

    return 0;
}
