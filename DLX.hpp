#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdio>
using namespace std;

const int N = 4;
const int SIZE = N*N;
const int ROW = SIZE*SIZE*SIZE + 10;  //
const int COL = SIZE*SIZE*N + 10;     //这三个常数是必须的
const int POINT = ROW*4 + COL;        //

class DLX{
    public:
        int n,m;
        int pcnt;
        int ansc,ans[ROW];
        
        DLX(int N,int M):n(N),m(M){
            pcnt = 0;
            ansc = 0;
            memset(ans,0,sizeof ans);
            memset(p,0,sizeof p);
            memset(row,0,sizeof row);
            memset(col,0,sizeof col);
            
            for(int i = 0;i<=m;i++){
                col[i] = 0;
                p[i].u = p[i].d = i;
                p[i].l = i-1;
                p[i].r = i+1;
            }
            p[0].l = m;
            p[m].r = 0;
            pcnt = m;
            for(int i = 1;i<=n;i++){
                row[i] = -1;
            }
        }
        
        void insert(int r,int c){
            pcnt++;
            p[pcnt].col = c;
            col[c]++;
            p[pcnt].row = r;
            p[pcnt].d = p[c].d;
            p[p[c].d].u = pcnt;
            p[pcnt].u = c;
            p[c].d = pcnt;
            
            if(row[r] == -1){
                row[r] = p[pcnt].l = p[pcnt].r = pcnt;
            }else{
                p[pcnt].r = p[row[r]].r;
                p[p[row[r]].r].l = pcnt;
                p[pcnt].l = row[r];
                p[row[r]].r = pcnt;
            }
        }
        
        bool search(int d){
            //clog << "enter" << d << endl;
            if(p[0].r == 0){
                ansc = d;
                return true;
            }
            int c = p[0].r;
            for(int i = p[0].r;i!=0;i = p[i].r){
                if(col[i]<col[c]){
                    c = i;
                }
            }
            remove(c);
            for(int i = p[c].d;i!=c;i = p[i].d){
                ans[d] = p[i].row;
                for(int j = p[i].r;j!=i;j = p[j].r){
                    remove(p[j].col);
                }
                if(search(d+1)){
                    return true;
                }				
                for(int j = p[i].l;j!=i;j = p[j].l){					
                    resume(p[j].col);
                }
            }
            resume(c);
            //clog << "exit " << d << endl;
            return false;
        }
        
    protected:
        struct node{
            int u,d,l,r;
            int row,col;
        }p[POINT];
        int row[ROW];
        int col[COL];
        
        void remove(int c){
            //clog << "remove " << c << endl; 
            p[p[c].r].l = p[c].l;
            p[p[c].l].r = p[c].r;
            for(int i = p[c].d;i!=c;i = p[i].d){
                for(int j = p[i].r;j!=i;j = p[j].r){
                    p[p[j].d].u = p[j].u;
                    p[p[j].u].d = p[j].d;
                    col[p[j].col]--;
                }
            }
        }
        
        void resume(int c){
            //clog << "resume " << c << endl; 
            for(int i = p[c].u;i!=c;i = p[i].u){
                for(int j = p[i].l;j!=i;j = p[j].l){
                    p[p[j].d].u = p[p[j].u].d = j;
                    col[p[j].col]++;
                }
            }
            p[p[c].r].l = p[p[c].l].r = c;
        }
};
