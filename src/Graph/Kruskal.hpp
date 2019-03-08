#include "LFS_base.hpp"
#include <queue>
using namespace std;

const int MAXM = 1e5+10;

class kruskal {
	struct edge {
    	int to, from;
    	int dis;
    	edge(int _t = 0, int _f = 0, int _dis = 0) {
        	to = _t;
        	from = _f;
        	dis = _dis;
    	}
	} e[MAXM * 2];

	int ecnt;
	int n;
	int fa[MAXN];
	int find(int u) { return (fa[u] == u) ? u : fa[u] = find(fa[u]); }
	
	static bool cmp(const edge& a,const edge& b){
		return a.dis < b.dis;
	}

  public:
	kruskal(int n){
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
	
	void create_tree(LFS *tree){
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
