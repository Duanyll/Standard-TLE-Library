#include <cstring>

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
