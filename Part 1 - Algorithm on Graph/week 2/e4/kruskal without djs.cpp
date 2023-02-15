#include<bits/stdc++.h>

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
    cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v,w;
		cin >> u >> v >> w;
	    g[i].start = u;
	    g[i].end = v;
	    g[i].w = w;
    }
    sort(g+1,g+1+m,comp);
    for(int i=1;i<=m;i++)
   	cout<<g[i].start<<" "<<g[i].end<<" "<<g[i].w<<endl;
}
int p[N]; //parent
int MST = 0;

void Kruskal(){
    for(int i=1;i<=n;i++)
        p[i]=i;
    for(Arc e : g){
        if(p[e.start] != p[e.end]){
        	cout<<endl<<e.start<<"-"<<e.end<<"-"<<e.w; 
            MST = MST + e.w;
            int old_id=p[e.start]; //dinh cu
            int new_id=p[e.end];
            for(int i=1;i<=n;i++){
            	if(p[i]==old_id) //dinh dai dien = dinh cu
            	p[i]=new_id;
			}
    	}
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
	cout <<endl<< MST<<endl<<time_use;
	return 0;
}
