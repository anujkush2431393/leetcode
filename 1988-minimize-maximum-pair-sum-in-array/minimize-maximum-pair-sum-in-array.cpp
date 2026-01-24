class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());  // Step 1: Sort the array
        int left = 0, right = nums.size() - 1;
        int maxSum = 0;

        // Step 2: Pair smallest with largest
        while (left < right) {
            int pairSum = nums[left] + nums[right];
            maxSum = max(maxSum, pairSum);
            left++;
            right--;
        }
        return maxSum;  // Step 3: Return minimized maximum pair sum
    }
};
