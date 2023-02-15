#include<bits/stdc++.h>

using namespace std;

#define fv(i, v) for(int i = 0; i < (int)v.size(); i++)
#define f(i, k, n) for(int i = k; i < n; i++)

struct node {
	int i;
	int j;
	int index;
};

class Parking {
	public:
	
	// duyet bai do xe theo chieu rong
	bool BFS(const node &C, const vector<node> &Ps, const vector<string> &park, int **graph) {
		bool visited[park.size()][park[0].size()];
		fv(i, park) {
			fv(j, park[0]) {
				visited[i][j] = false; 
			}
		}
		queue<node> q;
		q.push({ C.i, C.j, 0 }); // su dung index de dem so thoi gian
		node N;
		while(!q.empty()) {
			N = q.front(); //gan N bang node o dau hang doi
			q.pop();
			if(N.i < 0 || N.i >= (int)park.size() || N.j < 0 || N.j >= (int)park[0].size()) continue;
			if(visited[N.i][N.j]) continue;	//
			if(park[N.i][N.j] == 'X') continue; // neu vi tri do la tuong thi continue
			if(park[N.i][N.j] == 'P') {
				fv(i, Ps) { //duyet nhung diem do xe
					if(Ps[i].i == N.i && Ps[i].j == N.j) {
						//vi tri xe C va vi tri bai do xe i = vi tri cua node N
						graph[C.index][Ps[i].index] = N.index;
					}
				}
			}	
			visited[N.i][N.j] = true; //nhung diem dau cham - di duoc
			q.push({ N.i - 1, N.j, N.index + 1 }); // day vao hang doi nhung nuoc di tiep theo cua node N
			q.push({ N.i + 1, N.j, N.index + 1 });
			q.push({ N.i, N.j - 1, N.index + 1 });
			q.push({ N.i, N.j + 1, N.index + 1 });
		}
		return false;
	}
	
	// ham ket noi xe va diem do xe
	bool connected(int **graph, const vector<node> &Cs, const vector<node> &Ps){
		bool found; //kiem tra con cho do xe nao khong
		map<int, int> PCs; //khai bao map co thuoc tinh cua key va value la so nguyen 
		int C;
		fv(i, Cs) {
			// kiem tra xe co the vao diem do nao khong
			found = false;
			f(j, 0, (int)Ps.size()) {
				if(graph[i][j] > 0) { 
					found = true;
					break;
				}
			}
			if(!found) return false;
			// tim diem do xe con trong
			found = false;
			f(j, 0, (int)Ps.size()) {
				if(graph[i][j] > 0 && PCs.count(j) == 0) {
					PCs[j] = i;
					found = true;
					break;
				}
			}
			if(!found) { // xe co the den diem do, nhung ma bi day`
				f(j, 0, (int)Ps.size()) {
					// kiem tra diem do nay` da duoc su dung chua
					if(graph[i][j] > 0) {
						// day xe vao diem do xe
						C = PCs[j];
						// kiem tra xe co the doi sang diem do khac khong
						f(k, 0, (int)Ps.size()) {
							// co diem do va no chua duoc su dung
							if(graph[C][k] > 0 && PCs.count(k) == 0) {
								PCs[j] = i; //giai phong diem do cu
								PCs[k] = C;
								found = true;
								break;
							}
						}
					}
					if(found) break;
				}
			}
			if(!found) return false;
		}
		return true;	
	}
	
	int minTime(vector<string> park) {
		int ci = 0, pi = 0;
		vector<node> Cs, Ps;
		fv(i, park) {
			fv(j, park[i]) {
				if(park[i][j] == 'C') {
					Cs.push_back({ i, j, ci++ }); //day vi tri xe vao trong Cs
				}
				else if(park[i][j] == 'P') {
					Ps.push_back({ i, j, pi++ }); //day vi tri  diem do vao Ps
				}
			}
		}
		// ma tran chua thoi gian di can thiet tu xe den diem do
		int **graph = new int*[Cs.size()];
		fv(i, Cs) {
			graph[i] = new int[Ps.size()]; 
		}
		fv(i, Cs) {
			fv(j, Ps) {
				graph[i][j] = 0; 
			}
		}
		// thuc hien duyet theo chieu rong va tra ve nhung nuoc di
		fv(i, Cs) {
			BFS(Cs[i], Ps, park, graph); 
		}
		//in ra mang thoi gian can thiet de xe di den diem do
		int hi = 0;
		if(true){
			fv(i, Cs) {
				fv(j, Ps) {
					cout << graph[i][j] << " ";
					if(graph[i][j] > hi) hi = graph[i][j];
				}
				cout << endl;
			}
		}
		cout<<endl;
		//neu khong the ket noi toan bo xe va diem do thi tra ve gia tri -1
		if(!connected(graph, Cs, Ps)) return -1; 
		int lo = 1;
		// int hi = 20; //chon hi sao cho hi > duong di lon nhat trong graph
		int m; 
		bool c;
		while((hi - lo) > 1) {
			m = (hi + lo) / 2;
			// tao 1 mang clone dua tren mang graph de tien hanh kiem tra
			int **clone = new int*[Cs.size()];
			fv(i, Cs) {
				clone[i] = new int[Ps.size()];
			}
			fv(i, Cs) {
				fv(j, Ps) {
					clone[i][j] = graph[i][j];
				}
			}
			fv(i, Cs) {
				fv(j, Ps) {
					if(clone[i][j] > m) clone[i][j] = 0;
					else if(clone[i][j] > 0) clone[i][j] = 1;
				}
			}
			c = connected(clone, Cs, Ps);
			if(c) {
				hi = m;
			}
			else {
				lo = m;
			}
			// if(true) {
			// 	cout << hi << " // " << lo << endl;
			// 	cout << m << " > " << c << endl;
			// 	fv(i, Cs) {
			// 		fv(j, Ps) {   
			// 			cout << clone[i][j] << " ";
			// 		}
			// 		cout << endl;
			// 	}
			// }
			// cout<<endl;
		}
		return hi; // gia tri cua hi = gia tri nho nhat ban dau cua graph khi clone = 0
	}
};

void test(vector<string> park, int expected) {
	Parking p;
	int result = p.minTime(park);
	cout << (result == expected ? "passed" : "failed") << " => expected: " << expected << ", got: " << result << endl;
}

int main() {
	// test({"C.....P",
	// 	  "C.....P",
	// 	  "C.....P"}, 6);
		  
	// test({"C.X.....", 
	// 	  "..X..X..",
	// 	  "..X..X..",
	// 	  ".....X.P"}, 16);
				  
	// test({"XXXXXXXXXXX",
	//       "X......XPPX", 
	// 	  "XC...P.XPPX",
	//  	  "X......X..X", 
	// 	  "X....C....X",
	// 	  "XXXXXXXXXXX"}, 5);

	test({"XXXXXXXXXXX",
	      "X..C...XPPX", 
		  "XC...P.XPPX",
	 	  "X......X..X", 
		  "X....C....X",
		  "XXXXXXXXXXX"}, 5);
	  
	// test({"CCCCC",
	//       ".....",
	// 	  "PXPXP"}, -1);
		  	  
	// test({"..X..", 
	//       "C.X.P",
	// 	  "..X.."}, -1);

}
