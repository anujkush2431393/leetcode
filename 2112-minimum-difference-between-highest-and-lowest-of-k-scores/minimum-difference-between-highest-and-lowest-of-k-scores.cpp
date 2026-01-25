class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        // Sort the array so we can check consecutive windows
        sort(nums.begin(), nums.end());
        
        int n = nums.size();
        int ans = INT_MAX;
        
        // Sliding window of size k
        for (int i = 0; i + k - 1 < n; i++) {
            int diff = nums[i + k - 1] - nums[i];
            ans = min(ans, diff);
        }
        
        return ans;
    }
};
