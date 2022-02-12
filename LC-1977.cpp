#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
private:
    int mod = 1e9 + 7;
public:
    int numberOfCombinations(string num) {
        int n = num.length();
        
        vector<vector<int>> lcp(n + 1, vector<int>(n + 1, 0));
        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {
                if (num[i] == num[j]) {
                    lcp[i][j] = lcp[i+1][j+1] + 1;
                } else {
                    lcp[i][j] = 0;
                }
            }
        }
        
        vector<vector<int>> dp(n, vector<int>(n + 1, 0));
        for (int i = 0; i < n; i++) {
            for (int len = 1; len <= i + 1; len++) {
                int j = i - len + 1;
                int delta = 0;
                    
                if (num[j] != '0') {
                    if (j == 0) {
                        delta = 1;
                    } else {
                        int max_plen = min(len, j);
                        while (max_plen > 0 && num[j - max_plen] == '0') {
                            max_plen--;
                        }
                        if (max_plen == 0) {
                            delta = 0;
                        } else {
                            int pj = j - max_plen;
                            if (max_plen == len && 
                                lcp[pj][j] < max_plen &&
                                num[pj + lcp[pj][j]] > num[j + lcp[pj][j]]) {
                                max_plen--;
                            }
                            if (max_plen == 0) {
                                delta = 0;
                            } else {
                                delta = dp[j-1][max_plen];
                            }
                        }
                    }
                }
            
                dp[i][len] = (dp[i][len-1] + delta) % mod;
            }
        }
        
        return dp[n-1][n];
    }
};

int main() {
    string num = "327";
    Solution solution;
    cout << solution.numberOfCombinations(num) << endl;
}