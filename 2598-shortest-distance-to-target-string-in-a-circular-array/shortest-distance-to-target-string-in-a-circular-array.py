class Solution:
    def closestTarget(self, words: List[str], target: str, startIndex: int) -> int:
        n = len(words)
        # Try moving left and right step by step
        for step in range(n):
            if words[(startIndex + step) % n] == target:
                return step
            if words[(startIndex - step + n) % n] == target:
                return step
        return -1
