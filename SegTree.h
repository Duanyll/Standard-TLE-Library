/*
	Name: SegTree
	Author: Duanyll
	Date: 19/07/18 11:53
	Description: 线段树模板（POJ3468） 
*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 100010;
 
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1

template<typename value_t>
class segtree{
	public:
		segtree(int cnt){
			this->cnt = cnt;
		}
		void init(){
			_Build(1,cnt,1);
		}
		void add_range(int l,int r,value_t val){
			_Update(l,r,val,1,cnt,1);
		}
		value_t query(int l,int r){
			return _Query(l,r,1,cnt,1);
		}
	private:
		value_t lazy[MAXN*4];
		value_t sum[MAXN*4];
		int cnt;

		void PushUP(int rt){
    		sum[rt]=sum[rt<<1]+sum[rt<<1|1];
		}
 
		void PushDown(int rt,int m){
    		if(lazy[rt]){
    	    	lazy[rt<<1]+=lazy[rt];
     		   	lazy[rt<<1|1]+=lazy[rt];
    	    	sum[rt<<1]+=(m-(m>>1))*lazy[rt];
        		sum[rt<<1|1]+=(m>>1)*lazy[rt];
        		lazy[rt]=0;
    		}
		}
 
		void _Build(int l,int r,int rt){
    		lazy[rt]=0;
    		if(l==r){
    		    cin >> sum[rt];
        		return;
    		}
    		int m=(l+r)>>1;
    		_Build(lson);
    		_Build(rson);
    		PushUP(rt);
		}
 
		void _Update(int L,int R,value_t val,int l,int r,int rt){
    		if(L<=l&&R>=r){
        		lazy[rt]+=val;
        		sum[rt]+=(value_t)val*(r-l+1);
        		return;
    		}
    		PushDown(rt,r-l+1);
    		int m=(l+r)>>1;
    		if(L<=m)
        		_Update(L,R,val,lson);
    		if(R>m)
        		_Update(L,R,val,rson);
    		PushUP(rt);
		}
 
		value_t _Query(int L,int R,int l,int r,int rt){
    		if(L<=l&&R>=r)
    		    return sum[rt];
    		PushDown(rt,r-l+1);
    		int m=(l+r)>>1;
    		value_t ret=0;
    		if(L<=m)   
				ret+=_Query(L,R,lson);
    		if(R>m)    
				ret+=_Query(L,R,rson);
    		return ret;
		}

	#undef lson
	#undef rson
};
