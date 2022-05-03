#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class splay_seq {
   public:
    splay_seq(int n = 0) {
        for (int i = 1; i <= n; i++) {
            insert(root, i, i);
            splay(root, i);
        }
    }
    splay_seq(vector<T>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            insert(root, i + 1, vec[i]);
            splay(root, i + 1);
        }
    }
    void dispose() {
        if (root != nullptr) {
            // clog << "Disposed!" << endl;
            root->dispose();
            delete root;
        }
        root = nullptr;
    }
    void append(T val) {
        insert(root, size() + 1, val);
        splay(root, size());
    }
    size_t size() { return (root == nullptr) ? 0 : root->size; }
    void merge(splay_seq& right) {
        if (root == nullptr) {
            root = right.root;
            right.root = nullptr;
            return;
        }
        splay(root, size());
        root->ch[1] = right.root;
        root->maintain();
        right.root = nullptr;
    }
    splay_seq split(int k) {
        if (k > size()) return splay_seq();
        if (k == 0) {
            splay_seq r(root);
            root = nullptr;
            return r;
        }
        splay(root, k);
        splay_seq r(root->ch[1]);
        root->ch[1] = nullptr;
        root->maintain();
        return r;
    }
    void flip() {
        if (root != nullptr) root->flip = !root->flip;
    }
    vector<T> to_vec() {
        vector<T> ret;
        to_vec(root, ret);
        return ret;
    }

   protected:
    struct node {
        node* ch[2];
        int id;
        T val;
        int size = 1;
        bool flip = false;
        node(const int ID = 0, const T& v = 0) : id(ID), val(v) {
            ch[0] = ch[1] = nullptr;
        }
        int where(int k) {
            int rsize = k - ((ch[0] == nullptr) ? 0 : ch[0]->size);
            if (rsize == 1)
                return -1;
            else
                return rsize > 0;
        }
        void maintain() {
            size = 1;
            if (ch[0] != nullptr) size += ch[0]->size;
            if (ch[1] != nullptr) size += ch[1]->size;
        }
        void pushdown() {
            if (flip) {
                // clog << "Push down " << id << endl;
                swap(ch[0], ch[1]);
                if (ch[0] != nullptr) ch[0]->flip = !ch[0]->flip;
                if (ch[1] != nullptr) ch[1]->flip = !ch[1]->flip;
                flip = false;
            }
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
    splay_seq(node* n) { root = n; }
    node* root = nullptr;

    int nodesiz(node* n) { return n == nullptr ? 0 : n->size; }

    // d = 0 : 左， d = 1 : 右
    void rotate(node*& rt, int d) {
        node* nr = rt->ch[d ^ 1];
        nr->pushdown();
        rt->ch[d ^ 1] = nr->ch[d];
        nr->ch[d] = rt;
        rt->maintain();
        nr->maintain();
        rt = nr;
    }

    void insert(node*& rt, const int& id, const T& val) {
        if (rt == nullptr)
            rt = new node(id, val);
        else
            insert(rt->ch[id > rt->id], id, val);
        rt->maintain();
    }

    // 把子树中排名为k的旋转到根
    void splay(node*& rt, int k) {
        if (rt == nullptr) return;
        rt->pushdown();
        int d = rt->where(k);
        if (d == 1) k -= nodesiz(rt->ch[0]) + 1;
        if (d != -1) {
            rt->ch[d]->pushdown();
            int d2 = rt->ch[d]->where(k);
            int k2 = (d2 == 0 ? k : k - nodesiz(rt->ch[d]->ch[0]) - 1);
            if (d2 != -1) {
                splay(rt->ch[d]->ch[d2], k2);
                if (d == d2)
                    rotate(rt, d ^ 1);
                else
                    rotate(rt->ch[d], d);
            }
            rotate(rt, d ^ 1);
        }
    }

    void to_vec(node* rt, vector<T>& vec) {
        if (rt != nullptr) {
            rt->pushdown();
            to_vec(rt->ch[0], vec);
            vec.push_back(rt->val);
            to_vec(rt->ch[1], vec);
        }
    }

   private:
    splay_seq& operator=(const splay_seq& s) = delete;
};