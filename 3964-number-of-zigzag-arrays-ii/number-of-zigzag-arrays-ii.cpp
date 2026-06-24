class Solution {
public:
    static const int MOD = 1e9 + 7;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();

        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {

                if (A[i][k] == 0) continue;

                for (int j = 0; j < n; j++) {

                    if (B[k][j] == 0) continue;

                    C[i][j] =
                        (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }

        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();

        Matrix res(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++)
            res[i][i] = 1;

        while (exp) {

            if (exp & 1)
                res = multiply(res, base);

            base = multiply(base, base);

            exp >>= 1;
        }

        return res;
    }

    int zigZagArrays(int n, int l, int r) {

        int m = r - l + 1;
        int S = 2 * m;

        // Transition matrix
        Matrix T(S, vector<long long>(S, 0));

        // States:
        // 0 ... m-1     => up
        // m ... 2m-1    => down

        for (int y = 0; y < m; y++) {

            // up[y] -> down[z] where z < y
            for (int z = 0; z < y; z++) {
                T[m + z][y] = 1;
            }

            // down[y] -> up[z] where z > y
            for (int z = y + 1; z < m; z++) {
                T[z][m + y] = 1;
            }
        }

        // Initial vector for length = 2
        vector<long long> init(S, 0);

        for (int a = 0; a < m; a++) {

            for (int b = 0; b < m; b++) {

                if (a == b)
                    continue;

                if (a < b)
                    init[b]++;

                else
                    init[m + b]++;
            }
        }

        // Apply T^(n-2)
        Matrix P = power(T, n - 2);

        vector<long long> finalState(S, 0);

        for (int i = 0; i < S; i++) {

            for (int j = 0; j < S; j++) {

                finalState[i] =
                    (finalState[i] +
                     P[i][j] * init[j]) % MOD;
            }
        }

        long long ans = 0;

        for (long long x : finalState)
            ans = (ans + x) % MOD;

        return ans;
    }
};