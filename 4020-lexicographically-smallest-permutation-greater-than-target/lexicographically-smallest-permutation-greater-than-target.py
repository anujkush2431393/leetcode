class Solution:
    def lexGreaterPermutation(self, s: str, target: str) -> str:
        cnt = [0] * 26

        for ch in s:
            cnt[ord(ch) - ord('a')] += 1

        n = len(s)
        ans = []

        for i in range(n):
            t = ord(target[i]) - ord('a')

            # Case 1: We can keep target[i]
            if cnt[t] > 0:
                cnt[t] -= 1
                ans.append(target[i])
                continue

            # Case 2: Cannot keep target[i]
            # Try to put the smallest character > target[i]
            for c in range(t + 1, 26):
                if cnt[c] > 0:
                    ans.append(chr(c + ord('a')))
                    cnt[c] -= 1

                    # Fill remaining characters in sorted order
                    for x in range(26):
                        ans.extend([chr(x + ord('a'))] * cnt[x])

                    return ''.join(ans)

            # Cannot make the answer greater at this position.
            # Need to backtrack.
            break

        # Backtrack through the prefix
        while ans:
            # Return the last matched character to cnt
            last = ans.pop()
            cnt[ord(last) - ord('a')] += 1

            # Try increasing this position
            last_idx = ord(last) - ord('a')

            for c in range(last_idx + 1, 26):
                if cnt[c] > 0:
                    ans.append(chr(c + ord('a')))
                    cnt[c] -= 1

                    # Fill remaining positions minimally
                    for x in range(26):
                        ans.extend([chr(x + ord('a'))] * cnt[x])

                    return ''.join(ans)

        return ""