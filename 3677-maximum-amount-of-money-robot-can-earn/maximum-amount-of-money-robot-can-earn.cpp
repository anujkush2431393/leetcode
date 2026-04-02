class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();
        const int NEG_INF = -1e9;
        vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(3, NEG_INF)));

        // Base case
        for (int k = 0; k <= 2; k++) {
            dp[0][0][k] = (coins[0][0] >= 0 ? coins[0][0] : (k > 0 ? 0 : coins[0][0]));
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k <= 2; k++) {
                    if (i == 0 && j == 0) continue;

                    int val = coins[i][j];
                    int best = NEG_INF;

                    // From top
                    if (i > 0) best = max(best, dp[i-1][j][k]);
                    // From left
                    if (j > 0) best = max(best, dp[i][j-1][k]);

                    if (best != NEG_INF) {
                        dp[i][j][k] = max(dp[i][j][k], best + val);
                    }

                    // Neutralize robber
                    if (val < 0 && k > 0) {
                        int neutral = NEG_INF;
                        if (i > 0) neutral = max(neutral, dp[i-1][j][k-1]);
                        if (j > 0) neutral = max(neutral, dp[i][j-1][k-1]);
                        if (neutral != NEG_INF) {
                            dp[i][j][k] = max(dp[i][j][k], neutral);
                        }
                    }
                }
            }
        }

        return max({dp[m-1][n-1][0], dp[m-1][n-1][1], dp[m-1][n-1][2]});
    }
};