import math
from collections import defaultdict
from heapq import heappush, heappop, heappushpop
from typing import List

class LazyHeap:
    def __init__(self):
        self.heap = []
        self.remove_cnt = defaultdict(int)
        self.size = 0
        self.sum = 0
        
    def apply_remove(self):
        while self.heap and self.remove_cnt[self.heap[0]] > 0:
            self.remove_cnt[self.heap[0]] -= 1
            heappop(self.heap)
            
    def top(self) -> int:
        self.apply_remove()
        return self.heap[0]
        
    def pop(self) -> int:
        self.apply_remove()
        self.size -= 1
        self.sum -= self.heap[0]
        return heappop(self.heap)
        
    def push(self, x: int) -> None:
        if self.remove_cnt[x] > 0:
            self.remove_cnt[x] -= 1
        else:
            heappush(self.heap, x)
        self.size += 1
        self.sum += x
        
    def pushpop(self, x: int) -> int:
        self.apply_remove()
        if not self.heap or x <= self.heap[0]:
            return x
        self.sum += x - self.heap[0]
        return heappushpop(self.heap, x)

    def remove(self, x: int) -> None:
        self.remove_cnt[x] += 1
        self.size -= 1
        self.sum -= x


class Solution:
    def minOperations(self, nums: List[int], x: int, k: int) -> int:
        n = len(nums)
        ops = [0] * (n - x + 1)
        
        left = LazyHeap()
        right = LazyHeap()
        
        for i, num in enumerate(nums):
            if left.size == right.size:
                left.push(-right.pushpop(num))
            else:
                right.push(-left.pushpop(-num))
                
            start = i + 1 - x
            if start < 0:
                continue
                
            median = -left.top()
            sum_left = median * left.size + left.sum
            sum_right = right.sum - median * right.size
            ops[start] = sum_left + sum_right
            
            num_to_remove = nums[start]
            if num_to_remove <= -left.top():
                left.remove(-num_to_remove)
                if left.size < right.size:
                    left.push(-right.pop())
            else:
                right.remove(num_to_remove)
                if left.size > right.size + 1:
                    right.push(-left.pop())
                    
        # DP with rolling arrays
        inf = math.inf
        pre = [0] * (n + 1)
        
        for j in range(1, k + 1):
            cur = [inf] * (n + 1)
            for i in range(j * x, n + 1):
                cur[i] = min(cur[i - 1], pre[i - x] + ops[i - x])
            pre = cur
            
        return pre[n]