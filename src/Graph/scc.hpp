#include <stack>
#include "lfs.hpp"

class scc : public lfs {
   public:
   	int scccnt;
    int belong[MAXN];
	
	scc(int n) : lfs(n) {
    	memset(dfn, -1, sizeof dfn);
        memset(low, -1, sizeof low);
        memset(ins, false, sizeof ins);
		memset(belong,0,sizeof belong);
        tim = 1;
        scccnt = 0;
    }
	
    void solve() {
		for(int i = 1;i<=n;i++){
			if(dfn[i] == -1){
				tarjan(i);
			}
		}
    }
	
	//缩点，先调用solve
	void create_new(lfs* map){
		for(int i = 1;i<=n;i++){
			for(int j = head[i];j!=-1;j = e[j].next){
				int u = belong[i];
				int v = belong[e[j].to];
				if(u != v){
					map->adde(u,v,e[j].w);
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
