#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

// Improvement for LC-0850-CoordinateCompression.cpp

class DiffMatrix {
public:
    vector<vector<int>> diff;
    vector<vector<int>> matrix;
    int m;
    int n;
    
    DiffMatrix(int m, int n) {
        diff.assign(m + 1, vector<int>(n + 1, 0));
        matrix.assign(m + 1, vector<int>(n + 1, 0));
        this->m = m;
        this->n = n;
    }

    void set(int x1, int y1, int x2, int y2, int delta) {
        diff[x1][y1] += delta;
        diff[x1][y2 + 1] -= delta;
        diff[x2 + 1][y1] -= delta;
        diff[x2 + 1][y2 + 1] += delta;
    }

    void compute() {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                matrix[i][j] = 
                    (i == 0 ? 0 : matrix[i-1][j]) + 
                    (j == 0 ? 0 : matrix[i][j-1]) +
                    diff[i][j] - 
                    (i == 0 || j == 0 ? 0 : matrix[i-1][j-1]);
            }
        }
    }
};

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        set<int> x_set;
        set<int> y_set;
        for (auto& rectangle: rectangles) {
            x_set.insert(rectangle[0]);
            y_set.insert(rectangle[1]);
            x_set.insert(rectangle[2]);
            y_set.insert(rectangle[3]);
        }

        vector<int> x_list(x_set.begin(), x_set.end());
        vector<int> y_list(y_set.begin(), y_set.end());
        
        int m = x_list.size(), n = y_list.size();
        unordered_map<int, int> x_map;
        unordered_map<int, int> y_map;
        for (int i = 0; i < m; i++) {
            x_map[x_list[i]] = i;
        }
        for (int i = 0; i < n; i++) {
            y_map[y_list[i]] = i;
        }

        
        DiffMatrix grid(m, n);
        for (auto& rectangle: rectangles) {
            int x1 = x_map[rectangle[0]], y1 = y_map[rectangle[1]];
            int x2 = x_map[rectangle[2]] - 1, y2 = y_map[rectangle[3]] - 1;
            grid.set(x1, y1, x2, y2, 1);
        }
        grid.compute();

        long res = 0;
        long mod = 1000000007;
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (grid.matrix[i][j] > 0) {
                    res = (res + (long) (x_list[i+1] - x_list[i]) * (y_list[j+1] - y_list[j]) % mod) % mod;
                }
            }
        }

        return (int) res;
    }
};

int main() {
    Solution solution;

    vector<vector<int>> rectangles_one = {
        {0, 0, 2, 2},
        {1, 0, 2, 3},
        {1, 0, 3, 1}
    };
    cout << solution.rectangleArea(rectangles_one) << endl;

    vector<vector<int>> rectangles_two = {
        {0, 0, 1000000000, 1000000000}
    };
    cout << solution.rectangleArea(rectangles_two) << endl;
}