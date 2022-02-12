#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
private:
    int distance(vector<vector<int>>& points, int i, int j) {
        return abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();

        vector<int> visited(n, false);
        priority_queue<pair<int, int>> pq;
        int connected = 0;
        int index = 0;
        int res = 0;

        pq.push({0, 0}); // [-dist, node_index]
        while (connected < n) {
            while (visited[pq.top().second]) {
                pq.pop();
            }

            res -= pq.top().first;
            int cur = pq.top().second;
            visited[cur] = true;
            connected++;
            for (int nxt = 0; nxt < n; nxt++) {
                if (!visited[nxt]) {
                    pq.push({-distance(points, cur, nxt), nxt});
                }
            }
        }

        return res;
    }
};

int main() {
    vector<vector<int>> points = {{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}};
    Solution solution;
    cout << solution.minCostConnectPoints(points);
}