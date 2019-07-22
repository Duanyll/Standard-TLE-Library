#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef long long int64;

const int INF = 0x3f3f3f3f;

template <typename value_t>
class lct {
   protected:
    struct node {
        node* ch[2];  // 左儿子在原树中深度更浅, 右儿子更深
        node* fa;     // splay链上的父指针
        node* top;  // splay根的虚边指针, 若不是splay的根则为nullptr
        value_t val, sum;
        int id;
        bool flip = false;
        node(value_t v, int i, node* def = nullptr) : val(v), sum(v), id(i) {
            ch[0] = ch[1] = fa = top = def;
        }
        // 这个节点是不是某一个splay的根
        bool is_splay_root() { return top != nullptr; }
        // 更新sum信息
        void push_up() {
            // clog << id << ' ' << val << '+'
            //      << ((ch[0] == nullptr) ? 0 : ch[0]->val) << '+'
            //      << ((ch[1] == nullptr) ? 0 : ch[1]->val);
            sum = val;
            if (ch[0] != nullptr) sum ^= ch[0]->sum;
            if (ch[1] != nullptr) sum ^= ch[1]->sum;
            // clog << " = " << sum << endl;
        }
        // 下传翻转信息
        void push_down() {
            if (flip) {
                swap(ch[0], ch[1]);
                if (ch[0] != nullptr) ch[0]->flip ^= 1;
                if (ch[1] != nullptr) ch[1]->flip ^= 1;
                flip = false;
            }
        }
        // 使fa成为自己的左/右儿子. 在splay树中升高rt
        void rotate(int d) {
            // 方便起见, 下列代码保留this
            node* cur = this->fa;
            this->fa = cur->fa;
            if (cur->fa != nullptr) {
                if (cur->fa->ch[0] == cur)
                    cur->fa->ch[0] = this;
                else
                    cur->fa->ch[1] = this;
            }
            cur->ch[d ^ 1] = this->ch[d];
            if (cur->ch[d ^ 1] != nullptr) cur->ch[d ^ 1]->fa = cur;
            this->ch[d] = cur;
            cur->fa = this;
            cur->push_up();
            this->push_up();
            // 旋转使this升高, 应转移top指针
            this->top = cur->top;
            cur->top = nullptr;
        }

        // 使rt成为rt所在splay树中的根节点
        void splay() {
            while (fa != nullptr) {
                node* cur = fa;
                cur->push_down();
                if (cur->ch[0] != nullptr) cur->ch[0]->push_down();
                if (cur->ch[1] != nullptr) cur->ch[1]->push_down();
                // rt作为cur的孩子之一已经pushdown了
                // cur作为rt的孩子时在反方向
                if (cur->ch[0] == this)
                    rotate(1);
                else
                    rotate(0);
            }
        }

        // 改变点权
        void change_value(value_t v) {
            splay();
            push_down();
            val = v;
            push_up();
        }

        void display() {
            push_down();
            clog << '(';
            if (ch[0] != nullptr) {
                ch[0]->display();
                clog << ", ";
            }
            clog << id;
            if (ch[1] != nullptr) {
                clog << ", ";
                ch[1]->display();
            }
            clog << ')';
        }
    };

    vector<node*> pool;  // 指向编号为id的点, 下标从1开始, 垫一个nullptr

    // 使rt和rt所在子树的根节点位于一条重链的两端
    void access(node* x) {
        if (x == nullptr) return;
        x->splay();

        // 断开x的右儿子
        x->push_down();
        if (x->ch[1] != nullptr) {
            x->ch[1]->fa = nullptr;
            x->ch[1]->top = x;
            x->ch[1] = nullptr;
        }
        x->push_up();

        // 依次转移路径上的重链
        while (x->top != nullptr) {
            node* cur = x->top;
            cur->splay();
            // 先断开原有重链
            cur->push_down();
            if (cur->ch[1] != nullptr) {
                cur->ch[1]->fa = nullptr;
                cur->ch[1]->top = cur;
                cur->ch[1] = nullptr;
            }
            // 再连上新的重链
            cur->ch[1] = x;
            x->fa = cur;
            x->top = nullptr;
            cur->push_up();
            x = cur;
        }
        x->splay();  // 保证复杂度
    }

    // 找到原树中的树根
    node* find_root(node* x) {
        if (x == nullptr) return nullptr;
        access(x);
        x->splay();
        x->push_down();
        while (x->ch[0] != nullptr) x = x->ch[0];  // splay过程中已经pushdown了
        x->splay();                                // 保证复杂度
        return x;
    }

    bool is_connected(node* a, node* b) { return find_root(a) == find_root(b); }

    // 重设原树中的树根
    void make_root(node* x) {
        if (x == nullptr) return;
        access(x);
        x->splay();
        x->flip ^= 1;
        x->push_down();
    }

    // 如果a, b之间可以连边, 就连一条虚边
    void link(node* a, node* b) {
        if (is_connected(a, b)) return;
        // a是根, b连到a上
        make_root(a);
        a->splay();
        a->push_down();
        access(b);
        b->splay();
        b->push_down();

        a->ch[0] = b;
        b->fa = a;
        b->top = nullptr;
        a->push_up();
    }

    // 如果a, b之间恰好有一条边, 就断开它
    void cut(node* a, node* b) {
        if (!is_connected(a, b)) return;
        make_root(a);
        access(b);
        b->splay();
        b->push_down();
        // 判断边是否存在并删除(看a, b在排序二叉树上是否相邻)
        if (b->ch[0] == a && b->ch[0]->ch[1] == nullptr) {
            // 直接双向断开
            a->fa = a->top = nullptr;
            b->ch[0] = nullptr;
        }
        b->push_up();
    }

    // 查询a到b的路径
    value_t query(node* a, node* b) {
        // assert(is_connected(a, b));
        make_root(a);
        a->splay();
        a->push_down();
        access(b);
        b->splay();
        b->push_down();
        return b->sum;
    }

   public:
    // 创建一个空的lct
    lct() { pool.push_back(nullptr); }
    ~lct() {
        for (auto i : pool)
            if (i != nullptr) delete i;
    }
    // 返回lct中节点数量
    int size() { return pool.size() - 1; }

    // 新建一个孤立节点
    void insert_node(value_t val) {
        pool.push_back(new node(val, pool.size()));
    }
    // 尝试链接a, b边
    void insert_edge(int a, int b) { link(pool[a], pool[b]); }

    // 尝试删除a, b边
    void erase_edge(int a, int b) { cut(pool[a], pool[b]); }

    // 修改点权
    void assign_node(int u, value_t x) { pool[u]->change_value(x); }

    // 查询a, b之间的路径; 若a, b不连通, 则断言失败
    value_t query_path(int a, int b) { return query(pool[a], pool[b]); }

    void display_subtree(int a) { pool[a]->display(); }
};