#include<bits/stdc++.h>

using namespace std;

#define N 90000001

int n,m;
vector<pair<int,int>> adj[1000000];
struct Arc{
    int start;
    int end;
    int w;
};

Arc g[N];
void input(){
    cin >>n;
    m=(n*(n-1))/2;
    int a=1;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            g[a].start = i;
            g[a].end = j;
            g[a].w = 1 + rand()%100;
            a++;
        }
    }
//    for(int i=1;i<=m;i++) 
//   		cout<<g[i].start<<" "<<g[i].end<<" "<<g[i].w<<endl;
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
	clock_t start,shutdown;
    double time_use;
    vector<int> d(n+1, INT_MAX);
    d[s] = 0;
    p[s] = s;
   	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > Q;
    Q.push({0,s});
    start=clock();
    while(!Q.empty()){
        //Chon dinh co khoang cach tu dinh s nho nhat
        pair<int,int> top = Q.top();
        Q.pop();
        int trongso = top.first;
        int dinh = top.second;
        //neu khoang cach > trong so tu dinh s den u thi bo qua
        if(trongso>d[dinh]) continue;
        //Cap nhat khoang cach tu s toi cac dinh ke voi u
        for(auto j : adj[dinh]){
            int i = j.first;
            int w = j.second;
            if(d[i] > d[dinh] + w){
                d[i] = d[dinh] + w;
                Q.push({d[i], i});
                p[i] = dinh; // dinh truoc i la dinh
            }
        }
    }
    shutdown=clock();
    time_use=(double)(shutdown-start)/CLOCKS_PER_SEC;
    
//    for(int i = 1;i<=n;i++){
//    	cout<<"d["<<i<<"] = "<<d[i]<<"   "<<"Duong di la: ";
//		thepath(s,i); 
//		cout<<endl;
//	}
	cout<<time_use;
}

int main(){
    input();
    cout<<endl;
    int s;
    cin>>s;
    Dijkstra(s);
    return 0;
}
