#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

template <typename T>
class treap {
   protected:
    struct node {
        node* ch[2];
        int r, s;
        T val;
        //返回新节点应该放在那棵子树里
        int where(T x) {
            if (x == val) {
                return -1;
            } else {
                return x < val ? 0 : 1;
            }
        }

        void mt() {
            s = 1;
            if (ch[0] != nullptr) {
                s += ch[0]->s;
            }
            if (ch[1] != nullptr) {
                s += ch[1]->s;
            }
        }

        node() { ch[0] = ch[1] = nullptr; }

        node(T x) {
            ch[0] = ch[1] = nullptr;
            val = x;
            r = rand();
        }

        void dispose() {
            if (ch[0] != nullptr) {
                ch[0]->dispose();
                delete ch[0];
                ch[0] = nullptr;
            }
            if (ch[1] != nullptr) {
                ch[1]->dispose();
                delete ch[1];
                ch[1] = nullptr;
            }
        }
    };

    node* root;
    int cnt;
    // d=0:left,d=1:right
    void rotate(node*& rt, int d) {
        node* nr = rt->ch[d ^ 1];
        rt->ch[d ^ 1] = nr->ch[d];
        nr->ch[d] = rt;
        rt->mt();
        nr->mt();
        rt = nr;
    }

    void insert(node*& rt, T x) {
        if (rt == nullptr) {
            rt = new node(x);
        } else {
            int d = rt->where(x);
            insert(rt->ch[d], x);
            if (rt->ch[d]->r > rt->r) {
                rotate(rt, d ^ 1);
            }
        }
        rt->mt();
    }

    void remove(node*& rt, T x) {
        int d = rt->where(x);
        node* u = rt;
        if (d != -1) {
            remove(rt->ch[d], x);
        } else if (rt->ch[0] == nullptr) {
            rt = rt->ch[1];
            delete u;
        } else if (rt->ch[1] == nullptr) {
            rt = rt->ch[0];
            delete u;
        } else {
            d = (rt->ch[0]->r > rt->ch[1]->r) ? 1 : 0;
            rotate(rt, d);
            remove(rt->ch[d], x);
        }
        if (rt != nullptr) {
            rt->mt();
        }
    }

    bool find(node* rt, T x) {
        while (rt != nullptr) {
            int d = rt->where(x);
            if (d == -1) {
                return true;
            } else {
                assert(rt != rt->ch[d]);
                rt = rt->ch[d];
            }
        }
        return false;
    }

    T kth(node* rt, int k) {
        if (rt == nullptr || k <= 0 || k > rt->s) {
            return 0;
        }
        int s = (rt->ch[1] == nullptr) ? 0 : rt->ch[1]->s;
        if (k == s + 1) {
            return rt->val;
        } else if (k <= s) {
            return kth(rt->ch[1], k);
        } else {
            return kth(rt->ch[0], k - s - 1);
        }
    }

    void mergefrom(node* src) {
        if (src->ch[0] != nullptr) {
            mergefrom(src->ch[0]);
        }
        if (src->ch[1] != nullptr) {
            mergefrom(src->ch[1]);
        }
        insert(src->v);
    }

   public:
    treap() {
        root = nullptr;
        cnt = 0;
    }

    ~treap() {
        if (root != nullptr) {
            root->dispose();
        }
        delete root;
        root = nullptr;
    }

    bool insert(T x) {
        if (find(root, x) == false) {
            insert(root, x);
            cnt++;
            return true;
        } else {
            return false;
        }
    }

    bool remove(T x) {
        if (find(root, x)) {
            remove(root, x);
            cnt--;
            return true;
        } else {
            return false;
        }
    }

    bool find(T x) { return find(root, x); }

    int count() { return cnt; }

    bool empty() { return cnt == 0; }

    void clear() {
        if (root != nullptr) {
            root->dispose();
        }
        delete root;
        root = nullptr;
        cnt = 0;
    }

    T kth(int k) {
        if (k > cnt) {
            return 0;
        } else {
            return kth(root, k);
        }
    }

    void mergefrom(treap src) {
        if (src == nullptr) {
            return;
        }
        mergefrom(src.root);
    }
};
