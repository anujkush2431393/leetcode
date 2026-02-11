#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
    struct Node {
        int mn, mx, lazy;
        Node(): mn(0), mx(0), lazy(0) {}
    };
    int n;
    vector<Node> tree;

    SegmentTree(int n): n(n) {
        tree.resize(4*n);
    }

    void push(int idx) {
        if (tree[idx].lazy != 0) {
            for (int child : {idx*2, idx*2+1}) {
                tree[child].mn += tree[idx].lazy;
                tree[child].mx += tree[idx].lazy;
                tree[child].lazy += tree[idx].lazy;
            }
            tree[idx].lazy = 0;
        }
    }

    void pull(int idx) {
        tree[idx].mn = min(tree[idx*2].mn, tree[idx*2+1].mn);
        tree[idx].mx = max(tree[idx*2].mx, tree[idx*2+1].mx);
    }

    void build(int idx, int l, int r) {
        if (l == r) {
            tree[idx].mn = tree[idx].mx = 0;
            return;
        }
        int mid = (l+r)/2;
        build(idx*2, l, mid);
        build(idx*2+1, mid+1, r);
        pull(idx);
    }

    void rangeAdd(int idx, int l, int r, int ql, int qr, int val) {
        if (ql > r || qr < l) return;
        if (ql <= l && r <= qr) {
            tree[idx].mn += val;
            tree[idx].mx += val;
            tree[idx].lazy += val;
            return;
        }
        push(idx);
        int mid = (l+r)/2;
        rangeAdd(idx*2, l, mid, ql, qr, val);
        rangeAdd(idx*2+1, mid+1, r, ql, qr, val);
        pull(idx);
    }

    int queryRightmost(int idx, int l, int r, int target) {
        if (tree[idx].mn > target || tree[idx].mx < target) return -1;
        if (l == r) return l;
        push(idx);
        int mid = (l+r)/2;
        int res = queryRightmost(idx*2+1, mid+1, r, target);
        if (res != -1) return res;
        return queryRightmost(idx*2, l, mid, target);
    }
};

class Solution {
public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();
        SegmentTree seg(n);
        seg.build(1, 0, n-1);

        unordered_map<int, queue<int>> pos;
        for (int i = 0; i < n; i++) {
            pos[nums[i]].push(i);
        }

        // initialize contributions
        for (auto &kv : pos) {
            int val = kv.first;
            int p = kv.second.front();
            int sign = (val % 2 ? +1 : -1);
            seg.rangeAdd(1, 0, n-1, p, n-1, sign);
        }

        int ans = 0;
        for (int l = 0; l < n; l++) {
            int right = seg.queryRightmost(1, 0, n-1, 0);
            if (right != -1 && right >= l) {
                ans = max(ans, right - l + 1);
            }

            int val = nums[l];
            int sign = (val % 2 ? +1 : -1);
            pos[val].pop();
            int next = pos[val].empty() ? n : pos[val].front();
            seg.rangeAdd(1, 0, n-1, l, next-1, -sign);
        }
        return ans;
    }
};