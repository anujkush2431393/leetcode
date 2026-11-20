from typing import List


class Solution:
    def maxSelectedElements(self, nums: List[int]) -> int:
        nums.sort()
        dp = {}
        ans = 0

        for x in nums:
            # Option 1: increment x by 1 -> becomes x + 1
            up = x + 1
            dp[up] = dp.get(up - 1, 0) + 1
            ans = max(ans, dp[up])

            # Option 2: keep x unchanged -> stays x
            dp[x] = dp.get(x - 1, 0) + 1
            ans = max(ans, dp[x])

        return ans