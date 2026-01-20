class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        vector<int> ans;
        for (int num : nums) {
            if (num == 2) {
                ans.push_back(-1);
            } else {
                ans.push_back(num - getLeadingOneOfLastGroup(num));
            }
        }
        return ans;
    }

private:
    // Finds the leading one of the last group of 1s in binary representation
    int getLeadingOneOfLastGroup(int num) {
        int leadingOne = 1;
        while ((num & leadingOne) > 0) {
            leadingOne <<= 1;
        }
        return leadingOne >> 1;
    }
};
