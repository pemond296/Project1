#include <bits/stdc++.h>
#define MAX 1000

using namespace std;

int N;              // number of customers
int K;              // number of vehicles
int Q;              // capacity of each vehicle
int d[MAX] ;        // d[i] is the demand of customer i
int y[MAX] ;        // y[k] is the first point of container[k]; and y[1] < y[2] < ... < y[k];
int x[MAX] ;        // x[i] is the next point of container in point i on route;
int segments;       // number of segments on the solution routes
bool visited[MAX] ; // visited[v] = true , means point v is visited
int load[MAX];      // load[k] is the total of demand of customers on the route k
int c[100][100];
int path[MAX];      // path[i] is total length of vehicle[i] 's path;
int result = 999999;

void input(){
    cin >> N >> K >> Q;
    for(int i = 1; i <= N; i++){
        cin >> d[i] ;
    }
    for(int i = 0; i<=N; i++){
        for(int j = 0; j<=N; j++){
            cin >> c[i][j];
        }
    }
}

void printX(int k){
    if(x[k] != 0) {
        cout << " "<< x[k];
        printX(x[k]);
    }else{
        cout << " 0" ;
    }
    
}

void solution(){
    bool checkSolution = true;
    int res = 0;
    for(int i = 1; i<=N; i++){
        if(visited[i] == false) checkSolution = false;
    }
    if (checkSolution == true){
    for(int i = 1; i<=K;i++){
        res += path[i];
    }
    if(res < result) result = res;
    }
    
}

bool checkX(int v, int k){
    if(visited[v] == true) return false;
    if(d[v] + load[k] > Q) return false;
    return true;
}

void TryX(int v, int k){ // v is current point of vehicle[k]
    for(int i = 0; i<= N; i++){
        if(i == 0){
            path[k] += c[v][0];
            if(k == K){
                solution();
                path[k] -= c[v][0];
            }else{
                 TryX(y[k+1], k+1);
                 path[k] -= c[v][0];
            }
        }else{
            if(checkX(i, k)){
                x[v] = i;
                load[k] += d[i];
                visited[i] = true;
                path[k] += c[v][i];
                TryX(i,k);
                x[v] = 0;
                load[k] -= d[i];
                visited[i] = false;
                path[k] -= c[v][i];
            }
        }
    }
}

bool checkY(int v, int k){
    if(d[v] > Q) return false;
    if(visited[v] == true) return false;
    return true;
}

void TryY(int k){
    for(int v = y[k-1] + 1; v<=N; v++){
       if(checkY(v, k)) {
            y[k] = v;
        visited[v] = true;
        load[k] += d[v];
        path[k] += c[0][v];
        if(k == K){
            TryX(y[1], 1);
            visited[v] = false;
            load[k] -= d[v];
            y[k] = 0;
            path[k] -= c[0][v];
        }else{
            TryY(k+1);
            visited[v] = false;
            load[k] -= d[v];
            y[k] = 0;
            path[k] -= c[0][v];
        }
       }
    }
}

int main(){
    input();
    TryY(1);
    cout << result;
    return 0;
}