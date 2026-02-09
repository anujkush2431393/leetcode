class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        ans, mi = 0, inf
        for v in prices:
            mi = min(mi, v)
            ans = max(ans, v - mi)
        return ans