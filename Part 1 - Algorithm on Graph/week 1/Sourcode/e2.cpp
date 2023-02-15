#include<bits/stdc++.h>

using namespace std;

void nhap(int n, int m, int a[100][100]){
	for(int i=0;i<n;i++){
		for(int j=0; j<m;j++) 
		cin>>a[i][j];
	}
}

void xuat(int n,int m, int a[100][100]){
	for(int i=0;i<n;i++){
		for(int j=0; j<m;j++) 
		cout<<a[i][j]<<" ";
		cout<<endl;
	}
}

int tichmatran(int a[100][100],int b[100][100],int m,int k,int n){
	int c[100][100];
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			int sum=0;
			for(int d=0;d<k;d++){
				sum = sum + a[i][d] * b[d][j];
			}
			c[i][j]=sum;
		}
	}
	xuat(m,n,c);
}

int main(){
	int a[100][100];
	int b[100][100];
	int m,k,n;
	cin>>m>>k>>n;
	nhap(m,k,a);
	nhap(k,n,b);
	tichmatran(a,b,m,k,n);
}
