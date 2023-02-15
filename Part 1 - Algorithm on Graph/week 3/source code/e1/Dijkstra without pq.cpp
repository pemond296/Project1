#include<bits/stdc++.h>

using namespace std;

#define N 90000001

int n,m;
vector<pair<int,int>> adj[1000000]; // ma tran ke

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
            g[a].w = 1+rand()%100;
            a++;
        }
    }
    // for(int i=1;i<=m;i++) 
	//     cout<<g[i].start<<" "<<g[i].end<<" "<<g[i].w<<endl;
    for(int i=1;i<=m;i++){
        adj[g[i].start].push_back({g[i].end,g[i].w});
        adj[g[i].end].push_back({g[i].start,g[i].w});
    }
}

int p[N];

void thepath(int s, int i){
	    vector<int> path;
    while(1){
    	path.push_back(i);
    	if(i==s) break;
    	i = p[i];
	}
	//truy vet nguoc duong di
	reverse(begin(path),end(path));
	for(int x : path) cout<<x<<" ";
}

void Dijkstra(int s){
    clock_t start, shutdown;
    double time_use;
    vector<int> d(n+1,INT_MAX);
    d[s] = 0;
    p[s] = s;
    start=clock();
    int V = n-1; //dinh da duyet
    while(V>0){
        for(int i=1;i<=n;i++){
                for(pair<int,int> e : adj[i]){
                    int j = e.first;
                    int trongso = e.second;
                    if(d[j] > d[i] + trongso){
                        d[j] = d[i] + trongso;
                        p[j]=i;
                    }
                }
            }
        V--;
    }
    shutdown=clock();
	time_use = (double)(shutdown-start)/CLOCKS_PER_SEC;
    // for(int i = 1;i<=n;i++){
    // 	cout<<"d["<<i<<"] = "<<d[i]<<"   "<<"Duong di la: ";
	// 	thepath(s,i); 
	// 	cout<<endl;
	// }
	cout<<endl<<time_use;
}

int main(){
    input();
    cout<<endl;
    int s;
    cin>>s;
    Dijkstra(s);
    return 0;
}
