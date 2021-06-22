#include <vector>
#include <queue>
using namespace std;

class Comparator {
public:
    bool operator()(vector<int>& a, vector<int>& b) {
        int len_a = a[1] - a[0] + 1;
        int len_b = b[1] - b[0] + 1;
        
        if (len_a > len_b) {
            return true;
        } else {
            return false;
        }
    }
};

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        vector<int> res(queries.size(), -1);
        
        vector<vector<int>> processedQueries(queries.size());
        for (int i = 0; i < queries.size(); i++) {
            processedQueries[i].push_back(queries[i]);
            processedQueries[i].push_back(i);
        }
        
        sort(processedQueries.begin(), processedQueries.end(), [](vector<int>& a, vector<int>& b) -> bool {
            if (a[0] < b[0]) {
                return true;
            }
            return false;
        });
        
        sort(intervals.begin(), intervals.end(), [](vector<int>& a, vector<int>& b) {
            if (a[0] < b[0]) {
                return true;
            }
            return false;
        });
        
        priority_queue<vector<int>, vector<vector<int>>, Comparator> pq;
        
        int interval_index = 0;
        for (vector<int>& query: processedQueries) {
            int query_index = query[1];
            int target = query[0];
            while (interval_index < intervals.size() && intervals[interval_index][0] <= target) {
                pq.push(intervals[interval_index]);
                interval_index++;
            }
            
            while (pq.size() > 0 && pq.top()[1] < target) {
                pq.pop();
            }
            
            if (pq.size() > 0) {
                res[query_index] = pq.top()[1] - pq.top()[0] + 1;
            }
        }
        
        return res;
    }
};

int main() {
    Solution solution;
    vector<vector<int>> intervals = {{1, 4}, {2, 4}, {3, 6}, {4, 4}};
    vector<int> queries = {2, 3, 4, 5};
    vector<int> ans = solution.minInterval(intervals, queries);
}