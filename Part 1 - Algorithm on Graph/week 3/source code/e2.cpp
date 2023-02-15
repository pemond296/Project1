#include<bits/stdc++.h>
#define N 100

using namespace std;

int n;
int cap[N][N];//tap luu luong
vector<int> adj[N]; //tap dinh ke
int p[N]; //parent


int bfs(int source, int sink) {
    memset(p, -1, sizeof(p));
    p[source] = -2;
    queue<pair<int, int>> Q; 
    Q.push({source, INT_MAX});

    while (!Q.empty()) {
        int cur = Q.front().first;
        int flow = Q.front().second;
        Q.pop();

        for (int next : adj[cur]) {
            if (p[next] == -1 && cap[cur][next]) {
                p[next] = cur;
                int new_flow = min(flow, cap[cur][next]);
                if (next == sink)
                    return new_flow;
                Q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int EdmondsKarp(int source, int sink){
   	int maxFlow = 0;
   	while(true){
      	int flow = bfs(source, sink);
      	if (flow == 0){
         	break;
      	}
      	maxFlow += flow;
      	int cur = sink; //nut hien tai
      	while(cur != source){
         	int pre= p[cur]; // nut nguon
         	cap[pre][cur] -= flow;
         	cap[cur][pre] += flow;
         	cur = pre;
      }
   }
	return maxFlow;
}

int main(){
   	int nodes,edge; //nodes va edge
	cin>>nodes>>edge;    
    for(int i=1;i<=edge;i++){
        int from ,to ,capacity;
        cin>>from>>to>>capacity;
        cap[from][to] = capacity;
        adj[from].push_back(to);
        adj[to].push_back(from);
	}
	int source,sink;
	cin>>source>>sink;
	cout<<"Max flow: "<<EdmondsKarp(source,sink);
}
