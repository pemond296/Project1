#include<bits/stdc++.h>

#define N 100

using namespace std;

int n, m, edge; //dinh, dinh, canh
int p[N];
int visited[N];
int s = 0;
vector<int> adj[N]; //tap dinh ke

void input(){
    cin>>n>>m>>edge;
    if (n*m < edge) return;
    int x,y;
    while(edge-->0){
    	cin>>x>>y;
        adj[x].push_back(y);
	}
}

bool visit(int u) {
    if (visited[u] != s)
        visited[u] = s;
    else
        return false;

    for (int i=0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (!p[v] || visit(p[v])) {
            p[v] = u;
            return true;
        }
    }
    return false;
}

int main(){
    input();
    int count = 0; //tong so canh trong cap ghep cuc dai
    for (int i=1; i<=m; i++) {
        s++;
        count += visit(i);
    }
    cout<<endl;
   	cout<<count<<endl;
    for (int i=1;i<=n;i++)
        if (int j=p[i])
            cout<<j<<" "<<i<<endl; // canh duoc chon vao cap ghep cuc dai
}
