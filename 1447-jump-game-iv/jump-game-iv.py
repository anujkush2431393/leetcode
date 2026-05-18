from collections import deque

class Solution:
    def minJumps(self, arr: List[int]) -> int:
        idx = defaultdict(list)
        for i, v in enumerate(arr):
            idx[v].append(i)
        q = deque([(0, 0)]) # (index, step)
        vis = {0} # visited
        while q:
            i, step = q.popleft()
            if i == len(arr) - 1:
                return step
            v = arr[i]
            step += 1
            for j in idx[v]:
                if j not in vis:
                    vis.add(j)
                    q.append((j, step))
            # without this del, it will be huge/duplicated loop
            # over time limit for input [7,7,7,7,7,....7,7]
            del idx[v] # avoid dedup

            if i + 1 < len(arr) and (i + 1) not in vis:
                vis.add(i + 1)
                q.append((i + 1, step))
            if i - 1 >= 0 and (i - 1) not in vis:
                vis.add(i - 1)
                q.append((i - 1, step))
