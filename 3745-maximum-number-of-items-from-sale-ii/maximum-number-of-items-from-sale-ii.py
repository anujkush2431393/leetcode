class Solution:
    def maximumSaleItems(self, items: List[List[int]], budget: int) -> int:
        max_factor = max(factor for factor, _ in items)
        min_price = min(price for _, price in items)

        # Count occurrences of each factor, then sum multiples for every factor
        factor_cnt = [0] * (max_factor + 1)
        for factor, _ in items:
            factor_cnt[factor] += 1

        multiples_cnt = [0] * (max_factor + 1)
        for d in range(1, max_factor + 1):
            if factor_cnt[d]:
                for mult in range(d, max_factor + 1, d):
                    multiples_cnt[d] += factor_cnt[mult]

        # Each item i with `gain = multiples_cnt[factor] - 1 > 0` provides `gain`
        # marginal purchases worth 2 items each at cost `price`
        boosted_by_price = defaultdict(int)
        for factor, price in items:
            gain = multiples_cnt[factor] - 1
            if gain > 0 and price < 2 * min_price:
                boosted_by_price[price] += gain

        total_items = 0
        for price in sorted(boosted_by_price):
            available = boosted_by_price[price]
            buy = min(available, budget // price)
            total_items += 2 * buy
            budget -= buy * price
            if budget < price:
                break

        # Spend remaining budget on the cheapest item (1 item per min_price)
        total_items += budget // min_price
        return total_items
