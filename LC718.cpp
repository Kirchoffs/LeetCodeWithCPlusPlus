#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = min(nums1.size(), nums2.size()) + 1;
        while (i < j) {
            int m = i + (j - i) / 2;
            if (check(nums1, nums2, m)) {
                i = m + 1;
            } else {
                j = m;
            }
        }
        return i - 1;
    }
    
private:
    using ll = long long;
    ll mod = (ll)(1e10 + 7);
    int base = 101;
    
    ll binary_exponentiation(int base, int power) {
        ll res = 1;
        ll square = base;
        while (power > 0) {
            if (power % 2 == 1) {
                res = res * square % mod;
            }
            power = power / 2;
            square = square * square % mod;
        }
        return res;
    }
    
    bool check(vector<int>& nums1, vector<int>& nums2, int m) {   
        if (m == 0) {
            return true;
        }
        
        unordered_set<ll> hash1;
        unordered_set<ll> hash2;
        ll significant_base = binary_exponentiation(base, m);
        
        ll cur1 = 0;
        for (int i = 0; i < nums1.size(); i++) {
            cur1 = (cur1 * base + nums1[i]) % mod;
            if (i >= m) {
                cur1 = (cur1 + mod - nums1[i - m] * significant_base % mod) % mod;
            }
            if (i >= m - 1) {
                hash1.insert(cur1);
            }
        }
        
        ll cur2 = 0;
        for (int i = 0; i < nums2.size(); i++) {
            cur2 = (cur2 * base + nums2[i]) % mod;
            if (i >= m) {
                cur2 = (cur2 + mod - nums2[i - m] * significant_base % mod) % mod;
            }
            if (i >= m - 1) {
                hash2.insert(cur2);
            }
        }
        
        for (int hash: hash1) {
            if (hash2.count(hash) > 0) {
                return true;
            }
        }
        
        return false;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {1, 2, 3, 2, 1};
    vector<int> nums2 = {3, 2, 1, 4, 7};
    cout << solution.findLength(nums1, nums2) << endl;
}