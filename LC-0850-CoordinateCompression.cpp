#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

class Solution {
private:
    long area(int x1, int y1, int x2, int y2) {
        long mod = 1000000007;
        return (long) (x2 - x1) * (y2 - y1) % mod;
    }

public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        set<int> x_set;
        set<int> y_set;
        for (auto& rectangle: rectangles) {
            x_set.insert(rectangle[0]);
            x_set.insert(rectangle[2]);
            y_set.insert(rectangle[1]);
            y_set.insert(rectangle[3]);
        }

        vector<int> x_list(x_set.begin(), x_set.end());
        vector<int> y_list(y_set.begin(), y_set.end());

        unordered_map<int, int> x_map;
        unordered_map<int, int> y_map;
        for (int i = 0; i < x_list.size(); i++) {
            x_map[x_list[i]] = i;
        }
        for (int i = 0; i < y_list.size(); i++) {
            y_map[y_list[i]] = i;
        }

        vector<vector<bool>> matrix(x_list.size(), vector<bool>(y_list.size(), false));
        for (auto& rectangle: rectangles) {
            for (int x = x_map[rectangle[0]]; x < x_map[rectangle[2]]; x++) {
                for (int y = y_map[rectangle[1]]; y < y_map[rectangle[3]]; y++) {
                    matrix[x][y] = true;
                }
            }
        }

        long res = 0;
        long mod = 1000000007;
        for (int x = 0; x < x_list.size(); x++) {
            for (int y = 0; y < y_list.size(); y++) {
                if (matrix[x][y]) {
                    res = (res + area(x_list[x], y_list[y], x_list[x+1], y_list[y+1])) % mod;
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