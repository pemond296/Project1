#include<bits/stdc++.h>

using namespace std;

#define N 90000001

int n,m;
vector<pair<int,int>> adj[1000000];
bool used[N];
int d[N];

struct Arc{
    int start;
    int end; 
    int w;
};

Arc g[N];
input(){
    cin>>n;
    m=(n*(n-1))/2;
    int a=1;
    for(int i=1;i<n;i++){
        for(int j=i+1;j<=n;j++){
            g[a].start = i;
            g[a].end = j;
            g[a].w = 1+rand()%7;   
            a++;     
        }
    }
//    for(int i=1;i<=m;i++) 
//    cout<<g[i].start<<" "<<g[i].end<<" "<<g[i].w<<endl;
    for(int i=1;i<=m;i++){
        adj[g[i].start].push_back({g[i].end,g[i].w});
        adj[g[i].end].push_back({g[i].start,g[i].w});
    }
    memset(used, false, sizeof(used));
    for(int i=1;i<=n;i++) d[i] = INT_MAX;
}

int p[N]; //parent;

void prim(int u){
	clock_t start,end;
	double time_use;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > Q;
    // hang doi uu tien co phan tu dau tien co phan first nho nhat
    vector <Arc> MST;
    int sum =0;
    Q.push({0,u});
    start =clock();
    // lap voi hang doi uu tien chua rong
    while(!Q.empty()){
        pair<int,int> top = Q.top();Q.pop();
        int trongso = top.first;
        int dinh = top.second;
        if(used[dinh]) continue;
        sum += trongso;
        used[dinh] = true;
        if(u != dinh) 
        MST.push_back({dinh,p[dinh],trongso});
    // duyet danh sach ke cua dinh vua xet
        for(auto e : adj[dinh]){
        int y = e.first;
        int w = e.second;
        if(!used[y] && d[y]>w){
            Q.push({w,y});
            d[y] = w;
            p[y] = dinh;
        }
    }
}
	end=clock();
	time_use=(double)(end-start)/CLOCKS_PER_SEC;
    for( auto e : MST)
    cout<<endl<<e.start<<" "<<e.end<<" "<< e.w;
    cout<<endl<<sum;
    cout<<endl<<time_use;
}

int main(){
    input();
    prim(1);
    return 0;
}
