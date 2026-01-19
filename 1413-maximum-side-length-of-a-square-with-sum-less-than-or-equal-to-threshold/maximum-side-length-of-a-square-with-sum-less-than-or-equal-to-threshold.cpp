class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        int m = mat.size(), n = mat[0].size();
        
        // Build prefix sum matrix
        vector<vector<int>> ps(m+1, vector<int>(n+1, 0));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                ps[i][j] = mat[i-1][j-1] 
                         + ps[i-1][j] 
                         + ps[i][j-1] 
                         - ps[i-1][j-1];
            }
        }
        
        // Helper to check if square of size len exists
        auto can = [&](int len) {
            for (int i = len; i <= m; i++) {
                for (int j = len; j <= n; j++) {
                    int sum = ps[i][j] - ps[i-len][j] - ps[i][j-len] + ps[i-len][j-len];
                    if (sum <= threshold) return true;
                }
            }
            return false;
        };
        
        // Binary search
        int lo = 0, hi = min(m, n), ans = 0;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (can(mid)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        return ans;
    }
};
