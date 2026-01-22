class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int operations = 0;

        // Use a list for efficient erase/insert
        list<int> arr(nums.begin(), nums.end());

        while (!is_sorted(arr.begin(), arr.end())) {
            auto it = arr.begin();
            auto best = it;
            int minSum = INT_MAX;
            auto nextIt = it; ++nextIt;

            // Find adjacent pair with minimum sum (leftmost if tie)
            for (; nextIt != arr.end(); ++it, ++nextIt) {
                int sum = *it + *nextIt;
                if (sum < minSum) {
                    minSum = sum;
                    best = it;
                }
            }

            // Merge the chosen pair
            auto nextBest = best; ++nextBest;
            *best = *best + *nextBest;
            arr.erase(nextBest);
            operations++;
        }

        return operations;
    }
};
