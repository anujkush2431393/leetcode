class Solution {
public:
  vector<int> minBitwiseArray(vector<int>& nums) {
    vector<int> ans;
    ans.reserve(nums.size());
    for (int num : nums) {
      if (num == 2) {
        ans.push_back(-1);
      } else {
        ans.push_back(num - leadingOneOfLastGroup(num));
      }
    }
    return ans;
  }

private:
  // Returns the highest power-of-two bit within the last contiguous group of 1s.
  // Example: num=0b10111100 -> last group is 0b1111, leadingOne=0b1000.
  int leadingOneOfLastGroup(int num) {
    int leadingOne = 1;
    while ((num & leadingOne) > 0) leadingOne <<= 1;
    return leadingOne >> 1;
  }
};
