#include <vector>
#include "LFS_base.hpp"

class Cut_Vertex:public LFS{
	protected:
		int dfn[MAXN],low[MAXN];
		int tim;
		void dfs(int u,int fa){
			int cc = 0;
			dfn[u] = low[u] = tim++;
			for(int i = head[u];i!=-1;i = e[i].next){
				int v = e[i].to;
				if(dfn[v]==-1){
					dfs(v,u);
					cc++;
					low[u] = min(low[u],low[v]);
					if(fa!=-1 && low[v]>dfn[u]){
						ans.push_back(u);
					}
				}else if(v!=fa){
					low[u] = min(low[u],dfn[v]);
				}
			}
			if(fa==-1 && cc>=2){
				ans.push_back(u);
			}
		}
	public:
		vector<int> ans;
		Cut_Vertex(){
			memset(head, -1, sizeof head);
			ecnt = 0;
		}
		
		void solve(int n){
			memset(dfn,-1,sizeof dfn);
			tim = 1;
			
			for(int i = 1;i<=n;i++){
				if(dfn[i]==-1){
					dfs(i,-1);
				}
			}
			
			sort(ans.begin(),ans.end());
			vector<int>::iterator it = unique(ans.begin(),ans.end());
			ans.erase(it,ans.end());
		}
};
