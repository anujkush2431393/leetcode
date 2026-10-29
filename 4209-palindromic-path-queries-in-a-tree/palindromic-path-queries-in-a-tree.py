class Solution:
    def palindromePath(self, n: int, edges: list[list[int]], s: str, queries: list[str]) -> list[bool]:
        adj = [[] for _ in range(n)]

        for u, v in edges:
            adj[u].append(v)
            adj[v].append(u)

        LOG = n.bit_length()
        parent = [-1] * n
        depth = [0] * n
        tin = [0] * n
        tout = [0] * n
        bit = [0] * n
        timer = 0

        up = [[0] * n for _ in range(LOG)]

        # Iterative DFS
        stack = [(0, -1, 0)]

        while stack:
            u, p, state = stack.pop()

            if state == 0:
                tin[u] = timer
                timer += 1

                parent[u] = p
                up[0][u] = u if p == -1 else p
                bit[u] = 1 << (ord(s[u]) - ord('a'))

                for k in range(1, LOG):
                    up[k][u] = up[k - 1][up[k - 1][u]]

                stack.append((u, p, 1))

                for v in reversed(adj[u]):
                    if v != p:
                        depth[v] = depth[u] + 1
                        stack.append((v, u, 0))

            else:
                tout[u] = timer - 1

        # Fenwick Tree using XOR
        class Fenwick:
            def __init__(self, n):
                self.n = n
                self.tree = [0] * (n + 1)

            def add(self, i, val):
                i += 1
                while i <= self.n:
                    self.tree[i] ^= val
                    i += i & -i

            def query(self, i):
                res = 0
                i += 1

                while i > 0:
                    res ^= self.tree[i]
                    i -= i & -i

                return res

        fw = Fenwick(n)

        # Apply each node's contribution over its subtree interval
        for u in range(n):
            fw.add(tin[u], bit[u])

            if tout[u] + 1 < n:
                fw.add(tout[u] + 1, bit[u])

        def get_root_path(u):
            return fw.query(tin[u])

        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u

            diff = depth[u] - depth[v]

            for k in range(LOG):
                if diff & (1 << k):
                    u = up[k][u]

            if u == v:
                return u

            for k in range(LOG - 1, -1, -1):
                if up[k][u] != up[k][v]:
                    u = up[k][u]
                    v = up[k][v]

            return parent[u]

        ans = []
        s = list(s)

        for q in queries:
            parts = q.split()

            if parts[0] == "update":
                u = int(parts[1])
                c = parts[2]

                new_bit = 1 << (ord(c) - ord('a'))

                if s[u] != c:
                    change = bit[u] ^ new_bit

                    fw.add(tin[u], change)

                    if tout[u] + 1 < n:
                        fw.add(tout[u] + 1, change)

                    # IMPORTANT: Update the node's current bitmask too
                    bit[u] = new_bit
                    s[u] = c

            else:
                u = int(parts[1])
                v = int(parts[2])

                w = lca(u, v)

                mask = get_root_path(u) ^ get_root_path(v) ^ bit[w]

                # At most one character may have odd frequency
                ans.append((mask & (mask - 1)) == 0)

        return ans