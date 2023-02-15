#include <bits/stdc++.h>

using namespace std;

#define N 90000001

int n,m;
struct Arc{
	int start;
	int end;
	int w;
};

bool comp(Arc a, Arc b){
	return a.w<b.w;
}

Arc g[N];

void input(){
	cin >> n;
	m=(n*(n-1))/2;
	int a=1;
	for(int i=1;i<n;i++){
		int,
		for(int j=i+1;j<=n;j++){
			g[a].start=i;
			g[a].end=j;
			g[a].w=1+rand()%7;
			a++;
		}
	}
	sort(g+1,g+1+m,comp);
//	for(int i=1;i<=m; i++) 
//		cout << g[i].start << ' ' << g[i].end <<' ' << g[i].w << endl;
}

//disjoint set
int p[N]; // parent
int r[N]; // rank

void makeSet(){
   for(int i = 1; i<= m; i++)
		{
			p[i] = i;
			r[i] = 1;
		}
}
int Find(int x){ 
	// tim dinh dai dien 
    if(x != p[x]) p[x] = Find(p[x]);
    return p[x];
}

void Unify(int x, int y){
    // ket hop 2 tap hop chua x, y
    if(r[x] > r[y]) p[y] = x;
    else{
        p[x] = y;
        if(r[x] == r[y]) r[y] = r[y] + 1;
    }
}

int MST=0;
int edge = 0;

void Kruskal(){
	makeSet();
	int r1, r2;
	for(int i = 1; i<=m; i++)
	{
		r1 = Find(g[i].start);
		r2 = Find(g[i].end);
		if(r1 != r2) {
			cout<<endl<<g[i].start<<"-"<<g[i].end<<"-"<<g[i].w; 
			MST = MST + g[i].w;
			Unify(r1, r2);
			edge++;
		}
		if(edge == n-1) break;
	}
}
int main(){
	clock_t start,end;
	double time_use;
	input();
	start=clock();
	Kruskal();
	end=clock();
	time_use=(double)(end-start)/CLOCKS_PER_SEC;
	cout<<endl<<MST<<endl<<time_use;
	return 0;
}
