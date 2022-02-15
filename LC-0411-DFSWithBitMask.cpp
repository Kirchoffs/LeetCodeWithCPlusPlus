#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>

using namespace std;

// For bit mask in dictionary, bit 1 represents the different character compared to target.
// For bit mask in target, bit 1 represents keeping the original character.
class Solution {
private:
    int len(int mask, int length) {
        int count = 0;
        for (int i = 0; i < length; i++) {
            if (mask % 2 == 1) {
                count++;
                mask /= 2;
            } else {
                int j = i;
                while (j < length && mask % 2 == 0) {
                    j++;
                    mask /= 2;
                }
                count += 1;
                i = j - 1;
            }
        }
        return count;
    }

    string get_abbr(string& word, int mask) {
        string res;
        for (int i = 0; i < word.length(); i++) {
            if (mask % 2 == 1) {
                res.push_back(word[i]);
                mask /= 2;
            } else {
                int j = i;
                while (j < word.length() && mask % 2 == 0) {
                    j++;
                    mask /= 2;
                }
                res.append(to_string(j - i));
                i = j - 1;
            }
        }
        return res;
    }

    void dfs(int bit, int cur_mask, int length, unordered_set<int>& candidates, int candidates_mask, int& min_mask, int& min_len) {
        int cur_len = len(cur_mask, length);
        if (cur_len >= min_len) {
            return;
        }

        bool match = true;
        for (auto& candidate: candidates) {
            if ((cur_mask & candidate) == 0) {
                match = false;
                break;
            }
        }

        if (match) {
            min_mask = cur_mask;
            min_len = cur_len;
        } else {
            for (int nxt_bit = bit; nxt_bit < (1 << length); nxt_bit <<= 1) {
                if ((candidates_mask & nxt_bit) != 0) {
                    dfs(nxt_bit << 1, cur_mask + nxt_bit, length, candidates, candidates_mask, min_mask, min_len);
                }
            }
        }
    }

public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        if (dictionary.size() == 0) {
            return to_string(target.length());
        }

        int n = target.length();
        unordered_set<int> candidates;
        int candidates_mask = 0;
        for (auto& word: dictionary) {
            if (word.length() == n) {
                int word_mask = 0;
                int bit = 1;
                for (int i = 0; i < n; i++) {
                    if (word[i] != target[i]) {
                        word_mask = word_mask + bit;
                    }
                    bit <<= 1;
                }
                candidates.insert(word_mask);
                candidates_mask |= word_mask;
            }
        }

        int original_mask = 0;
        int min_mask = -1;
        int min_len = INT_MAX;
        dfs(1, original_mask, n, candidates, candidates_mask, min_mask, min_len);

        if (min_mask == -1) {
            return "";
        }
        return get_abbr(target, min_mask);
    }
};

int main() {
    Solution solution;

    string target_one = "apple";
    vector<string> dictionary_one = {"blade"};
    cout << solution.minAbbreviation(target_one, dictionary_one) << endl;

    string target_two = "apple";
    vector<string> dictionary_two = {"blade", "plain", "amber"};
    cout << solution.minAbbreviation(target_two, dictionary_two) << endl;

    string target_three = "abcdef";
    vector<string> dictionary_three = {"ablade", "xxxxef", "abdefi"};
    cout << solution.minAbbreviation(target_three, dictionary_three) << endl;   
}