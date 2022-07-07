# Standard-TLE-Library Offline for XCPC

- [Standard-TLE-Library Offline for XCPC](#standard-tle-library-offline-for-xcpc)
  - [数据结构](#数据结构)
    - [笛卡尔树](#笛卡尔树)
    - [DLX](#dlx)
    - [树状数组](#树状数组)
      - [人人都会的](#人人都会的)
      - [区间修改, 区间查询](#区间修改-区间查询)
      - [二维前缀和](#二维前缀和)
      - [二维矩阵修改, 矩阵查询](#二维矩阵修改-矩阵查询)
    - [LCT](#lct)
    - [线段树](#线段树)
      - [先进的模板化线段树](#先进的模板化线段树)
    - [不那么先进的线段树](#不那么先进的线段树)
    - [ST 表](#st-表)
    - [Splay](#splay)
    - [树链剖分](#树链剖分)
    - [Treap](#treap)
  - [图论](#图论)
    - [边双连通分量与染色](#边双连通分量与染色)
    - [点双连通分量和割点](#点双连通分量和割点)
    - [Dinic 网络流](#dinic-网络流)
    - [EK 网络流](#ek-网络流)
    - [Kruscal 最小生成树](#kruscal-最小生成树)
    - [倍增 LCA](#倍增-lca)
    - [链式前向星](#链式前向星)
    - [最小费用最大流](#最小费用最大流)
    - [网络流基类](#网络流基类)
    - [有向图强连通分量](#有向图强连通分量)
    - [最短路](#最短路)
      - [Dijkstra](#dijkstra)
      - [SPFA](#spfa)
    - [拓扑排序](#拓扑排序)
    - [矩阵树定理](#矩阵树定理)
    - [最小树形图](#最小树形图)
    - [全局最小割](#全局最小割)
  - [数学](#数学)
    - [组合数](#组合数)
      - [组合数递推](#组合数递推)
      - [卢卡斯定理](#卢卡斯定理)
    - [Exgcd](#exgcd)
    - [高斯消元相关](#高斯消元相关)
      - [解线性方程组](#解线性方程组)
      - [行列式](#行列式)
    - [多项式](#多项式)
    - [质数](#质数)
      - [线性筛](#线性筛)
      - [欧拉 Phi 函数](#欧拉-phi-函数)
      - [MR 素数测试](#mr-素数测试)
  - [其他](#其他)
    - [AC 自动机](#ac-自动机)
    - [IO 优化](#io-优化)
    - [KMP](#kmp)
      - [EXKMP](#exkmp)
    - [马拉车](#马拉车)
    - [归并排序](#归并排序)
    - [莫队](#莫队)
      - [普通莫队](#普通莫队)
      - [不删除莫队](#不删除莫队)
      - [树上莫队](#树上莫队)
    - [模拟退火](#模拟退火)
    - [后缀自动机](#后缀自动机)
    - [后缀数组](#后缀数组)
  - [对拍](#对拍)
    - [Shell](#shell)
    - [PowerShell](#powershell)

## 数据结构

### 笛卡尔树

给定一个 $1 \sim n$ 的排列 $p$，构建其笛卡尔树。

即构建一棵二叉树，满足：

1. 每个节点的编号满足二叉搜索树的性质。
2. 节点 $i$ 的权值为 $p_i$，每个节点的权值满足小根堆的性质。

```cpp
class cartesian_tree {
   protected:
    int lson[MAXN], rson[MAXN], rt;
    int s[1000], top;
    int* a;

   public:
    cartesian_tree(int n, int* a) {
        memset(lson, 0, sizeof lson);
        memset(rson, 0, sizeof rson);
        top = 0;
        this->a = a;
        for (int i = 1; i <= n; i++) {
            while (top && a[s[top]] <= a[i]) {
                lson[i] = s[top--];
            }
            rson[s[top]] = i;
            s[++top] = i;
        }
        rt = s[1];
    }

    int query(int l, int r) {
        int x = rt;
        do {
            if (l <= x && x <= r) {
                return a[x];
            }
        } while (x = (r < x ? lson : rson)[x]);
    }
};
```

### DLX

精确覆盖问题: 选择特定的行使得所有的列有且只含有一个 1.

```cpp
const int N = 4;
const int SIZE = N * N;
const int ROW = SIZE * SIZE * SIZE + 10;  //
const int COL = SIZE * SIZE * N + 10;     // 这三个常数是必须的
const int POINT = ROW * 4 + COL;          //
class dlx {
   public:
    int n, m;
    int pcnt;
    int ansc, ans[ROW];

    dlx(int N, int M) : n(N), m(M) {
        pcnt = 0;
        ansc = 0;
        memset(ans, 0, sizeof ans);
        memset(p, 0, sizeof p);
        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);

        for (int i = 0; i <= m; i++) {
            col[i] = 0;
            p[i].u = p[i].d = i;
            p[i].l = i - 1;
            p[i].r = i + 1;
        }
        p[0].l = m;
        p[m].r = 0;
        pcnt = m;
        for (int i = 1; i <= n; i++) {
            row[i] = -1;
        }
    }

    void insert(int r, int c) {
        pcnt++;
        p[pcnt].col = c;
        col[c]++;
        p[pcnt].row = r;
        p[pcnt].d = p[c].d;
        p[p[c].d].u = pcnt;
        p[pcnt].u = c;
        p[c].d = pcnt;

        if (row[r] == -1) {
            row[r] = p[pcnt].l = p[pcnt].r = pcnt;
        } else {
            p[pcnt].r = p[row[r]].r;
            p[p[row[r]].r].l = pcnt;
            p[pcnt].l = row[r];
            p[row[r]].r = pcnt;
        }
    }

    bool search(int d) {
        // clog << "enter" << d << endl;
        if (p[0].r == 0) {
            ansc = d;
            return true;
        }
        int c = p[0].r;
        for (int i = p[0].r; i != 0; i = p[i].r) {
            if (col[i] < col[c]) {
                c = i;
            }
        }
        remove(c);
        for (int i = p[c].d; i != c; i = p[i].d) {
            ans[d] = p[i].row;
            for (int j = p[i].r; j != i; j = p[j].r) {
                remove(p[j].col);
            }
            if (search(d + 1)) {
                return true;
            }
            for (int j = p[i].l; j != i; j = p[j].l) {
                resume(p[j].col);
            }
        }
        resume(c);
        // clog << "exit " << d << endl;
        return false;
    }

   protected:
    struct node {
        int u, d, l, r;
        int row, col;
    } p[POINT];
    int row[ROW];
    int col[COL];

    void remove(int c) {
        // clog << "remove " << c << endl;
        p[p[c].r].l = p[c].l;
        p[p[c].l].r = p[c].r;
        for (int i = p[c].d; i != c; i = p[i].d) {
            for (int j = p[i].r; j != i; j = p[j].r) {
                p[p[j].d].u = p[j].u;
                p[p[j].u].d = p[j].d;
                col[p[j].col]--;
            }
        }
    }

    void resume(int c) {
        // clog << "resume " << c << endl;
        for (int i = p[c].u; i != c; i = p[i].u) {
            for (int j = p[i].l; j != i; j = p[j].l) {
                p[p[j].d].u = p[p[j].u].d = j;
                col[p[j].col]++;
            }
        }
        p[p[c].r].l = p[p[c].l].r = c;
    }
};

```

### 树状数组

```cpp
template <typename value_t>
class fenwick {
   public:
    fenwick(int n) : n(n), c(n + 1, 0) {}

    void add(int i, value_t x) {
        while (i <= n) {
            c[i] += x;
            i += lowbit(i);
        }
    }

    value_t sum(int x) {
        value_t sum = 0;
        while (x > 0) {
            sum += c[x];
            x -= lowbit(x);
        }
        return sum;
    }

    value_t sum(int l, int r) { return sum(r) - sum(l - 1); }

   private:
    vector<value_t> c;
    int n;

    inline int lowbit(int x) { return x & (-x); }
};
```

树状数组是一种能够$O(\log n)$在线维护前缀和的数据结构, 其写法简单常数小... 不具体介绍了, 看看一些奇妙的操作吧.

#### 人人都会的

+ 单点修改, 区间查询: 基本维护前缀和
+ 区间修改, 单点查询: 维护差分

#### 区间修改, 区间查询

引入数组$d$, $d_i$表示区间$[i, n]$中需要加值的差分, 进行区间加法时, 就直接对$d$操作, 对$d_l$加上$x$, 对$d_{r+1}$减去$x$. 查询前缀和时, 设$sum_i$为区间$[1,i]$的元素和, 易得

$$
\begin{aligned}
    sum_i &= \sum_{j=1}^i(a_j) + \sum_{j=1}^i\sum_{k=1}^j(d_k) \\
          &= \sum_{j=1}^i(a_j) + \sum_{j=1}^i(d_j\times(i-j+1)) \\
          &= \sum_{j=1}^i(a_j) + (i+1)\sum_{j=1}^i(d_j) + \sum_{j=1}^i(d_j*j) 
\end{aligned}
$$
  
发现我们需要维护$a_i$, $d_i$, $d_i\times i$的前缀和. 代码可以这样写:

```cpp
int suma[MAXN], sumd[MAXN], sumdi[MAXN];

void update(int* c, int pos, int x) {
    while (pos <= n) {
        c[pos] += x;
        pos += lowbit(pos);
    }
}

void sum(int* c, int pos) {
    int res = 0;
    while (pos >= 1) {
        res += c[pos];
        pos -= lowbit(pos);
    }
}

void add(int l, int r, int x) {
    update(sumd, l, x);
    update(sumd, r + 1, -x);
    update(sumdi, l, l * x);
    update(sumdi, r + 1, -(r + 1) * x);
}

int query(int l, int r) {
    return suma[r] + r * sum(sumd, r) + sum(sumdi, r)
           - (suma[l - 1] + (l - 1) * sum(sumd, l - 1) + sum(sumdi, l));
}
```

#### 二维前缀和

首先, 由二维前缀和求矩阵$(x_1, y_1)\rightarrow(x_2,y_2)$的操作方法:

$$
sum=sum[x_2][y_2]-sum[x_1-1][y_2]-sum[x_2][y_1-1]+sum[x_1-1][x_2-1]
$$

用树状数组维护二维前缀和的方法: 

```cpp
void update(int x, int y, int val) {
    while (x <= n) {
        int t = y;
        while (t <= m) {
            c[x][t] += val;
            t += lowbit(t);
        }
        x += lowbit(x);
    }
}

int query(int x, int y) {
    int res = 0;
    while (x >= 1) {
        int t = y;
        while (t >= 1) {
            res += c[x][t]
            t -= lowbit(t);
        }
        x -= lowbit(x);
    }
    return res;
}
```

因此不难做到二维单点修改, 矩阵查询.
  
#### 二维矩阵修改, 矩阵查询

首先说明一下二维差分怎么写. 由二维前缀和的形式, 定义

$$
d[i][j] = a[i][j] - a[i-1][j] - a[i][j-1] + a[i-1][j-1]
$$

因此

$$
a[i][j] = \sum_{n=1}^i\sum_{m=1}^j(d[n][m])
$$

即可用二维树状数组维护差分.

比如给一个$5\times5$的矩阵中间$3\times3$的部分加上$x$, 可以这么修改差分数组: 

```
 0  0  0  0  0
 0 +x  0  0 -x
 0  0  0  0  0
 0  0  0  0  0
 0 -x  0  0 +x
```

所以矩阵修改操作的写法:

```cpp
void add(int x1, int y1, int x2, int y2, int x) {
    update(x1, y1, x);
    update(x1, y2 + 1, -x);
    update(x2 + 1, y1, -x);
    update(x2 + 1, y2 + 1, x);
} 
```

为了实现二维区间修改和查询的操作, 我们可以类比一维的情况, 用差分来表示前缀和.

$$
\begin{aligned}    
sum[x][y] &= \sum_{i=1}^x\sum_{j=1}^y(a[i][j]) \\
          &= \sum_{i=1}^x\sum_{j=1}^y\sum_{n=1}^i\sum_{m=1}^j(d[n][m])
\end{aligned}
$$

根据前面的套路, 我们统计每一个$d[i][j]$的出现次数, 可以展开两层$\Sigma$:
$$
\begin{aligned}    
sum[x][y] =& \sum_{i=1}^x\sum_{j=1}^yd[i][j] * (x-i+1) * (y-j+1) \\
          =& (x+1)*(y+1)\sum_{i=1}^x\sum_{j=1}^yd[i][j] \\
           & -(y+1)\sum_{i=1}^x\sum_{j=1}^yd[i][j]*i-(x+1)\sum_{i=1}^x\sum_{j=1}^yd[i][j]*j \\
           & +\sum_{i=1}^x\sum_{j=1}^yd[i][j]*i*j
\end{aligned}
$$

也就是说, 我们需要维护

+ $\sum_{i=1}^x\sum_{j=1}^yd[i][j]$
+ $\sum_{i=1}^x\sum_{j=1}^yd[i][j]*i$
+ $\sum_{i=1}^x\sum_{j=1}^yd[i][j]*j$ 
+ $\sum_{i=1}^x\sum_{j=1}^yd[i][j]*i*j$

开四个树状数组即可. 这样用树状数组写, 常数会比线段树小一些.

### LCT

```cpp
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
```

### 线段树

#### 先进的模板化线段树

```cpp
struct segtree_data_store {
    int64 addv = 0;
    int64 mulv = 1;
    int64 sum = 0;
    int len = 1;

    segtree_data_store() {}
    segtree_data_store(int val) : sum(val) {}

    void push_down(segtree_data_store& lson, segtree_data_store& rson) {
        if (mulv != 1) {
            lson.mulv *= mulv;
            rson.mulv *= mulv;
            lson.addv *= mulv;
            rson.addv *= mulv;
            lson.sum *= mulv;
            rson.sum *= mulv;
            mulv = 1;
        }
        if (addv != 0) {
            lson.addv += addv;
            rson.addv += addv;
            lson.sum += addv * (len - len / 2);
            rson.sum += addv * (len / 2);
            addv = 0;
        }
    }

    void push_up(segtree_data_store& lson, segtree_data_store& rson) {
        sum = lson.sum + rson.sum;
        len = lson.len + rson.len;
    }
};

struct segtree_query_sum {
    int64 sum = 0;
    segtree_query_sum() {}
    segtree_query_sum(segtree_data_store& seg) : sum(seg.sum) {}
    void merge_left(segtree_query_sum lson) { sum += lson.sum; }
    void merge_right(segtree_query_sum rson) { sum += rson.sum; }
};

struct segtree_update_mul {
    int64 val = 0;
    segtree_update_mul(int64 mul) : val(mul) {}
    void apply(segtree_data_store& seg) const {
        seg.mulv *= val;
        seg.addv *= val;
        seg.sum *= val;
    }
};

struct segtree_update_add {
    int64 val = 0;
    segtree_update_add(int64 add) : val(add) {}
    void apply(segtree_data_store& seg) const {
        seg.addv += val;
        seg.sum += val * int64(seg.len);
    }
};

class segtree {
   public:
    segtree(int n) : n(n), s((n << 2) + 1) { build(1, n, 1); }
    template <typename TBaseData>
    segtree(int n, TBaseData* data) : n(n), s((n << 2) + 1) {
        build(data, 1, n, 1);
    }

    int n;

    template <typename TUpdate>
    void update(int L, int R, const TUpdate& data) {
        update(L, R, data, 1, n, 1);
    }

    template <typename TQuery>
    TQuery query(int L, int R) {
        return query<TQuery>(L, R, 1, n, 1);
    }

   protected:
    vector<segtree_data_store> s;

#define LSON l, mid, rt << 1
#define RSON mid + 1, r, rt << 1 | 1

    void build(int l, int r, int rt) {
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(LSON);
        build(RSON);
        s[rt].push_up(s[rt << 1], s[rt << 1 | 1]);
    }

    template <typename TBaseData>
    void build(TBaseData* data, int l, int r, int rt) {
        if (l == r) {
            s[rt] = data[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(data, LSON);
        build(data, RSON);
        s[rt].push_up(s[rt << 1], s[rt << 1 | 1]);
    }

    template <typename TUpdate>
    void update(int L, int R, const TUpdate& data, int l, int r, int rt) {
        if (L <= l && r <= R) {
            data.apply(s[rt]);
            return;
        }
        s[rt].push_down(s[rt << 1], s[rt << 1 | 1]);
        int mid = (l + r) >> 1;
        if (L <= mid) update(L, R, data, LSON);
        if (R > mid) update(L, R, data, RSON);
        s[rt].push_up(s[rt << 1], s[rt << 1 | 1]);
    }

    template <typename TQuery>
    TQuery query(int L, int R, int l, int r, int rt) {
        if (L <= l && r <= R) {
            return TQuery(s[rt]);
        }
        s[rt].push_down(s[rt << 1], s[rt << 1 | 1]);
        int mid = (l + r) >> 1;
        TQuery res;
        if (L <= mid) res.merge_left(query<TQuery>(L, R, LSON));
        if (R > mid) res.merge_right(query<TQuery>(L, R, RSON));
        return res;
    }

#undef LSON
#undef RSON
};
```

### 不那么先进的线段树

```cpp
template <typename value_t>
class segtree {
   public:
    segtree() {}
    segtree(int cnt) {
        this->cnt = cnt;
        memset(sum, 0, sizeof sum);
        memset(lazy, 0, sizeof lazy);
    }
    void init() { build_from_cin(1, cnt, 1); }
    void init(value_t *num, int *rnk) {
        this->num = num;
        this->rnk = rnk;
        build(1, cnt, 1);
    }
    void add_range(int l, int r, value_t val) { update(l, r, val, 1, cnt, 1); }
    value_t query(int l, int r) { return query(l, r, 1, cnt, 1); }

   private:
    value_t lazy[MAXN << 2];
    value_t sum[MAXN << 2];
    int cnt;

    value_t *num;
    int *rnk;

#define lson l, m, rt << 1
#define rson m + 1, r, rt << 1 | 1

    void push_up(int rt) { sum[rt] = sum[rt << 1] + sum[rt << 1 | 1]; }

    void push_down(int rt, int m) {
        if (lazy[rt]) {
            lazy[rt << 1] += lazy[rt];
            lazy[rt << 1 | 1] += lazy[rt];
            sum[rt << 1] += (m - (m >> 1)) * lazy[rt];
            sum[rt << 1 | 1] += (m >> 1) * lazy[rt];
            lazy[rt] = 0;
        }
    }

    void build_from_cin(int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            cin >> sum[rt];
            return;
        }
        int m = (l + r) >> 1;
        build_from_cin(lson);
        build_from_cin(rson);
        push_up(rt);
    }

    void build(int l, int r, int rt) {
        lazy[rt] = 0;
        if (l == r) {
            sum[rt] = num[rnk[rt]];
            return;
        }
        int m = (l + r) >> 1;
        build(lson);
        build(rson);
        push_up(rt);
    }

    void update(int L, int R, value_t c, int l, int r, int rt) {
        if (L <= l && R >= r) {
            lazy[rt] += c;
            sum[rt] += (value_t)c * (r - l + 1);
            return;
        }
        push_down(rt, r - l + 1);
        int m = (l + r) >> 1;
        if (L <= m) update(L, R, c, lson);
        if (R > m) update(L, R, c, rson);
        push_up(rt);
    }

    value_t query(int L, int R, int l, int r, int rt) {
        if (L <= l && R >= r) return sum[rt];
        push_down(rt, r - l + 1);
        int m = (l + r) >> 1;
        value_t ret = 0;
        if (L <= m) ret += query(L, R, lson);
        if (R > m) ret += query(L, R, rson);
        return ret;
    }

#undef lson
#undef rson
};
```

### ST 表

```cpp
template <typename T, typename TMerge>
class spharse_table {
   protected:
    T st[MAXN][22];
    // st[i][j]:从i开始,长度为1<<j的区间的最大值
   public:
    spharse_table(int n, const T* a) {
        memset(st, 0, sizeof st);
        for (int i = 1; i <= n; i++) {
            st[i][0] = a[i];
        }
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 1; i + (1 << j) - 1 <= n; i++) {
                st[i][j] =
                    TMerge()(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
                //递推:每一节的最大值等于前半截和后半截的最大值
            }
        }
    }

    T query(int l, int r) {
        int k = 0;
        while ((1 << (k + 1)) <= r - l + 1) {
            k++;
        }
        return TMerge()(st[l][k], st[r - (1 << k) + 1][k]);
        //前后等长两节区间,区间可重复
    }
};
```

### Splay

```cpp
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
```

### 树链剖分

```cpp
class tls : public lfs {
   public:
    tls(int n, int root = 1)
        : lfs(n, (n - 1) * 2),
          root(root),
          tree(1),
          size(n + 1, 0),
          top(n + 1, 0),
          son(n + 1, -1),
          dep(n + 1, 0),
          tid(n + 1, 0),
          rnk(n + 1, 0),
          fa(n + 1, 0) {}

    template <typename TBaseData>
    void init(TBaseData* num) {
        dfs1(root, 0, 0);
        dfs2(root, root);
        vector<TBaseData> data(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            data[i] = num[rnk[i]];
        }
        tree = segtree(n, data.data());
    }

    template <typename TUpdate>
    void update(int x, int y, const TUpdate& data) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            tree.update(tid[top[x]], tid[x], data);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        tree.update(tid[x], tid[y], data);
    }

    template <typename TQuery>
    TQuery query(int x) {
        return tree.query<TQuery>(tid[x], tid[x]);
    }

    template <typename TQuery>
    TQuery query(int x, int y) {
        TQuery x_to_lca;
        TQuery lca_to_y;
        while (top[x] != top[y]) {
            if (dep[top[x]] >= dep[top[y]]) {
                TQuery seg = tree.query<TQuery>(tid[top[x]], tid[x]);
                seg.flip();
                x_to_lca.merge_right(seg);
                x = fa[top[x]];
            } else {
                TQuery seg = tree.query<TQuery>(tid[top[y]], tid[y]);
                lca_to_y.merge_left(seg);
                y = fa[top[y]];
            }
        }
        if (dep[x] >= dep[y]) {
            TQuery seg = tree.query<TQuery>(tid[y], tid[x]);
            seg.flip();
            x_to_lca.merge_right(seg);
            x_to_lca.merge_right(lca_to_y);
            return x_to_lca;
        } else {
            TQuery seg = tree.query<TQuery>(tid[x], tid[y]);
            x_to_lca.merge_right(seg);
            x_to_lca.merge_right(lca_to_y);
            return x_to_lca;
        }
    }

    template <typename TUpdate>
    void update_subtree(int u, const TUpdate& data) {
        tree.update(tid[u], tid[u] + size[u] - 1, data);
    }

    template <typename TQuery>
    TQuery query_subtree(int u) {
        return tree.query<TQuery>(tid[u], tid[u] + size[u] - 1);
    }

   private:
    int root;
    segtree tree;
    int tim = 0;
    vector<int> size, top, son, dep, tid, rnk, fa;

    void dfs1(int u, int fa, int d) {
        dep[u] = d;
        this->fa[u] = fa;
        size[u] = 1;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v != fa) {
                dfs1(v, u, d + 1);
                size[u] += size[v];
                if (son[u] == -1 || size[v] > size[son[u]]) son[u] = v;
            }
        }
    }
    void dfs2(int u, int tp) {
        top[u] = tp;
        tid[u] = ++tim;
        rnk[tid[u]] = u;
        if (son[u] == -1) return;
        dfs2(son[u], tp);
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v != son[u] && v != fa[u]) dfs2(v, v);
        }
    }
};
```

### Treap

```cpp
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
```

## 图论

### 边双连通分量与染色

```cpp
class bcc : public lfs {
   protected:
    int dfn[MAXN];
    int low[MAXN];
    int tim;
    int color[MAXN];  //  处理bcc数组时防重复用
    stack<pair<int, int>> s;

    void dfs(int u, int fa) {
        dfn[u] = low[u] = ++tim;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (v == fa) continue;
            if (dfn[v] == 0) {
                s.push(make_pair(u, v));
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    vector<int> cur;
                    bcccnt++;
                    pair<int, int> now;
                    do {
                        now = s.top();
                        s.pop();
                        if (color[now.first] != bcccnt) {
                            cur.push_back(now.first);
                            color[now.first] = bcccnt;
                            belong[now.first].push_back(bcccnt);
                        }
                        if (color[now.second] != bcccnt) {
                            cur.push_back(now.second);
                            color[now.second] = bcccnt;
                            belong[now.second].push_back(bcccnt);
                        }
                    } while (!(now.first == u && now.second == v));
                    bccs.push_back(cur);
                }
            } else if (dfn[v] < dfn[u]) {
                s.push(make_pair(u, v));
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

   public:
    vector<int> belong[MAXN];
    int bcccnt;
    vector<vector<int>> bccs;

    bcc(int n) : lfs(n) {
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        memset(color, 0, sizeof color);
        tim = bcccnt = 0;
    }

    void pre() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == 0) dfs(i, -1);
        }
    }
};
```

### 点双连通分量和割点

```cpp
class cut_vertex : public lfs {
   protected:
    int dfn[MAXN], low[MAXN];
    int tim;
    int scc_count = 0;
    stack<int> s;
    void tarjan(int u, int fa) {
        s.push(u);
        int cc = 0;
        dfn[u] = low[u] = tim++;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dfn[v] == -1) {
                tarjan(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] >= dfn[u]) {
                    cc++;
                    if (fa != -1 || cc > 1) {
                        is_cut_vertex[u] = true;
                    }
                    scc_count++;
                    while (!s.empty()) {
                        int cur = s.top();
                        s.pop();
                        belong_to[cur].push_back(scc_count);
                        if (cur == v) break;
                    }
                    belong_to[u].push_back(scc_count);
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
    }

   public:
    vector<int> belong_to[MAXN];
    bool is_cut_vertex[MAXN];
    cut_vertex(int n) : lfs(n) {}

    void pre() {
        memset(dfn, -1, sizeof dfn);
        memset(is_cut_vertex, false, sizeof is_cut_vertex);
        tim = 1;

        for (int i = 1; i <= n; i++) {
            if (dfn[i] == -1) {
                tarjan(i, -1);
            }
        }
    }

    void shrink_point(lfs* graph, vector<int>& mapping) {
        mapping = vector<int>(n + 1, 0);
        int cut_vertex_id = scc_count;
        for (int i = 1; i <= n; i++) {
            if (is_cut_vertex[i]) {
                cut_vertex_id++;
                mapping[i] = cut_vertex_id;
                for (auto& scc : belong_to[i]) {
                    graph->addde(cut_vertex_id, scc, 1);
                }
            } else {
                mapping[i] = belong_to[i][0];
            }
        }
    }
};
```

### Dinic 网络流

```cpp
class dinic : public network_flow {
   private:
    int dis[MAXN];  //起点到i的距离
    int cur[MAXN];  //当前弧
    bool vis[MAXN];

    int s, t;

    bool bfs() {
        memset(vis, false, sizeof vis);
        queue<int> q;
        q.push(s);
        dis[s] = 0;
        vis[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i : g[u]) {
                edge& now = e[i];
                if (!vis[now.to] && now.cap > now.flow) {
                    vis[now.to] = true;
                    dis[now.to] = dis[u] + 1;
                    q.push(now.to);
                }
            }
        }
        return vis[t];
    }

    int dfs(int u, int a) {
        if (u == t || a == 0) {
            return a;
        }
        int flow = 0;
        for (; cur[u] < g[u].size(); cur[u]++) {
            edge& now = e[g[u][cur[u]]];
            if (dis[u] + 1 == dis[now.to]) {
                int f = dfs(now.to, min(a, now.cap - now.flow));
                if (f > 0) {
                    now.flow += f;
                    e[g[u][cur[u]] ^ 1].flow -= f;
                    flow += f;
                    a -= f;
                    if (a == 0) {
                        break;
                    }
                }
            }
        }
        return flow;
    }

   public:
    dinic(int n) : network_flow(n) {
        memset(dis, 0, sizeof dis);
        memset(cur, 0, sizeof cur);
        memset(vis, false, sizeof vis);
    }

    int maxflow(int s, int t) {
        this->s = s;
        this->t = t;
        int flow = 0;
        while (bfs()) {
            memset(cur, 0, sizeof cur);
            flow += dfs(s, INF);
        }
        return flow;
    }
};
```

### EK 网络流

```cpp
class edmonds_karp : public network_flow {
   private:
    int a[MAXN];   //起点到i的可改进量
    int fa[MAXN];  //最短路树上的入边
   public:
    edmonds_karp(int n) : network_flow(n) {
        memset(a, 0, sizeof a);
        memset(fa, 0, sizeof fa);
    }

    int maxflow(int s, int t) {
        int flow = 0;
        while (true) {
            memset(a, 0, sizeof a);
            queue<int> q;
            q.push(s);
            a[s] = INF;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int i : g[u]) {
                    edge& now = e[i];
                    if (a[now.to] == 0 && now.cap > now.flow) {
                        fa[now.to] = i;
                        a[now.to] = min(a[u], now.cap - now.flow);
                        q.push(now.to);
                    }
                }
                if (a[t] > 0) {  //剪枝：已经找到了一条
                    break;
                }
            }
            if (a[t] == 0) {  //没有增广路了
                break;
            }
            for (int u = t; u != s; u = e[fa[u]].from) {
                e[fa[u]].flow += a[t];
                e[fa[u] ^ 1].flow -= a[t];
            }
            flow += a[t];
        }
        return flow;
    }
};
```

### Kruscal 最小生成树

```cpp
class kruskal {
    struct edge {
        int to, from;
        int dis;
        edge(int to = 0, int from = 0, int dis = 0) : to(to), from(from), dis(dis) {}
    } e[MAXM * 2];

    int ecnt;
    int n;
    int fa[MAXN];
    int find(int u) { return (fa[u] == u) ? u : fa[u] = find(fa[u]); }

    static bool cmp(const edge& a, const edge& b) { return a.dis < b.dis; }

   public:
    kruskal(int n) {
        this->n = n;
        ecnt = 0;
    }

    void adde(int to, int from, int dis) { e[++ecnt] = edge(to, from, dis); }

    int solve() {
        sort(e + 1, e + ecnt + 1, cmp);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
        int cnt = 0;
        int pos = 0;
        int ans = 0;
        while (cnt < n && pos <= ecnt) {
            edge now = e[++pos];
            if (find(now.from) != find(now.to)) {
                ans += now.dis;
                cnt++;
                fa[find(now.from)] = find(fa[now.to]);
            }
        }
        return ans;
    }

    void create_tree(lfs* tree) {
        sort(e + 1, e + ecnt + 1, cmp);
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
        int cnt = 0;
        int pos = 0;
        int ans = 0;
        while (cnt < n && pos <= ecnt) {
            edge now = e[++pos];
            if (find(now.from) != find(now.to)) {
                tree->addde(now.from, now.to, now.dis);
                cnt++;
                fa[find(now.from)] = find(fa[now.to]);
            }
        }
    }
};
```

### 倍增 LCA

```cpp
class lca : public lfs {
   public:
    int dep[MAXN];
    lca(int n) : lfs(n) { memset(dep, -1, sizeof dep); }
    void pre(int rt = 1) { dfs(rt, 1, 0); }
    int querylca(int a, int b) {
        if (dep[a] > dep[b]) swap(a, b);
        int h = dep[b] - dep[a];
        for (int i = 20; i >= 0; i--) {
            if (h & (1 << i)) {
                b = f[b][i];
            }
        }
        if (a == b) return a;
        for (int i = 20; i >= 0; i--) {
            if (f[a][i] == f[b][i]) continue;
            a = f[a][i];
            b = f[b][i];
        }
        return f[a][0];
    }

   protected:
    int f[MAXN][22];

   private:
    void dfs(int u, int d, int fa) {
        dep[u] = d;
        f[u][0] = fa;
        for (int i = 1; i < 21; i++) {
            f[u][i] = f[f[u][i - 1]][i - 1];
        }
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dep[v] == -1) {
                dfs(v, d + 1, u);
            }
        }
    }
};
```

### 链式前向星

```cpp
class lfs {
   public:
    lfs(int n) : n(n), head(n + 1, -1) {}
    lfs(int n, int m) : lfs(n) { e.reserve(m); }
    int n;

    vector<int> head;
    struct edge {
        int to;
        int next;
        int w;
    };
    vector<edge> e;

    void adde(int u, int v, int w = 1) {
        e.push_back(edge{.to = v, .next = head[u], .w = w});
        head[u] = e.size() - 1;
    }

    void addde(int a, int b, int w = 1) {
        adde(a, b, w);
        adde(b, a, w);
    }
};
```

### 最小费用最大流

```cpp
class mcmf {
   public:
    mcmf(int n) {
        this->n = n;
        memset(head, -1, sizeof head);
        memset(e, 0, sizeof e);
    }
    void adde(int from, int to, int flow, int cost) {
        _adde(from, to, flow, cost);
        _adde(to, from, 0, -cost);
    }

    int max_flow = 0;
    int min_cost = 0;

    void solve(int s, int t) {
        // 每次只增广最短路
        while (spfa(s, t)) {
            max_flow += flow[t];
            min_cost += flow[t] * cost[t];
            int u = t;
            while (u != s) {
                e[in_edge[u]].flow -= flow[t];
                e[in_edge[u] ^ 1].flow += flow[t];
                u = e[in_edge[u]].from;
            }
        }
    }

   protected:
    struct edge {
        int from, to, next;
        int flow, cost;
    } e[MAXN * 2];
    int head[MAXN];
    int ecnt = 0;
    int n;

    void _adde(int from, int to, int flow, int cost) {
        e[ecnt].from = from;
        e[ecnt].to = to;
        e[ecnt].flow = flow;
        e[ecnt].cost = cost;
        e[ecnt].next = head[from];
        head[from] = ecnt++;
    }

    int cost[MAXN];     // 最小花费
    int in_edge[MAXN];  // 进入节点的边
    int flow[MAXN];     // 源点至此流量

    bool ins[MAXN];

    bool spfa(int s, int t) {
        memset(cost, INF, sizeof cost);
        memset(flow, INF, sizeof flow);
        memset(ins, false, sizeof ins);
        memset(in_edge, -1, sizeof in_edge);

        queue<int> q;
        q.push(s);
        ins[s] = true;
        cost[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            ins[u] = false;
            for (int i = head[u]; i != -1; i = e[i].next) {
                int v = e[i].to;
                if (e[i].flow > 0 && cost[v] > cost[u] + e[i].cost) {
                    cost[v] = cost[u] + e[i].cost;
                    in_edge[v] = i;
                    flow[v] = min(flow[u], e[i].flow);
                    if (!ins[v]) {
                        q.push(v);
                        ins[v] = true;
                    }
                }
            }
        }
        return in_edge[t] != -1;
    }
};
```

### 网络流基类

```cpp
class network_flow {
   protected:
    struct edge {
        int from, to;
        int cap, flow;
        edge(int u, int v, int c, int f = 0)
            : from(u), to(v), cap(c), flow(f){};
    };
    int n, m;
    vector<edge> e;
    vector<int> g[MAXN];

   public:
    network_flow() {
        n = 0;
        m = 0;
    }

    network_flow(int n) {
        this->n = n;
        m = 0;
    }

    void adde(int from, int to, int cap) {
        e.push_back(edge(from, to, cap));
        g[from].push_back(e.size() - 1);
        e.push_back(edge(to, from, 0));
        g[to].push_back(e.size() - 1);
        m += 2;
    }

    void clear_flow() {
        for (edge& i : e) {
            i.flow = 0;
        }
    }
};
```

### 有向图强连通分量

```cpp
class scc : public lfs {
   public:
    int scccnt;
    int belong[MAXN];

    scc(int n) : lfs(n) {
        memset(dfn, -1, sizeof dfn);
        memset(low, -1, sizeof low);
        memset(ins, false, sizeof ins);
        memset(belong, 0, sizeof belong);
        tim = 1;
        scccnt = 0;
    }

    void solve() {
        for (int i = 1; i <= n; i++) {
            if (dfn[i] == -1) {
                tarjan(i);
            }
        }
    }

    //缩点，先调用solve
    void create_new(lfs* map) {
        for (int i = 1; i <= n; i++) {
            for (int j = head[i]; j != -1; j = e[j].next) {
                int u = belong[i];
                int v = belong[e[j].to];
                if (u != v) {
                    map->adde(u, v, e[j].w);
                }
            }
        }
    }

   protected:
    stack<int> s;
    bool ins[MAXN];
    int mina[MAXN];
    int low[MAXN], dfn[MAXN];
    int tim;
    void tarjan(int u) {
        dfn[u] = low[u] = tim++;
        s.push(u);
        ins[u] = true;
        for (int i = head[u]; i != -1; i = e[i].next) {
            int v = e[i].to;
            if (dfn[v] == -1) {
                tarjan(v);
                low[u] = min(low[u], low[v]);
            } else {
                if (ins[v]) {
                    low[u] = min(low[u], dfn[v]);
                }
            }
        }
        if (dfn[u] == low[u]) {
            scccnt++;
            int v = 0;
            while (v != u) {
                v = s.top();
                s.pop();
                ins[v] = false;
                belong[v] = scccnt;
            }
        }
    }
};
```

### 最短路

#### Dijkstra

```cpp
class dijkstra : public lfs {
   public:
    dijkstra(int n) : lfs(n) { memset(dis, INF, sizeof dis); }
    int dis[MAXN];
    void solve(int s) {
        priority_queue<pair<int, int>, vector<pair<int, int>>,
                       greater<pair<int, int>>>
            q;
        dis[s] = 0;
        q.push({0, s});
        while (!q.empty()) {
            auto x = q.top();
            q.pop();
            int u = x.second;
            if (dis[u] < x.first) continue;
            for (int i = head[u]; i != -1; i = e[i].next) {
                int v = e[i].to;
                if (dis[u] + e[i].w < dis[v]) {
                    dis[v] = dis[u] + e[i].w;
                    q.push({dis[v], v});
                }
            }
        }
    }
};
```

#### SPFA

```cpp
class spfa : public lfs {
   public:
    spfa(int n) : lfs(n) { memset(dis, INF, sizeof dis); }
    int dis[MAXN];
    void solve(int s) {
        memset(ins, false, sizeof ins);
        memset(dis, INF, sizeof dis);
        queue<int> q;
        q.push(s);
        ins[s] = true;
        dis[s] = 0;
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            ins[now] = false;
            for (int i = head[now]; i != -1; i = e[i].next) {
                int v = e[i].to;
                int w = e[i].w;
                if (dis[now] + w < dis[v]) {
                    dis[v] = dis[now] + w;
                    if (!ins[v]) {
                        q.push(v);
                        ins[v] = true;
                    }
                }
            }
        }
    }

   private:
    bool ins[MAXN];
};
```

### 拓扑排序

```cpp
class toposort : public lfs {
 public:
 	toposort(int n) : lfs(n) {}
    int in[MAXN];
    vector<int> ans;
    bool operator()() {
    	memset(in, 0, sizeof in);
    	for (int i = 1; i <= n; i++) {
    		for (int j = head[i]; j != -1; j = e[j].next) {
    			in[e[j].to]++;
    		}
    	}
    	queue<int> q;
    	for (int i = 1; i <= n; i++) {
    		if (in[i] == 0) {
    			q.push(i);
    		}
    	}
    	while (!q.empty()) {
    		int u = q.front();
    		q.pop();
    		ans.push_back(u);
    		for (int i = head[u]; i != -1; i = e[i].next) {
    			int v = e[i].to;
    			in[v]--;
    			if (in[v] == 0) {
    				q.push(v);
    			}
    		}
    	}
    	return ans.size() == n;
    }
};
```

### 矩阵树定理

定义图的 Laplacian 矩阵 $L\in Z^{n\times n}$,

$$
L_{ij}=
\begin{cases}
\textrm{deg}(i),  & i=j \\
-m_{ij}, & i\neq j
\end{cases}
$$

其中 $\textrm{deg}(i)$ 是节点 i 的度数, $m_{ij}$ 是节点 u 和 v 的边数.

![image.png](https://s2.loli.net/2022/04/22/chFxqy8ZplIvDgr.png)

例如, 上图的 Laplacian 矩阵是

$$
L=
\begin{pmatrix}
3  & 0  & -1 & 0  & -1 & -1 \\
0  & 2  & 0  & 0  & -1 & -1 \\
-1 & 0  & 3  & -1 & -1 & 0  \\
0  & 0  & -1 & 1  & 0  & 0  \\
-1 & -1 & -1 & 0  & 4  & -1 \\
-1 & -1 & 0  & 0  & -1 & 3  \\
\end{pmatrix}
$$

则图的生成树个数为 $\det(L_0)$, 其中 $L_0$ 是 $L$ 去掉 $i$ 行 $i$ 列, $i$ 任取 $1 \leq i \leq n$.

### 最小树形图

最小树形图是有向图上，从给定的根节点出发到达所有节点的一颗生成树。

```cpp
int g[MAXN][MAXN];
bool remove_tag[MAXN];  // 缩环时删点标记
int fa[MAXN];           // 每轮，每个点的最小前驱节点
bool vis[MAXN];         // 找环的标记

int directional_spawning_tree(int root, int n) {
    int ans = 0;
    memset(remove_tag, false, sizeof remove_tag);
    while (true) {
        // 找每个点的最小前驱边
        for (int u = 1; u <= n; u++) {
            if (remove_tag[u] || u == root) continue;
            int min_val = INF;
            int min_node = 0;
            for (int i = 1; i <= n; i++) {
                if (remove_tag[i]) continue;
                if (g[i][u] < min_val) {
                    min_val = g[i][u];
                    min_node = i;
                }
            }
            // 如果没有前驱，则无解
            if (min_node == 0) return -1;
            fa[u] = min_node;
        }

        // 判断是否有环
        bool has_loop = false;
        int loop_head = 0;
        for (int i = 1; i <= n; i++) {
            if (remove_tag[i] || i == root) continue;
            memset(vis, false, sizeof vis);
            vis[root] = true;
            int u = i;
            while (!vis[u]) {
                vis[u] = true;
                u = fa[u];
            }
            if (u != root) {
                has_loop = true;
                loop_head = u;
                break;
            }
        }

        if (!has_loop) {
            // 没有环，则算法结束
            for (int i = 1; i <= n; i++) {
                if (remove_tag[i] || i == root) continue;
                ans += g[fa[i]][i];
            }
            return ans;
        }

        // cout << loop_head << endl;

        // 进行缩环操作
        // 统计环上的权值
        int u = loop_head;
        do {
            ans += g[fa[u]][u];
            u = fa[u];
        } while (u != loop_head);

        // 然后处理环上所有入边的权值，入边权值减去环上边的权值
        // 这样缩环后再判断找最小前驱边时，选到入环的边就决定了断环的位置
        u = loop_head;
        do {
            for (int i = 1; i <= n; i++) {
                if (remove_tag[i]) continue;
                if (i != fa[u] && g[i][u] != INF) {
                    g[i][u] -= g[fa[u]][u];
                }
            }
            u = fa[u];
        } while (u != loop_head);

        // 缩点，转移权值
        for (int i = 1; i <= n; i++) {
            if (remove_tag[i] || i == loop_head) continue;
            int u = fa[loop_head];
            do {
                g[loop_head][i] = min(g[loop_head][i], g[u][i]);
                g[i][loop_head] = min(g[i][loop_head], g[i][u]);
                u = fa[u];
            } while (u != loop_head);
        }

        // 把环上其他的点都标记删除
        u = fa[loop_head];
        do {
            remove_tag[u] = true;
            u = fa[u];
        } while (u != loop_head);
    }
}
```

### 全局最小割

任意两点间最小割

```cpp
int g[MAXN][MAXN];
int w[MAXN]; // w[i] 已选定集合中所有点到 i 的直接连边边权总和
int fa[MAXN]; // 处理合并操作后，删掉其中一个点
bool ins[MAXN];

int main() {
    int n, m;
    while (cin >> n >> m) {
        memset(g, 0, sizeof g);
        for (int i = 1; i <= m; i++) {
            int u = read();
            int v = read();
            int c = read();
            g[u][v] += c;
            g[v][u] += c;
        }
        for (int i = 0; i < n; i++) {
            fa[i] = i;
        }
        int ans = INF;
        int remain = n;
        while (remain > 1) {
            memset(w, 0, sizeof w);
            memset(ins, false, sizeof ins);
            ins[0] = true;
            int u = 0;
            int v = 0;
            for (int i = 1; i < remain; i++) {
                u = v;
                v = -1;
                int cut_v = -1;
                for (int j = 1; j < remain; j++) {
                    if (!ins[j]) {
                        w[j] += g[fa[j]][fa[u]];
                        if (w[j] > cut_v) {
                            cut_v = w[j];
                            v = j;
                        }
                    }
                }
                ins[v] = true;
            }
            ans = min(ans, w[v]);

            // 类似并查集的合并操作
            for (int i = 1; i < remain; i++) {
                if (i == v) continue;
                g[fa[i]][fa[0]] += g[fa[i]][fa[v]];
                g[fa[0]][fa[i]] += g[fa[v]][fa[i]];
            }
            remain--;
            fa[v] = fa[remain]; // 相当于是把 v 删掉了
        }

        write(ans);
        putchar('\n');
    }
}
```

## 数学

### 组合数

#### 组合数递推

```cpp
const int MAXC = 50;

int C[MAXC][MAXC];

void init_cnum() {
    for (int i = 0; i < MAXC; i++) {
        C[i][0] = 1;
        for (int j = 1; j < MAXC; j++) {
            C[i][j] = C[i - 1][j] + C[i][j - 1];
        }
    }
    return;
}
```

#### 卢卡斯定理

模意义下的大组合数

```cpp
template<typename T, size_t N>
struct lucas_t {
   private:
	T pow(T a, T b, T mod) {
    	T res = 1;
    	while (b) {
        	if (b & 1) res = res * a % mod;
        	a = a * a % mod;
        	b /= 2;
    	}
    	return res;
	}
   	
   public:
   	T c(T n, T m, T mod) {
   		if (n < m) {
   			return 0;
   		} else if (m > n - m) {
   			m = n - m;
   		}
   		T a = 1, b = 1;
   		for (int i = 0; i < m; i++) {
   			a = a * (n - i) % mod;
   			b = b * (i + 1) % mod;
   		}
   		return a * pow(b, mod - 2, mod) % mod;
   	}
   	
	T operator()(T n, T m, T mod) {
		if (m == 0) {
			return 1;
		} else if (m > n) {
			return 0;
		}	
		return (*this)(n / mod, m / mod, mod) * c(n % mod, m % mod, mod) % mod;
	} 	
};
```

### Exgcd

```cpp
template <typename T>
T exgcd(T a, T b, T &x, T &y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }
    T g = exgcd(b, a % b, x, y);
    T tmp = x;
    x = y;
    y = tmp - a / b * y;
    return g;
}

template <typename T>
T inv1(T a, T mod) {
    T x, y;
    T d = exgcd(a, mod, x, y);
    if (d == 1) return (x % mod + mod) % mod;
    return -1;
}
```

### 高斯消元相关

#### 解线性方程组

```cpp
const double EPS = 1e-8;

int dcmp(double x, double y) {
	double c = x - y;
	if (c > EPS) return 1;
	if (c < -EPS) return -1;
	return 0;
}

template <typename T>
bool gauss(const vector<vector<T>>& in, vector<T>& out) {
	vector<vector<T>> a(in);
	size_t n = in.size();
	// i 枚举列 
	for (size_t i = 0; i < n; i++) {
		// 选定当前列的最大系数项 
		size_t mxid = i;
		for (size_t j = i + 1; j < n; j++) {
			if (dcmp(fabs(a[j][i]), fabs(a[mxid][i])) == 1) {
				mxid = j;
			}
		}
		// 提到当前排 
		swap(a[i], a[mxid]);
		if (a[i][i] == 0) return false;
		for (size_t j = 0; j < n; j++) {
			if (j == i) continue;
			T mi = a[j][i] / a[i][i];
			for (size_t k = i + 1; k <= n; k++) {
				a[j][k] -= a[i][k] * mi;
			}
		} 
	}
	
	out = vector<T>(n, 0);
	for (size_t i = 0; i < n; i++) {
		out[i] = a[i][n] / a[i][i];
	}
	return true;
}
```

#### 行列式

```cpp
template <typename T>
T det(vector<vector<T>> a, T mod, int n = -1) {
    T symbol = 1;
    if (n == -1) n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            while (a[i][i] != 0) {
                T d = a[j][i] / a[i][i] % mod;
                for (int k = i; k < n; k++) {
                    a[j][k] -= a[i][k] * d % mod;
                    a[j][k] = (a[j][k] % mod + mod) % mod;
                }
                swap(a[i], a[j]);
                symbol = -symbol;
            }
            swap(a[i], a[j]);
            symbol = -symbol;
        }
    }

    T ans = symbol;
    for (int i = 0; i < n; i++) {
        ans *= a[i][i];
        ans %= mod;
    }
    return (ans + mod) % mod;
}
```

### 多项式

```cpp
namespace polynomial
{
    const double PI = acos(-1);

    template <typename T>
    struct point
    {
        T x, y;
        point() : x(0), y(0) {}
        point(T X, T Y) : x(X), y(Y) {}
    };
    template <typename T>
    point<T> operator+(const point<T> &a, const point<T> &b)
    {
        return point<T>(a.x + b.x, a.y + b.y);
    }
    template <typename T>
    point<T> operator-(const point<T> &a, const point<T> &b)
    {
        return point<T>(a.x - b.x, a.y - b.y);
    }
    template <typename T>
    point<T> cross(const point<T> &a, const point<T> &b)
    {
        return point<T>(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x);
    }

    typedef point<double> complex;
    inline complex operator*(const complex &a, const complex &b) { return cross(a, b); }

    void fft(complex *f, int limit, int reverse, const int *r)
    {
        for (int i = 0; i < limit; i++)
        {
            if (i < r[i])
                swap(f[i], f[r[i]]);
        }
        for (int j = 1; j < limit; j <<= 1)
        {
            complex omega(cos(PI / j), reverse * sin(PI / j));
            for (int k = 0; k < limit; k += (j << 1))
            {
                complex cur(1, 0);
                for (int l = 0; l < j; l++, cur = cur * omega)
                {
                    complex nx = f[k + l], ny = cur * f[k + j + l];
                    f[k + l] = nx + ny;
                    f[k + j + l] = nx - ny;
                }
            }
        }
    }

    template <typename T = int>
    T *multiplicate_coefficient(complex *a, int n, complex *b, int m)
    {
        int lim = 1, l = 0;
        while (lim <= n + m)
        {
            lim <<= 1;
            l++;
        }
        int *r = new int[lim + 10];
        memset(r, 0, (lim + 10) * sizeof(int));
        for (int i = 0; i < lim; i++)
        {
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
        }
        fft(a, lim, 1, r);
        fft(b, lim, 1, r);
        for (int i = 0; i <= lim; i++)
        {
            a[i] = a[i] * b[i];
        }
        fft(a, lim, -1, r);
        delete[] r;
        T *ans = new T[n + m + 1];
        for (int i = 0; i <= n + m; i++)
        {
            ans[i] = (T)(a[i].x / lim + 0.5);
        }
        return ans;
    }

    const int64 P = 998244353;
    const int64 G = 3;

    template <typename T>
    T pow_mod(T a, T b, T MOD)
    {
        T res = 1;
        while (b)
        {
            if (b & 1)
                res = res * a % MOD;
            a = a * a % MOD;
            b /= 2;
        }
        return res;
    }

    int64 inv = pow_mod(G, P - 2, P);

    void ntt(int64 *f, int limit, bool reverse, const int *r)
    {
        for (int i = 0; i < limit; i++)
        {
            if (i < r[i])
                swap(f[i], f[r[i]]);
        }
        for (int j = 1; j < limit; j <<= 1)
        {
            int64 omega =
                reverse ? pow_mod(G, (P - 1) / (j << 1), P) : pow_mod(inv, (P - 1) / (j << 1), P);
            for (int k = 0; k < limit; k += (j << 1))
            {
                int64 cur = 1;
                for (int l = 0; l < j; l++)
                {
                    int64 nx = f[k + l], ny = (cur * f[k + j + l]) % P;
                    f[k + l] = (nx + ny) % P;
                    f[k + j + l] = (nx - ny + P) % P;
                    cur = (cur * omega) % P;
                }
            }
        }
    }

    // template <typename T = int64>
    void multiplicate_coefficient(int64 *a, int n, int64 *b, int m)
    {
        int lim = 1, l = 0;
        while (lim <= n + m)
        {
            lim <<= 1;
            l++;
        }

        int *r = new int[lim + 10];
        memset(r, 0, (lim + 10) * sizeof(int));
        for (int i = 0; i < lim; i++)
        {
            r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
        }
        ntt(a, lim, false, r);
        ntt(b, lim, false, r);
        for (int i = 0; i <= lim; i++)
        {
            a[i] = a[i] * b[i];
        }
        ntt(a, lim, true, r);
        int64 inv = pow_mod<int64>(lim, P - 2, P);
        for (int i = 0; i <= lim; i++)
        {
            a[i] = a[i] * inv % P;
        }
        delete[] r;
    }
};
```

### 质数

#### 线性筛

```cpp
const int MAXA = 5e6 + 10;
const int AMXA = 5e6;

int prime[MAXA];
bool isntp[MAXA];
int prime_cnt;

void make_prime() {
    prime_cnt = 0;
    memset(isntp, false, sizeof(isntp));
    for (int i = 2; i <= AMXA; ++i) {
        if (!isntp[i]) {
            prime[prime_cnt++] = i;
        }
        for (int j = 0; j < prime_cnt; ++j) {
            if (i * prime[j] > AMXA) {
                break;
            }
            isntp[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                break;
            }
        }
    }
}
```

#### 欧拉 Phi 函数

```cpp
int phi[MAXA];

void init_phi() {
    phi[1] = 1;
    for (int i = 2; i <= AMXA; i++) {
        if (!isntp[i]) {
            prime[++prime_cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= prime_cnt && i * prime[j] <= AMXA; j++) {
            isntp[i * prime[j]] = true;
            if (i % prime[j] == 0) {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            } else {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
            }
        }
    }
}
```

#### MR 素数测试

```cpp
bool mr(int64 x, int64 b) {
    int64 d = x - 1;
    int64 p = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        p++;
    }
    int64 cur = pow_mod(b, d, x);
    if (cur == 1 || cur == x - 1) return true;
    for (int i = 1; i <= p; i++) {
        cur = cur * cur % x;
        if (cur == x - 1) return true;
    }
    return false;
}
bool is_prime(int64 x) {
    if (x == 46856248255981ll || x < 2) return false;
    if (x == 2 || x == 3 || x == 7 || x == 61 || x == 24251) return true;
    return mr(x, 2) && mr(x, 3) && mr(x, 7) && mr(x, 61) && mr(x, 24251);
}
```

## 其他

### AC 自动机

```cpp
const int MAXS = 2e6 + 10;
const int MAXT = 2e5 + 10;

template <typename T = char, size_t sigma_size = 26, T insert_offset = 'a'>
class ac {
   public:
    ac() {
        trie[0] = null = new trie_node();
        trie[1] = root = new trie_node(null);
        memset(endpoint, -1, sizeof endpoint);
        memset(ans, 0, sizeof ans);
        for (int i = 0; i < sigma_size; i++) {
            null->ch[i] = root;
        }
        null->fail = null;
    }

    ~ac() {
        for (int i = 0; i <= node_cnt; i++) delete trie[i];
    }

    void insert(const T* t, int id) {
        trie_node* u = root;
        while (*t != '\0') {
            int v = *t - insert_offset;
            if (u->ch[v] == null) {
                u->ch[v] = trie[++node_cnt] = new trie_node(null);
            }
            u = u->ch[v];
            t++;
        }
        if (u->id == 0) u->id = id;
        endpoint[id] = u->id;
    }

    void get_fail() {
        queue<trie_node*> q;
        q.push(root);
        while (!q.empty()) {
            trie_node* u = q.front();
            q.pop();
            for (int i = 0; i < sigma_size; i++) {
                if (u->ch[i] == null) {
                    u->ch[i] = u->fail->ch[i];
                } else {
                    u->ch[i]->fail = u->fail->ch[i];
                    u->ch[i]->fail->in++;
                    q.push(u->ch[i]);
                }
            }
        }
    }

    void query(const T* s) {
        trie_node* u = root;
        while (*s != '\0') {
            u = u->ch[*s - insert_offset];
            u->hit++;
            s++;
        }

        queue<trie_node*> q;
        for (int i = 1; i <= node_cnt; i++) {
            if (trie[i]->in == 0) q.push(trie[i]);
        }
        while (!q.empty()) {
            trie_node* u = q.front();
            q.pop();
            ans[u->id] = u->hit;
            u->fail->hit += u->hit;
            u->fail->in--;
            if (u->fail->in == 0) q.push(u->fail);
        }
    }

    int get_ans(int id) { return ans[endpoint[id]]; }

   protected:
    struct trie_node {
        trie_node* ch[sigma_size];
        trie_node* fail;
        int in;
        int id, hit;
        trie_node(trie_node* def = nullptr) {
            for (int i = 0; i < sigma_size; i++) {
                ch[i] = def;
            }
            fail = def;
            hit = id = in = 0;
        }
    };
    trie_node* trie[MAXT];
    trie_node* root;
    trie_node* null;
    int node_cnt = 1;
    int endpoint[MAXT];
    int ans[MAXT];
};
```

### IO 优化

```cpp
#define getchar()                                                              \
    (frS == frT &&                                                             \
             (frT = (frS = frBB) + fread(frBB, 1, 1 << 15, stdin), frS == frT) \
         ? EOF                                                                 \
         : *frS++)
char frBB[1 << 15], *frS = frBB, *frT = frBB;

template <typename T = int>
T read() {
    T x = 0;
    bool negative = false;
    char ch = '\0';
    while (!isdigit(ch))
    {
        negative |= (ch == '-');
        ch = getchar();
    }
    while (isdigit(ch)) {
        x *= 10;
        x += ch - '0';
        ch = getchar();
    }
    return negative ? -x : x;
}

double dbread() {
    double X = 0, Y = 1.0;
    int w = 0;
    char ch = 0;
    while (!isdigit(ch)) {
        w |= ch == '-';
        ch = getchar();
    }
    while (isdigit(ch)) X = X * 10 + (ch ^ 48), ch = getchar();
    ch = getchar();  //读入小数点
    while (isdigit(ch)) X += (Y /= 10) * (ch ^ 48), ch = getchar();
    return w ? -X : X;
}

template<typename T>
void write(T x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}
```

### KMP

```cpp
const int MAXM = 1e4 + 10;
const int MAXN = 1e6 + 10;

template <typename value_t = char>
struct kmp {
   public:
    // S:源串    T:模式串
    int operator()(const value_t *S, const int n, const value_t *T,
                   const int m) {
        getnext(T, m);
        return search(S, n, T, m);
    }

   private:
    int next[MAXM];
    void getnext(const value_t *T, const int m) {
        int j = 0, k = -1;  // j前缀，p后缀
        next[0] = -1;
        while (j < m - 1) {
            if (k == -1 || T[j] == T[k]) {
                j++;
                k++;
                if (T[j] != T[k]) {
                    next[j] = k;
                } else {
                    next[j] = next[k];
                }
            } else {
                k = next[k];
            }
        }
    }
    int search(const value_t *S, const int n, const value_t *T, const int m) {
        int i = 0, j = 0;
        while (i < n && j < m) {
            if (j == -1 || S[i] == T[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
        }
        if (j == m) {
            return i - j;
        } else {
            return -1;
        }
    }
    int count(const value_t *S, const int n, const value_t *T, const int m) {
        int i = 0, j = 0;
        int ans = 0;
        while (i < n && j < m) {
            if (j == -1 || S[i] == T[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
            if (j == m) {
                ans++;
                j = 0;
            }
        }
        return ans;
    }
};
```

#### EXKMP

```cpp
const int INF = 0x3f3f3f3f;
const int MAXN = 2e7 + 10;

namespace exkmp {
int next[MAXN];
void getnext(const string& str) {
    int len = str.length();
    next[0] = len;  // 根据定义
    // 枚举求 next[1]
    next[1] = 0;
    while (next[1] < len - 1 && str[next[1]] == str[next[1] + 1]) {
        next[1]++;
    }
    int k = 1;  // 最远位置处，相同前后缀的后缀的起始下标
    for (int i = 2; i < len; i++) {
        int p = k + next[k] - 1;  // 能最远找到的下标
        if (i + next[i - k] <= p) {
            next[i] = next[i - k];
        } else {
            next[i] = max(0, p - i + 1);
            while (i + next[i] < len && str[i + next[i]] == str[next[i]]) {
                next[i]++;
            }
            k = i;
        }
    }
}

int ext[MAXN];
void getext(const string& a, const string& b) {
    int alen = a.length();
    int blen = b.length();
    ext[0] = 0;
    while (ext[0] < alen && ext[0] < blen && a[ext[0]] == b[ext[0]]) {
        ext[0]++;
    }
    int k = 0;
    for (int i = 1; i < alen; i++) {
        int p = k + ext[k] - 1;  // 能最远找到的下标
        if (i + next[i - k] <= p) {
            ext[i] = next[i - k];
        } else {
            ext[i] = max(0, p - i + 1);
            while (i + ext[i] < alen && ext[i] < blen &&
                   a[i + ext[i]] == b[ext[i]]) {
                ext[i]++;
            }
            k = i;
        }
    }
}
}  // namespace exkmp
```

### 马拉车

```cpp
const char BLANK = -1;

template <typename T>
int manacher(T* a, size_t len) {
    T* s = new T[len * 2 + 10];
    int* p = new int[len * 2 + 10];
    memset(s, 0, (len * 2 + 10) * sizeof(T));
    memset(p, 0, (len * 2 + 10) * sizeof(int));
    
    s[0] = s[1] = BLANK;
    for (int i = 0; i < len;i++) {
        s[i * 2 + 2] = a[i];
        s[i * 2 + 3] = BLANK;
    }
    len = len * 2 + 2;
    s[len] = 0;
    
    int mxpos = 0, mxaxis = 0;
    for (int i = 1; i < len; i++) {
        if (i < mxpos) {
            p[i] = min(p[mxaxis * 2 - i], p[mxaxis] + mxaxis - i);
        } else {
            p[i] = 1;
        }
        while (s[i + p[i]] == s[i - p[i]]) {
            p[i]++;
        }
        if (p[i] + i > mxpos) {
            mxpos = p[i] + i;
            mxaxis = i;
        }
    }
    
    int ans = 1;
    for (int i = 0; i < len; i++) {
        ans = max(ans, p[i]);
    }
    
    delete[] s;
    delete[] p;
    return ans - 1;
}
```

### 归并排序

```cpp
template <typename T>
void merge_sort(T* a, int l, int r, int& ans, T* tmp) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    merge_sort(a, l, mid);
    merge_sort(a, mid + 1, r);
    int i = l, j = mid + 1;
    int k = l;
    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            tmp[k++] = a[j++];
            ans += mid - i + 1;
        }
    }
    while (i <= mid) {
        tmp[k++] = a[i++];
    }
    while (j <= r) {
        tmp[k++] = a[j++];
    }
    for (int i = l; i <= r; i++) {
        a[i] = tmp[i];
    }
}

template <typename T> 
int merge_sort(T* a, int n) {
    auto tmp = new T[n + 10];
    int ans = 0;
    merge_sort(a, 1, n, ans, tmp);
    delete[] tmp;
    return ans;
}
```

### 莫队

#### 普通莫队

```cpp
template <typename TAns>
struct segment {
    int id;
    int l, r;
    TAns ans;
};

template <typename TAns>
void offline_segments(int n, vector<segment<TAns>>& segments,
                      function<void(int, TAns&)> add,
                      function<void(int, TAns&)> del) {
    int block_size = ceil(sqrt(n));
    sort(segments.begin(), segments.end(),
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
    TAns ans = 0;
    add(1, ans);
    for (auto& seg : segments) {
        while (l > seg.l) add(--l, ans);
        while (r < seg.r) add(++r, ans);
        while (l < seg.l) del(l++, ans);
        while (r > seg.r) del(r--, ans);
        seg.ans = ans;
    }
}
```

#### 不删除莫队

```cpp
template <typename TQuery, typename TAns>
void offline_segments(int n, vector<TQuery>& queries,
                      function<void(TQuery&)> direct_process,
                      function<void(int, TAns&)> add, function<void(int)> del,
                      TAns ans_reset) {
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

    TAns ans = ans_reset;
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
            ans = ans_reset;
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
```

#### 树上莫队

```cpp
class offline_tree_path {
   public:
    lfs& g;

    offline_tree_path(lfs& graph, int root = 1)
        : g(graph),
          size(g.n + 1, 0),
          top(g.n + 1, 0),
          son(g.n + 1, -1),
          dep(g.n + 1, 0),
          fa(g.n + 1, 0),
          enter(g.n + 1, 0),
          leave(g.n + 1, 0) {
        eular.reserve(g.n * 2);
        eular.push_back(0);
        dfs1(root, 0, 0);
        dfs2(root, root);
    }

    int query_lca(int x, int y) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            x = fa[top[x]];
        }
        if (dep[x] > dep[y]) swap(x, y);
        return x;
    }

    template <typename TAns>
    struct query {
        int id = 0;
        int x = 0, y = 0;
        int l = 0, r = 0;
        int lca = 0;
        TAns ans = 0;
    };

    template <typename TQuery, typename TAns>
    void solve(vector<TQuery>& queries, function<void(int, TAns&)> add,
               function<void(int, TAns&)> del, TAns ans_reset = TAns()) {
        for (auto& q : queries) {
            if (enter[q.x] > enter[q.y]) {
                swap(q.x, q.y);
            }
            int lca = query_lca(q.x, q.y);
            if (lca == q.x) {
                q.l = enter[q.x];
                q.r = enter[q.y];
            } else {
                q.l = leave[q.x];
                q.r = enter[q.y];
                q.lca = lca;
            }
        }
        int block_size = g.n * 2 / sqrt(queries.size() * 2 / 3);
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

                TAns ans = ans_reset;
        vector<char> ins(g.n + 1, 0);  // Avoid vector<bool>
        auto update_point = [&](int u) {
            if (ins[u]) {
                del(u, ans);
            } else {
                add(u, ans);
            }
            ins[u] = !ins[u];
        };
        int l = 1;
        int r = 0;
        for (auto& q : queries) {
            while (l > q.l) update_point(eular[--l]);
            while (r < q.r) update_point(eular[++r]);
            while (l < q.l) update_point(eular[l++]);
            while (r > q.r) update_point(eular[r--]);
            if (q.lca != 0) {
                update_point(q.lca);
            }
            q.ans = ans;
            if (q.lca != 0) {
                update_point(q.lca);
            }
        }
    }

   private:
    vector<int> size, top, son, dep, fa;

    void dfs1(int u, int fa, int d) {
        dep[u] = d;
        this->fa[u] = fa;
        size[u] = 1;
        for (int i = g.head[u]; i != -1; i = g.e[i].next) {
            int v = g.e[i].to;
            if (v != fa) {
                dfs1(v, u, d + 1);
                size[u] += size[v];
                if (son[u] == -1 || size[v] > size[son[u]]) son[u] = v;
            }
        }
    }

    vector<int> enter, leave;
    vector<int> eular;

    void dfs2(int u, int tp) {
        top[u] = tp;
        eular.push_back(u);
        enter[u] = eular.size() - 1;
        if (son[u] != -1) {
            dfs2(son[u], tp);
            for (int i = g.head[u]; i != -1; i = g.e[i].next) {
                int v = g.e[i].to;
                if (v != son[u] && v != fa[u]) dfs2(v, v);
            }
        }
        eular.push_back(u);
        leave[u] = eular.size() - 1;
    }
};
```

### 模拟退火

```cpp
const double TBEGIN = 3000;
const double EPS = 1e-14;
const double TEND = EPS;
const double DELTAT = 0.99;
const double INF = 1e18;

template <typename TValue>
TValue sa(function<void(function<double()>)> step, function<TValue()> f,
          function<void(bool)> update,
          decltype(mt19937::default_seed) seed =
              chrono::steady_clock::now().time_since_epoch().count()) {
    double t = TBEGIN;
    double ans = INF;
    mt19937 rd(seed);
    while (t > EPS) {
        uniform_real_distribution dis(0, t);
        step([&]() -> auto { return dis(rd); });
        TValue cur = f();
        if (cur < ans) {
            ans = cur;
            update(true);
        } else {
            bernoulli_distribution accept(max(1.0lf, exp((ans - nans) / t)));
            if (accept(rd)) {
                update(true);
            } else {
                update(false);
            }
        }
        t *= DELTAT;
    }
    return ans;
}
```

### 后缀自动机

```cpp
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
```

### 后缀数组

```cpp
const int INF = 0x3f3f3f3f;
const int MAXN = 1e6 + 10;
const int SIGMA = 26;

struct suffix_array {
    int sa[MAXN];     // 排名为i的后缀的位置 sa[rnk[i]] = i
    int rnk[MAXN];     // 后缀i的排名 rnk[sa[i]] = i
    int bucket[MAXN];  // 元素i出现的次数
    int tp[MAXN];      // 基数排序的第二关键字

    int operator[](int x) { return sa[x]; }
    // str 下标从1开始
    suffix_array(char* str, int len) {
        memset(sa, 0, sizeof sa);
        memset(rnk, 0, sizeof rnk);
        memset(bucket, 0, sizeof bucket);
        int m = 200;
        for (int i = 1; i <= len; i++) {
            rnk[i] = str[i];
            bucket[rnk[i]]++;
        }
        for (int i = 1; i <= m; i++) {
            bucket[i] += bucket[i - 1];
        }
        for (int i = len; i >= 1; i--) {
            sa[bucket[rnk[i]]--] = i;
        }
        int k = 1, p;
        do {
            int cnt = 0;
            memset(bucket, 0, sizeof bucket);
            for (int i = len - k + 1; i <= len; i++) {
                tp[++cnt] = i;
            }
            for (int i = 1; i <= len; i++) {
                if (sa[i] > k) tp[++cnt] = sa[i] - k;
            }
            for (int i = 1; i <= len; i++) {
                bucket[rnk[i]]++;
            }
            for (int i = 1; i <= m; i++) {
                bucket[i] += bucket[i - 1];
            }
            for (int i = len; i >= 1; i--) {
                sa[bucket[rnk[tp[i]]]--] = tp[i];
            }
            p = 1;
            swap(rnk, tp);
            rnk[sa[1]] = 1;
            for (int i = 2; i <= len; i++) {
                rnk[sa[i]] = (tp[sa[i]] == tp[sa[i - 1]] &&
                               tp[sa[i] + k] == tp[sa[i - 1] + k])
                                  ? p
                                  : ++p;
            } 
            k <<= 1;
            m = p;
        } while (p < len);
    }
};
```

## 对拍

### Shell

```sh
g++ example.cpp -o example.out
g++ example_std.cpp -o example_std.out
g++ example_dm.cpp -o example_dm.out
while true; do
    ./example_dm.out > example.in
    ./example_std.out < example.in > example_std.ans
    ./example.out < example.in > example.ans
    if diff example.ans example_std.ans; then
        printf "AC\n"
    else
        printf "WA\n"
        exit 0
    fi
done
```

### PowerShell

```ps1
g++ example.cpp -o example.exe --std=gnu++17
g++ example_std.cpp -o example_std.exe --std=gnu++17
g++ example_dm.cpp -o example_dm.exe --std=gnu++17
while($true) {
    ./example_dm.exe > example.in
    "Data maked."
    Get-Content example.in | ./example_std.exe > example_std.out
    "Std called."
    Get-Content example.in | ./example_std.exe > example.out
    "Program called."
    if ($LASTEXITCODE) {
        "RE!"
        break
    }
    $result = Compare-Object (Get-Content example.out) (Get-Content example_std.out)
    if ($result) {
        Write-Host $result
        break
    }
}
```
