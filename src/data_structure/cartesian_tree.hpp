#include <cstring>

template <size_t SIZE, size_t STACK_SIZE = 1000>
class cartesian_tree {
   protected:
    int lson[SIZE], rson[SIZE], rt;
    int s[STACK_SIZE], top;
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