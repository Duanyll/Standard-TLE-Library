#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 10;

typedef char value_t;
const int SIGMA = 26;
const int OFFSET = 'a';

class sam {
   protected:
    struct state {
        state* ch[SIGMA];
        // 定义w为这些字符串中最长的一个, 连接到对应于w的最长后缀的另一个
        // endpos 等价类的状态
        state* link;
        int len, size, id;
        state(int i, state* def = nullptr) : id(i) {
            for (int i = 0; i < SIGMA; i++) ch[i] = def;
            link = def;
            len = size = 0;
        }
    };
    state* null;
    state* last;  //整个字符串对应的状态
    state* root;
    state* states[MAXN * 2];
    int state_cnt = 0;

    void insert_char(value_t val) {
        state* p = last;
        state* cur = states[state_cnt] = new state(state_cnt, null);
        state_cnt++;
        cur->size = 1;
        cur->len = p->len + 1;
        while (p != null && p->ch[val] == null) {
            p->ch[val] = cur;
            p = p->link;
        }
        if (p == null)
            cur->link = root;
        else {
            state* q = p->ch[val];
            if (p->len + 1 == q->len)
                cur->link = q;
            else {
                state* clone = states[state_cnt] = new state(state_cnt, null);
                state_cnt++;
                clone->len = p->len + 1;
                memcpy(clone->ch, q->ch, sizeof state::ch);
                clone->link = q->link;
                while (p != null && p->ch[val] == q) {
                    p->ch[val] = clone;
                    p = p->link;
                }
                q->link = cur->link = clone;
            }
        }
        last = cur;
    }

   public:
    sam(const value_t* str) {
        null = new state(-1);
        for (int i = 0; i < SIGMA; i++) null->ch[i] = null;
        null->link = null;
        memset(states, 0, sizeof states);
        last = root = states[state_cnt] = new state(state_cnt, null);
        state_cnt++;
        while (*str != '\0') {
            insert_char(*str - OFFSET);
            str++;
        }
    }

    ~sam() {
        delete null;
        for (int i = 0; i < state_cnt; i++) delete states[i];
    }

    void create_parent_tree(lfs* tree) {
        for (int i = 0; i < state_cnt; i++) {
            tree->dp[i] = states[i]->size;
            tree->len[i] = states[i]->len;
            if (states[i]->link != null) {
                tree->adde(states[i]->link->id, states[i]->id);
            }
        }
    }
};

class sam_noptr {
   protected:
    typedef int ptr;
    ptr ch[MAXN * 2][SIGMA];
    ptr link[MAXN * 2];
    int len[MAXN * 2];
    int size[MAXN * 2];
    ptr null;
    ptr last, root;
    int state_cnt;
    void insert_char(int val) {
        ptr p = last;
        ptr cur = state_cnt++;
        size[cur] = 1;
        len[cur] = len[p] + 1;
        while (p != null && ch[p][val] == null) {
            ch[p][val] = cur;
            p = link[p];
        }
        if (p == null) {
            link[cur] = root;
        } else {
            ptr q = ch[p][val];
            if (len[p] + 1 == len[q]) {
                link[cur] = q;
            } else {
                ptr clone = state_cnt++;
                len[clone] = len[p] + 1;
                memcpy(ch[clone], ch[q], sizeof ch[q]);
                link[clone] = link[q];
                while (p != null && ch[p][val] == q) {
                    ch[p][val] = clone;
                    p = link[p];
                }
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }

   public:
    sam_noptr(const value_t* str) {
        state_cnt = 0;
        memset(ch, 0, sizeof ch);
        memset(link, 0, sizeof link);
        memset(len, 0, sizeof len);
        memset(size, 0, sizeof size);
        null = state_cnt++;
        root = state_cnt++;
        link[root] = null;
        last = root;
        while (*str != '\0') {
            insert_char(*str - OFFSET);
            str++;
        }
    }

    void create_parent_tree(lfs* tree) {
        for (int i = 1; i < state_cnt; i++) {
            tree->dp[i] = size[i];
            tree->len[i] = len[i];
            if (link[i] != null) {
                // clog << "Add e " << link[i] << ' ' << i << endl;
                tree->adde(link[i], i);
            }
        }
    }
};