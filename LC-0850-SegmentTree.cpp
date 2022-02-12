#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

// Improvement for LC-0850-SweepLine.cpp

class SegmentTree {
private:
    vector<int> data;
    int len;
    vector<int> st;
    vector<int> cnt;

    void update(int p, int s, int e, int l, int r, int delta) {
        if (l >= r) {
            return;
        }

        if (l <= s && r >= e) {
            cnt[p] += delta;
        } else {
            int m = s + (e - s) / 2;
            // if (l < m) {
            //     update(p * 2 + 1, s, m, l, r, delta);
            // } 
            // if (r > m) {
            //     update(p * 2 + 2, m, e, l, r, delta);
            // }

            update(p * 2 + 1, s, m, l, min(m, r), delta);
            update(p * 2 + 2, m, e, max(m, l), r, delta);
        }

        if (cnt[p] > 0) {
            st[p] = data[e] - data[s];
            return;
        } else {
            st[p] = 0;
        }

        if (s + 1 == e) {
            return;
        }

        st[p] = st[p * 2 + 1] + st[p * 2 + 2];
    }

    int query(int p, int s, int e, int l, int r) {
        if (l >= r) {
            return 0;
        }

        if (l <= s && r >= e) {
            return st[p];
        }

        int m = s + (e - s) / 2;
        int res = 0;
        
        // if (l < m) {
        //     res += query(p * 2 + 1, s, m, l, r);
        // }
        // if (r > m) {
        //     res += query(p * 2 + 2, m, e, l, r);
        // }

        res += query(p * 2 + 1, s, m, l, min(m, r));
        res += query(p * 2 + 2, m, e, max(m, l), r);

        return res;
    }

public:
    SegmentTree(vector<int>& data): data(data) {
        len = data.size();
        st.assign((len - 1) * 4, 0);
        cnt.assign((len - 1) * 4, 0);
    }

    void update(int a, int b, int delta) {
        update(0, 0, len - 1, a, b, delta);
    }

    int query() {
        return query(0, 0, len - 1, 0, len - 1);
    }
};

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size();
        int OPEN = 1, CLOSE = -1;
        vector<vector<int>> events(2 * n);
        set<int> x_set;
 
        for (int i = 0; i < rectangles.size(); i++) {
            auto& rectangle = rectangles[i];
            events[i * 2] = {rectangle[1], OPEN, rectangle[0], rectangle[2]};
            events[i * 2 + 1] = {rectangle[3], CLOSE, rectangle[0], rectangle[2]};
            x_set.insert(rectangle[0]);
            x_set.insert(rectangle[2]);
        }

        sort(events.begin(), events.end());
        vector<int> x_list(x_set.begin(), x_set.end());

        unordered_map<int, int> x_map;
        for (int i = 0; i < x_list.size(); i++) {
            x_map[x_list[i]] = i;
        }

        long res = 0;
        long mod = 1000000007;
        int last_y = events[0][0];
        SegmentTree segment_tree(x_list);
        for (auto& event: events) {
            int y = event[0], type = event[1], x1 = event[2], x2 = event[3];

            int delta_x = segment_tree.query();
            res = (res + (long) (y - last_y) * delta_x) % mod;

            segment_tree.update(x_map[x1], x_map[x2], type);

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