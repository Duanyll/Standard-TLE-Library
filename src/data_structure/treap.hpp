#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

template <typename T, bool is_multi = false, T INF = 0x3f3f3f3f>
class treap {
   protected:
    struct node {
        node* ch[2];
        int r, s;
        T val;
        int count = 1; 
        //返回新节点应该放在那棵子树里
        int where(T x) {
            if(is_multi){
                return x < val ? 0 : 1;
            } else {
                if (x == val) {
                    return -1;
                } else {
                    return x < val ? 0 : 1;
                }
            }
        }

        void mt() {
            s = count;
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
        } else if (rt->val == x) {
        	rt->count++;
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
        if (rt->val != x) {
            remove(rt->ch[d], x);
        } else if (rt->count > 1) {
        	rt->count--;
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

    node* find(node* rt, T x) {
        while (rt != nullptr) {
            int d = rt->where(x);
            if (rt->val == x) {
                return rt;
            } else {
                assert(rt != rt->ch[d]);
                rt = rt->ch[d];
            }
        }
        return nullptr;
    }

    T kth(node* rt, int k) {
        if (rt == nullptr || k < 0 || k > rt->s) {
            // clog << "Oops!" << endl;
            return INF;
        }
        int s = (rt->ch[0] == nullptr) ? 0 : rt->ch[0]->s;
        if (k >= s + 1 && k <= s + rt->count) {
            return rt->val;
        } else if (k <= s) {
            return kth(rt->ch[0], k);
        } else {
            return kth(rt->ch[1], k - s - rt->count);
        }
    }

    int rank(node* rt, T x) {
        int s = (rt->ch[0] == nullptr) ? 0 : rt->ch[0]->s;
        if (rt->val == x) {
            return s + 1;
        } else if (rt->val > x) {
            return rank(rt->ch[0], x);
        } else {
            return rank(rt->ch[1], x) + s + rt->count;
        }
    }

    void prev(node* rt, T x, T& result) {
        if (rt == nullptr) {
            return;
        }
        if (rt->val < x) {
            result = max(result, rt->val);
            prev(rt->ch[1], x, result);
        } else {
            prev(rt->ch[0], x, result);
        }
    }

    void succ(node* rt, T x, T& result) {
        if (rt == nullptr) {
            return;
        }
        if (rt->val > x) {
            result = min(result, rt->val);
            succ(rt->ch[0], x, result);
        } else {
            succ(rt->ch[1], x, result);
        }
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
        if (!is_multi) {
            if (find(root, x) != nullptr) {
                return false;
            }
        }
        cnt++;
        insert(root, x);
        return true;
    }

    bool erase(T x) {
        node* cur = find(root, x);
        if (cur != nullptr) {
            cnt--;
            remove(root, x);
            return true;
        } else {
            return false;
        }
    }

    bool find(T x) { return find(root, x) != nullptr; }

    int size() { return cnt; }

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
            return INF;
        } else {
            return kth(root, k);
        }
    }

    int rank(T x) {
        if (find(root, x) == nullptr) {
            return -1;
        }
        return rank(root, x);
    }

    T succ(T x){
        T result = INF;
        succ(root, x, result);
        return result;
    }

    T prev(T x){
        T result = -INF;
        prev(root, x, result);
        return result;
    }
};
