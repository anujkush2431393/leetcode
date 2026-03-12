from typing import List

class Solution:
    def maxStability(self, n: int, edges: List[List[int]], k: int) -> int:
        # DSU (Union-Find) implementation
        parent = list(range(n))
        rank = [0] * n

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(x, y):
            rx, ry = find(x), find(y)
            if rx == ry:
                return False
            if rank[rx] < rank[ry]:
                parent[rx] = ry
            elif rank[rx] > rank[ry]:
                parent[ry] = rx
            else:
                parent[ry] = rx
                rank[rx] += 1
            return True

        # Check feasibility for a given stability threshold X
        def can(X):
            # Reset DSU
            for i in range(n):
                parent[i] = i
                rank[i] = 0
            used_upgrades = 0
            edges_used = 0

            # First, include mandatory edges
            for u, v, s, must in edges:
                if must == 1:
                    if s < X:  # mandatory edge too weak
                        return False
                    if not union(u, v):
                        return False  # cycle with mandatory edges
                    edges_used += 1

            # Collect optional edges
            usable_no_upgrade = []
            usable_with_upgrade = []
            for u, v, s, must in edges:
                if must == 0:
                    if s >= X:
                        usable_no_upgrade.append((s, u, v))
                    elif s * 2 >= X:
                        usable_with_upgrade.append((s, u, v))

            # Sort edges by strength descending (to maximize min edge)
            usable_no_upgrade.sort(reverse=True)
            usable_with_upgrade.sort(reverse=True)

            # Use non-upgraded edges first
            for s, u, v in usable_no_upgrade:
                if union(u, v):
                    edges_used += 1
                    if edges_used == n - 1:
                        return True

            # Use upgraded edges if needed
            for s, u, v in usable_with_upgrade:
                if used_upgrades < k and union(u, v):
                    used_upgrades += 1
                    edges_used += 1
                    if edges_used == n - 1:
                        return True

            return edges_used == n - 1

        # Binary search over possible stability values
        lo, hi = 1, max(s for _, _, s, _ in edges) * 2
        ans = -1
        while lo <= hi:
            mid = (lo + hi) // 2
            if can(mid):
                ans = mid
                lo = mid + 1
            else:
                hi = mid - 1
        return ans
