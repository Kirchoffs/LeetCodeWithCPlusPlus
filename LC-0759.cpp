#include <iostream>
#include <vector>
using namespace std;

class Interval {
public:
    int start;
    int end;

    Interval() {}

    Interval(int _start, int _end) {
        start = _start;
        end = _end;
    }
};

class Solution {
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>> schedule) {
        int len = schedule.size();
        vector<pair<int, int>> points;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < schedule[i].size(); j++) {
                points.push_back(make_pair(schedule[i][j].start, 1));
                points.push_back(make_pair(schedule[i][j].end, -1));
            }
        }
        sort(points.begin(), points.end(), [](pair<int, int>&a, pair<int, int>&b) {
            return a.first < b.first;
        });
        
        vector<Interval> res;
        int curNum = 0;
        int preTime = -1;
        int i = 0;
        while (i < points.size()) {
            int curTime = points[i].first;
            while (i < points.size() && points[i].first == curTime) {
                curNum += points[i].second;
                i++;
            }
            if (curNum == 0) {
                if (preTime == -1) {
                    preTime = curTime;
                }
            } else {
                if (preTime != -1) {
                    res.push_back(Interval(preTime, curTime));
                    preTime = -1;
                }
            }
        }
        
        return res;
    }
};

int main() {
    Solution solution;
    vector<vector<Interval>> schedule;
    schedule.push_back({Interval(1, 2), Interval(5, 6)});
    schedule.push_back({Interval(1, 3)});
    schedule.push_back({Interval(4, 10)});
    vector<Interval> res = solution.employeeFreeTime(schedule);
    for (auto& re: res) {
        cout << re.start << " " << re.end << endl;
    }
}