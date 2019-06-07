#include <queue>
#include "lfs.hpp"

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
