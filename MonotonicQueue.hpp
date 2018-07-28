#include <iostream>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>
using namespace std;

//这个不好封装

const int MAXN = 10e6+10;

deque<int> qmin;
deque<int> qmax;
int mins[MAXN], maxs[MAXN];

int a[MAXN];

int main(){
	ios::sync_with_stdio(false);
	int n,k;
	cin >> n >> k;
	for(int i = 0;i<n;i++){
		cin >> a[i];
	}
	for(int i = 0;i<n;i++){
		while(!qmax.empty()&&a[qmax.back()]<=a[i]){
			qmax.pop_back();
		}
		qmax.push_back(i);
		while(!qmin.empty()&&a[qmin.back()]>=a[i]){
			qmin.pop_back();
		}
		qmin.push_back(i);
		while(qmin.front()<=i-k&&qmin.front()!=qmin.back()){
			qmin.pop_front();
		}
		while(qmax.front()<=i-k&&qmax.front()!=qmax.back()){
			qmax.pop_front();
		}
		mins[i] = a[qmin.front()];
		maxs[i] = a[qmax.front()];
	}
	for(int i = k-1;i<n;i++){
		cout << mins[i] << ' ';
	}
	cout << endl;
	for(int i = k-1;i<n;i++){
		cout << maxs[i] << ' ';
	}
	cout << endl;
}