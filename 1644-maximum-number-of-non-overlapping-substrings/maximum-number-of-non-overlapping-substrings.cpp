class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {
        int N = s.size();
        vector<int> left(26, -1), right(26, -1); // the range of each character
        for (int i = 0; i < N; ++i) {
            int c = s[i] - 'a';
            if (left[c] == -1) left[c] = i;
            right[c] = i;
        }
        for (int i = 0; i < 26; ++i) { // An inefficient way of generating the ranges satisfying condition 2.
            if (left[i] == -1) continue;
            for (int j = left[i] + 1; j < right[i]; ++j) {
                int L = left[s[j] - 'a'], R = right[s[j] - 'a'];
                if (L < left[i]) j = L; // rewind
                left[i] = min(left[i], L);
                right[i] = max(right[i], R);
            }
        }
        vector<int> dp(N + 1), pick(N + 1, -1), len(N + 1, N + 1);
        for (int i = 0; i < N; ++i) {
            len[i + 1] = len[i];
            pick[i + 1] = pick[i];
            dp[i + 1] = dp[i];
            int j = 0;
            for (; j < 26; ++j) {
                if (right[j] == i) break;
            }
            if (j == 26 || dp[left[j]] + 1 < dp[i + 1]) continue;
            if (dp[left[j]] + 1 > dp[i + 1] || len[left[j]] + right[j] - left[j] + 1 < len[i]) {
                len[i + 1] = len[left[j]] + right[j] - left[j] + 1; // find a better choice, update the choice.
                pick[i + 1] = j;
            }
            dp[i + 1] = max(dp[i + 1], dp[left[j]] + 1);
        }
        vector<string> ans;
        for (int p = pick[N]; p != -1;) { // reconstruct the substrings.
            int L = left[p], R = right[p];
            ans.push_back(s.substr(L, R - L + 1));
            p = pick[L];
        }
        return ans;
    }
};