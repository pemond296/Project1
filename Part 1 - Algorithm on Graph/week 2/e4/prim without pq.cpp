#include<bits/stdc++.h>

using namespace std;

#define N 90000001

int n,m;
vector<pair<int,int>> adj[1000000]; // chuyen danh sach canh ve danh sach ke
bool used[N]; //danh dau dinh da tham, true thuoc MST, false thuoc tap dinh chua xet


struct Arc{
	int start;
	int end;
	int w;
};

Arc g[N];

void input(){
	cin>>n;
	m=(n*(n-1))/2;
	int a=1;
	for(int i=1;i<n;i++){
		for(int j=i+1;j<=n;j++){
			g[a].start = i;
			g[a].end = j;
			g[a].w = 1+rand()% 7;
			a++;
		}
	}
//	for(int i=1;i<=m;i++)
//    	cout<<g[i].start<<" "<<g[i].end<<" "<<g[i].w<<endl;
	for(int i=1;i<=m;i++){
		adj[g[i].start].push_back({g[i].end, g[i].w});
		adj[g[i].end].push_back({g[i].start,g[i].w});
	}
	memset(used, false, sizeof(used));
}

void prim(int u){
	clock_t start,end;
	double time_use;
	vector <Arc> MST; //cay khung
	int sum=0; //chieu dai cay khung
	used[u] = true; //dua dinh u vao MST
	start=clock();
	while(MST.size() < n-1){
		// tim canh ngan nhat co 1 dinh thuoc V 1 dinh thuoc V(MST)
		int min_w = INT_MAX;
		int x,y; // luu 2 dinh cua canh
		for(int i=1;i<=n;i++){
			// neu dinh i thuoc tap V(MST)
			if(used[i]){
				// duyet danh sach ke cua dinh i
				for( pair<int,int> e : adj[i]){
					int j = e.first;
					int trongso = e.second;
					if( !used[j] && trongso<min_w){
						min_w = trongso;
						x = j;
						y = i;
					}
				}
			}
		}
		MST.push_back({x,y,min_w});
		sum += min_w;
		used[x] = true; // them dinh x vao MST 
	}
	end=clock();
	time_use=(double)(end-start)/CLOCKS_PER_SEC;
	for(Arc e: MST) cout<<endl<<e.start<<" "<<e.end<<" "<<e.w;
	cout<<endl<<sum ;
	cout<<endl<<time_use;
}
int main(){
	input();;
	prim(1);
	return 0;
}
