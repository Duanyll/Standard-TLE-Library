#include <cmath>
using namespace std;

template<typename T>
class block{
  int bl[MAXN];
  T v[MAXN];	//点权 
  T atag[MAXN],sum[MAXN];//块操作 
  int blo;//块的大小 
  int n;
public:
  block(int n){
    this->n = n;
    blo = sqrt(n);
    for(int64 i = 1;i<=n;i++){
      v[i] = read();
      bl[i] = (int64)(i-1)/blo+1;
      sum[bl[i]]+=v[i]; 
    }
  }
  
  void add(int l,int r,T x){
    int siz = min(r,bl[l]*blo);
    for(int i = l;i<=siz;i++){
      v[i]+=x;
      sum[bl[i]]+=x;
    }
    if(bl[l]!=bl[r]){
      for(int i = (bl[r]-1)*blo+1;i<=r;i++){
        v[i]+= x;
        sum[bl[i]]+=x;
      }
    }
    for(int i = bl[l]+1;i<=bl[r]-1;i++){
      atag[i]+=x;
    }
  }

  T query(int l,int r){
    int siz = min(r,bl[l]*blo);
    T ans = 0;
    for(int i = l;i<=siz;i++){
      ans+=v[i]+atag[bl[i]];
    }
    if(bl[l]!=bl[r]){
      for(int i = (bl[r]-1)*blo+1;i<=r;i++){
        ans+=v[i]+atag[bl[i]];
      }
    }
    for(int i = bl[l]+1;i<=bl[r]-1;i++){
      ans+=atag[i]*blo+sum[i];
    }
    return ans;
  }
}
