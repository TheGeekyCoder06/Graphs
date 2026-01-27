#include <iostream>
#include <vector>
using namespace std;

class DSU {
    vector<int> parent, rankv, size;

public:
    DSU(int n) {
        parent.resize(n);
        rankv.resize(n, 0);
        size.resize(n, 1);

        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    // Find with Path Compression
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    // Union by Rank
    void unionByRank(int u, int v) {
        int pu = findUPar(u);
        int pv = findUPar(v);

        if (pu == pv) return;

        if (rankv[pu] < rankv[pv]) {
            parent[pu] = pv;
        }
        else if (rankv[pv] < rankv[pu]) {
            parent[pv] = pu;
        }
        else {
            parent[pv] = pu;
            rankv[pu]++;
        }
    }

    // Union by Size
    void unionBySize(int u, int v) {
        int pu = findUPar(u);
        int pv = findUPar(v);

        if (pu == pv) return;

        if (size[pu] < size[pv]) {
            parent[pu] = pv;
            size[pv] += size[pu];
        }
        else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};

int main() {
    DSU dsu(7); // nodes 0 to 6

    dsu.unionByRank(1, 2);
    dsu.unionByRank(2, 3);
    dsu.unionByRank(4, 5);
    dsu.unionByRank(6, 5);

    // Check if 3 and 6 are in same component
    if (dsu.findUPar(3) == dsu.findUPar(6))
        cout << "Same Component\n";
    else
        cout << "Different Components\n";

    dsu.unionByRank(3, 6);

    if (dsu.findUPar(3) == dsu.findUPar(6))
        cout << "Same Component\n";
    else
        cout << "Different Components\n";

    return 0;
}
