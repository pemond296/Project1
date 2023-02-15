#include<bits/stdc++.h>

using namespace std;

nhap(int *a,int m){
	for(int i=m;i>=0;i--)
	cin>>a[i];
}

void Hornermethod(int a[], int m, int x){
	int b[10];
	for(int i=0; i<=m;i++) b[i]=0;
	for(int i=m;i>=0;i--){
		if(i==m) b[i]=a[i];
		b[i] = x*b[i+1]+a[i];
	}
	cout<<"Gia tri cua da thuc tai "<<x<<" la: "<<b[0];
}

int main(){
	int n;
	cout<<"Nhap vao bac cua da thuc: "; cin>>n;
	int a[n];
	cout<<"Nhap da thuc voi bac giam dan: ";
	nhap(a,n);
	int x;
	cout<<"Nhap vao gia tri cua x: ";
	cin>>x;
	Hornermethod(a,n,x);
	return 0;
}

