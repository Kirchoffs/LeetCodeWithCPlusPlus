#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
    int distance(vector<vector<int>>& points, int i, int j) {
        return abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1]);
    }

    int find(vector<int>& uf, int i) {
        if (uf[i] != i) {
            uf[i] = find(uf, uf[i]);
        }
        return uf[i];
    }

    bool is_connected(vector<int>& uf, int i, int j) {
        return find(uf, i) == find(uf, j);
    }

    void connect(vector<int>& uf, int i, int j) {
        int ir = find(uf, i);
        int jr = find(uf, j);
        uf[ir] = jr;
    }

public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        vector<vector<int>> graph;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                graph.push_back({distance(points, i, j), i, j});
            }
        }

        sort(graph.begin(), graph.end());
        vector<int> uf(n, 0);
        for (int i = 0; i < n; i++) {
            uf[i] = i;
        }

        int res = 0;
        for (auto& edge: graph) {
            if (!is_connected(uf, edge[1], edge[2])) {
                connect(uf, edge[1], edge[2]);
                res += edge[0];
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