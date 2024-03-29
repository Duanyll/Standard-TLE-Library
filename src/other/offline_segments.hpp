#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;

struct segment {
    int id;
    int l, r;
    int ans;
};

template <typename TQuery, typename TAns>
void offline_segments(int n, vector<TQuery>& queries,
                      function<void(int, TAns&)> add,
                      function<void(int, TAns&)> del, TAns ans_reset = TAns()) {
    int block_size = ceil(sqrt(n));
    sort(queries.begin(), queries.end(),
         [&](const auto& a, const auto& b) -> bool {
             if (a.l / block_size != b.l / block_size) {
                 return a.l / block_size < b.l / block_size;
             } else if ((a.l / block_size) & 1) {
                 return a.r < b.r;
             } else {
                 return a.r > b.r;
             }
         });

    int l = 1;
    int r = 1;
    TAns ans = ans_reset;
    add(1, ans);
    for (auto& q : queries) {
        while (l > q.l) add(--l, ans);
        while (r < q.r) add(++r, ans);
        while (l < q.l) del(l++, ans);
        while (r > q.r) del(r--, ans);
        q.ans = ans;
    }
}

template <typename TQuery, typename TAns>
void offline_segments(int n, vector<TQuery>& queries,
                      function<void(TQuery&)> direct_process,
                      function<void(int, TAns&)> add, function<void(int)> del,
                      TAns ans_reset = TAns()) {
    // 划分分块
    int block_size = sqrt(n);
    int block_count = n / block_size;
    vector<int> block_l(block_count + 2), block_r(block_count + 2);
    for (int i = 1; i <= block_count; i++) {
        block_l[i] = (i - 1) * block_size + 1;
        block_r[i] = i * block_size;
    }
    if (block_r[block_count] < n) {
        block_count++;
        block_l[block_count] = block_r[block_count - 1] + 1;
        block_r[block_count] = n;
    }
    vector<int> block(n + 1);
    for (int i = 1; i <= block_count; i++) {
        for (int j = block_l[i]; j <= block_r[i]; j++) {
            block[j] = i;
        }
    }

    // 排序询问
    sort(queries.begin(), queries.end(),
         [&](const auto a, const auto b) -> bool {
             if (block[a.l] == block[b.l]) {
                 return a.r < b.r;
             } else {
                 return block[a.l] < block[b.l];
             }
         });

    TAns ans;
    int last_block = 0;
    int l = 1;
    int r = 0;
    // 处理询问
    for (auto& q : queries) {
        if (block[q.l] == block[q.r]) {
            direct_process(q);
            continue;
        }

        if (block[q.l] != last_block) {
            while (l <= r) del(l++);
            l = block_r[block[q.l]] + 1;
            r = block_r[block[q.l]];
            ans = TAns();
            last_block = block[q.l];
        }
        while (r < q.r) add(++r, ans);

        int l_tmp = l;
        TAns ans_tmp = ans;
        while (l_tmp > q.l) add(--l_tmp, ans_tmp);
        q.ans = ans_tmp;

        while (l_tmp < l) del(l_tmp++);
    }
}