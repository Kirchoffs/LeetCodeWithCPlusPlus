#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    int numMatchingSubseq(string S, vector<string>& words) {
        int cnt = 0;
        vector<const char*> waiting[26];
        for (auto &w : words) {
            waiting[w[0] - 'a'].push_back(w.c_str());
        }
            
        for (char c : S) {
            auto advance = waiting[c - 'a'];
            waiting[c - 'a'].clear();
            for (auto it: advance) {
                it++;
                if (*it >= 'a') {
                    waiting[*it - 'a'].push_back(it);
                } else {
                    cnt++;
                }
            }
        }
        return cnt++;
    }
};

int main() {
    string S = "abcde";
    vector<string> words = {"a", "bb", "acd", "ace"};
    Solution solution;
    cout << solution.numMatchingSubseq(S, words) << endl;
}

