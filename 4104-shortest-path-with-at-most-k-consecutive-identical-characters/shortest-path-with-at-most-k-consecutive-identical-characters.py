from typing import List
import heapq

class Solution:
    def shortestPath(self, n: int, edges: List[List[int]], labels: str, k: int) -> int:
        graph = [[] for _ in range(n)]

        for u, v, w in edges:
            graph[u].append((v, w))

        # State: (distance, node, last character count)
        start_count = 1
        pq = [(0, 0, start_count)]
        dist = {(0, 1): 0}

        while pq:
            cost, node, count = heapq.heappop(pq)

            if cost != dist.get((node, count), float('inf')):
                continue

            if node == n - 1:
                return cost

            for nei, weight in graph[node]:
                if labels[nei] == labels[node]:
                    new_count = count + 1
                else:
                    new_count = 1

                if new_count > k:
                    continue

                new_cost = cost + weight
                state = (nei, new_count)

                if new_cost < dist.get(state, float('inf')):
                    dist[state] = new_cost
                    heapq.heappush(pq, (new_cost, nei, new_count))

        return -1