class Solution {
public:
    vector<vector<int>> Res;

    void fun(vector<int>& nums, int i, int n) {
        if (i == n) {
            Res.push_back(nums);
            return;
        }

        for (int j = i; j < n; j++) {
            swap(nums[i], nums[j]);
            fun(nums, i + 1, n);
            swap(nums[i], nums[j]);
        }
    }

    vector<vector<int>> permute(vector<int>& nums) {
        Res.clear();
        fun(nums, 0, nums.size());
        return Res;
    }
};