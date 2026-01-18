class Solution {
public:
    int largestMagicSquare(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> row(m, vector<int>(n + 1, 0));
        vector<vector<int>> col(n, vector<int>(m + 1, 0));

        // Build row and column prefix sums
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                row[i][j + 1] = row[i][j] + grid[i][j];
                col[j][i + 1] = col[j][i] + grid[i][j];
            }
        }

        auto rowSum = [&](int r, int c1, int c2) {
            return row[r][c2 + 1] - row[r][c1];
        };
        auto colSum = [&](int c, int r1, int r2) {
            return col[c][r2 + 1] - col[c][r1];
        };

        // Try sizes from largest to smallest
        for (int k = min(m, n); k >= 2; --k) {
            if (containsMagic(grid, rowSum, colSum, k)) return k;
        }
        return 1;
    }

private:
    bool containsMagic(const vector<vector<int>>& grid,
                       function<int(int,int,int)> rowSum,
                       function<int(int,int,int)> colSum,
                       int k) {
        int m = grid.size(), n = grid[0].size();
        for (int i = 0; i + k <= m; ++i) {
            for (int j = 0; j + k <= n; ++j) {
                // Target sum from first row of the kxk square
                int target = rowSum(i, j, j + k - 1);

                // Check rows
                bool ok = true;
                for (int r = i; r < i + k && ok; ++r) {
                    if (rowSum(r, j, j + k - 1) != target) ok = false;
                }
                if (!ok) continue;

                // Check columns
                for (int c = j; c < j + k && ok; ++c) {
                    if (colSum(c, i, i + k - 1) != target) ok = false;
                }
                if (!ok) continue;

                // Check main diagonal
                int d1 = 0, d2 = 0;
                for (int t = 0; t < k; ++t) {
                    d1 += grid[i + t][j + t];
                    d2 += grid[i + t][j + k - 1 - t];
                }
                if (d1 == target && d2 == target) return true;
            }
        }
        return false;
    }
};
