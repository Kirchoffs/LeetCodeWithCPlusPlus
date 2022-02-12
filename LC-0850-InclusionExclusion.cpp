#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
    void intersect(vector<int>& rec, vector<int>& cur) {
        rec[0] = max(rec[0], cur[0]);
        rec[1] = max(rec[1], cur[1]);
        rec[2] = min(rec[2], cur[2]);
        rec[3] = min(rec[3], cur[3]);
    }

    long area(vector<int>& rec) {
        if (rec[0] >= rec[2] || rec[1] >= rec[3]) {
            return 0;
        }
        return (long) (rec[2] - rec[0]) * (rec[3] - rec[1]);
    }

public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int mod = 1000000007;
        int n = rectangles.size();
        long res = 0;

        for (int subset = 1; subset < (1 << n); subset++) {
            vector<int> rec = {0, 0, 1000000000, 1000000000};
            int parity = -1;
            for (int bit = 0; bit < n; bit++) {
                if (((subset >> bit) & 1) != 0) {
                    parity *= -1;
                    intersect(rec, rectangles[bit]);
                }
            }
            res = (res + parity * area(rec) + mod) % mod;
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