class Solution {
public:
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) {
        const long long MOD = 1e9 + 7;

        // Add boundary fences (cannot be removed)
        hFences.push_back(1);
        hFences.push_back(m);
        vFences.push_back(1);
        vFences.push_back(n);

        // Sort fences
        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        // Store all possible horizontal distances
        unordered_set<long long> hDist;
        for (int i = 0; i < hFences.size(); i++) {
            for (int j = i + 1; j < hFences.size(); j++) {
                hDist.insert(hFences[j] - hFences[i]);
            }
        }

        long long bestSide = -1;

        // Check vertical distances
        for (int i = 0; i < vFences.size(); i++) {
            for (int j = i + 1; j < vFences.size(); j++) {
                long long d = vFences[j] - vFences[i];
                if (hDist.count(d)) {
                    bestSide = max(bestSide, d);
                }
            }
        }

        // If no square possible
        if (bestSide == -1) return -1;

        // Return area modulo 1e9+7
        return (bestSide * bestSide) % MOD;
    }
};
