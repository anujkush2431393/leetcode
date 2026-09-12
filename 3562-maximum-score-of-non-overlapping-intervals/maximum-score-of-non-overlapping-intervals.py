from bisect import bisect_left

class Solution:
    def maximumWeight(self, input):
        intervals = [(s, e, w, i) for i, (s, e, w) in enumerate(input)]
        intervals.sort(key=lambda x: (x[0], x[1]))

        memo = [[None] * 5 for _ in range(len(intervals))]

        def findFirstGreater(startFrom, rightBoundary):
            l, r = startFrom, len(intervals)
            while l < r:
                m = (l + r) // 2
                if intervals[m][0] > rightBoundary:
                    r = m
                else:
                    l = m + 1
            return l

        def dp(i, quota):
            if i == len(intervals) or quota == 0:
                return (0, [])
            if memo[i][quota] is not None:
                return memo[i][quota]

            # Skip current
            skip = dp(i + 1, quota)

            # Pick current
            _, r, weight, idx = intervals[i]
            j = findFirstGreater(i + 1, r)
            nextRes = dp(j, quota - 1)

            newSelected = nextRes[1] + [idx]
            newSelected.sort()
            pick = (weight + nextRes[0], newSelected)

            if pick[0] > skip[0] or (pick[0] == skip[0] and pick[1] < skip[1]):
                memo[i][quota] = pick
            else:
                memo[i][quota] = skip
            return memo[i][quota]

        return dp(0, 4)[1]



