#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        vector<vector<int>> partial_cost(n, vector<int>(n, 0));
        
        for (int i = 0; i < n; i++) {
            int max_value = INT_MIN;
            int total = 0;
            for (int j = i; j < n; j++) {
                max_value = max(max_value, nums[j]);
                total += nums[j];
                partial_cost[i][j] = max_value * (j - i + 1) - total;
            }
        }
        
        vector<vector<int>> dp(n, vector<int>(k + 2, INT_MAX));
        
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= k + 1; j++) {
                for (int l = j - 2; l < i; l++) {
                    dp[i][j] = min(dp[i][j], 
                                   j == 1 ? partial_cost[0][i] : dp[l][j-1] + partial_cost[l+1][i]);
                }
            }
        }
        
        return dp[n-1][k+1];
    }
};

int main() {
    Solution solution;
    vector<int> arr = {10, 20};
    cout << solution.minSpaceWastedKResizing(arr, 0) << endl;
}