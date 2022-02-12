#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        int OPEN = 0, CLOSE = 1;
        vector<vector<int>> events(2 * n);

        for (int i = 0; i < rectangles.size(); i++) {
            auto& rectangle = rectangles[i];
            events[2 * i] = {rectangle[1], OPEN, rectangle[0], rectangle[2]};
            events[2 * i + 1] = {rectangle[3], CLOSE, rectangle[0], rectangle[2]};
        }

        sort(events.begin(), events.end());

        long res = 0;
        long mod = 1000000007;
        int last_y = events[0][0];
        vector<pair<int, int>> active;
        for (auto& event: events) {
            int y = event[0], type = event[1], x1 = event[2], x2 = event[3];

            sort(active.begin(), active.end());
            int delta_x = 0;
            int cur_x = -1;
            for (auto& interval: active) {
                cur_x = max(cur_x, interval.first);
                delta_x += max(interval.second - cur_x, 0);
                cur_x = max(cur_x, interval.second);
            }

            res = (res + (long) (y - last_y) * delta_x) % mod;

            if (type == OPEN) {
                active.push_back({x1, x2});
            } else {
                for (vector<pair<int, int>>::iterator it = active.begin(); it != active.end(); it++) {
                    if ((*it).first == x1 && (*it).second == x2) {
                        active.erase(it);
                        break;
                    }
                }
            }

            last_y = y;
        }

        return res;
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