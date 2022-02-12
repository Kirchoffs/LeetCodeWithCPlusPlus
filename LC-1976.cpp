#include <vector>
#include <map>
#include <queue>
#include <iostream>

#define ll long long
#define pll pair<ll, ll>

using namespace std;

class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int mod = (int)(1e9 + 7);
        
        vector<map<int, ll>> graph(n);
        
        for (auto& road: roads) {
            int src = road[0];
            int dst = road[1];
            int cost = road[2];
            graph[src][dst] = cost;
            graph[dst][src] = cost;
        }
        
        vector<ll> dist(n, LONG_MAX);
        dist[0] = 0;
        
        vector<ll> ways(n);
        ways[0] = 1;
        
        priority_queue<pll, vector<pll>, greater<pll>> pq;
        
        pq.push({0, 0}); // cost, node
        while (!pq.empty()) {
            auto[cost, node] = pq.top();
            pq.pop();
            
            if (cost > dist[node]) {
                continue;
            }
            
            for (auto& [next_node, next_time]: graph[node]) {
                if (dist[next_node] > dist[node] + next_time) {
                    dist[next_node] = dist[node] + next_time;
                    ways[next_node] = ways[node];
                    pq.push({dist[next_node], next_node});
                } else if (dist[next_node] == dist[node] + next_time) {
                    ways[next_node] = (ways[next_node] + ways[node]) % mod;
                }
            }
        }
        
        return ways[n-1];
    }
};

int main() {
    int n = 7;
    vector<vector<int>> roads = {
        {0, 6, 7}, {0, 1, 2}, {1, 2, 3}, 
        {1, 3, 3}, {6, 3, 3}, {3, 5, 1},
        {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}
    };
    Solution solution;
    cout << solution.countPaths(n, roads);
}
