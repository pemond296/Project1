#include<bits/stdc++.h>

using namespace std;

void in(int a[], int n){
	for(int i=0;i<n+1;i++){
		if(i==0) cout<<a[0]<<" + ";
		if(i!=0)
		cout<<a[i]<<"x^"<<i;
		if(i!=0 && i!=n) 
		cout<<" + ";
	}
}

void tich(int a[], int b[],int m, int n){
	int s[10];
	for(int i=0;i<m+n+1;i++)
	s[i]=0;
	for(int i=0;i<m+1;i++){
		for(int j=0;j<n+1;j++){
			s[i+j] += a[i]*b[j];
		}
	}
		in(s,m+n);
}

void nhap(int a[], int m){
	for(int i=0;i<m+1;i++){
		cin>>a[i];
	}
}

int main(){
	int m,n;
	cout<<"Nhap vao bac cua da thuc thu nhat: "; cin>>m;
	int a[m];
	cout<<"Nhap da thuc thu nhat: "; 
	nhap(a,m);
	cout<<"Nhap vao bac cua da thuc thu hai: "; cin>>n;
	int b[n];
	cout<<"Nhap da thuc thu hai: "; 
	nhap(b,n);
	cout<<"In ra ket qua: ";
	tich(a,b,m,n);
}


