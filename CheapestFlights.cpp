#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int CheapestFLight(int n, vector<vector<int>>& flights, int src, int dst, int K) {
        
        vector<pair<int,int>> adj[n];
        for(auto it : flights){
            adj[it[0]].push_back({it[1], it[2]}); // {destination, cost}
        }
        
        // {stops, {node, totalCost}}
        queue<pair<int, pair<int,int>>> q;
        q.push({0, {src, 0}});
        
        vector<int> dist(n, 1e9);
        dist[src] = 0;
        
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            
            int stops = it.first;
            int node = it.second.first;
            int cost = it.second.second;
            
            if(stops > K) continue;
            
            for(auto iter : adj[node]){
                int adjNode = iter.first;
                int wt = iter.second;
                
                if(cost + wt < dist[adjNode] && stops <= K){
                    dist[adjNode] = cost + wt;
                    q.push({stops + 1, {adjNode, cost + wt}});
                }
            }
        }
        
        return dist[dst] == 1e9 ? -1 : dist[dst];
    }
};

int main() {
    Solution obj;

    int n = 4;
    vector<vector<int>> flights = {
        {0, 1, 100},
        {1, 2, 100},
        {2, 3, 100},
        {0, 2, 500}
    };

    int src = 0;
    int dst = 3;
    int K = 1;

    int ans = obj.CheapestFLight(n, flights, src, dst, K);
    cout << "Cheapest Price: " << ans << endl;

    return 0;
}
