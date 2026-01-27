#include <bits/stdc++.h>
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

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    void unite(int u, int v) {
        int pu = find(u);
        int pv = find(v);
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

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        int n = accounts.size();
        DSU ds(n);

        unordered_map<string, int> emailOwner;

        // Step 1: Union accounts that share emails
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < accounts[i].size(); j++) {
                string email = accounts[i][j];
                if (emailOwner.count(email)) {
                    ds.unite(i, emailOwner[email]);
                } else {
                    emailOwner[email] = i;
                }
            }
        }

        // Step 2: Group emails by root
        unordered_map<int, set<string>> groupedEmails;
        unordered_map<int, string> rootName;

        for (auto &it : emailOwner) {
            string email = it.first;
            int owner = it.second;
            int root = ds.find(owner);

            groupedEmails[root].insert(email);

            // Store name once per root (first encountered)
            if (!rootName.count(root)) {
                rootName[root] = accounts[root][0];
            }
        }

        // Step 3: Build result
        vector<vector<string>> result;

        for (auto &it : groupedEmails) {
            int root = it.first;
            vector<string> merged;
            merged.push_back(rootName[root]);

            for (auto &email : it.second)
                merged.push_back(email);

            result.push_back(merged);
        }

        return result;
    }
};
