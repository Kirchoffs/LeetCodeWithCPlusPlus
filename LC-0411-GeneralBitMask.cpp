#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
private:
    int len(int mask, int length) {
        int count = 0;
        for (int i = 0; i < length; i++) {
            // If the bit is one, then keep the original character
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

public:
    string minAbbreviation(string target, vector<string>& dictionary) {
        if (dictionary.size() == 0) {
            return to_string(target.length());
        }
        
        int m = target.length();

        unordered_set<string> candidates;
        for (auto& word: dictionary) {
            if (word.length() == m) {
                candidates.insert(word);
            }
        }

        vector<pair<int, int>> masks;
        for (int state = 0; state < (1 << m); state++) {
            masks.push_back({len(state, m), state});
        }
        sort(masks.begin(), masks.end());

        for (auto& mask_info: masks) {
            int mask = mask_info.second;
            string target_abbr = get_abbr(target, mask);

            bool is_matched = false;
            for (string word: candidates) {
                string word_abbr = get_abbr(word, mask);
                if (target_abbr == word_abbr) {
                    is_matched = true;
                    break;
                }
            }

            if (!is_matched) {
                return target_abbr;
            }
        }

        return "";
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
}