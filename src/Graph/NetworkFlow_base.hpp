#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 110;

class network_flow{
	protected:
		struct edge{
			int from,to;
			int cap,flow;
			edge(int u,int v,int c,int f = 0):from(u),to(v),cap(c),flow(f) {};
		};		
		int n,m;
		vector<edge> e;
		vector<int> g[MAXN];
	public:
		network_flow(){
			n = 0;
			m = 0;
		}
		
		network_flow(int n){
			this->n = n;
			m = 0;
		}
		
		adde(int from,int to,int cap){
			e.push_back(edge(from,to,cap));
			g[from].push_back(e.size() - 1);
			e.push_back(edge(to,from,0));
			g[to].push_back(e.size()-1);
			m += 2;
		}
};
