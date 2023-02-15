#include<bits/stdc++.h>

using namespace std;

void nhap(int a[],int n){
	for(int i=0;i<n;i++)
		cin>>a[i];
}

void xuat(int a[], int n){
	for(int i=0;i<n;i++)
	cout<<a[i]<<" ";
}

void twoway(int a[], int first, int last)
{ 
   int i=first-1, j=last; int pivot=a[last];
   if (last <= first) return;
   for (;;)
   {
      while (a[++i] < pivot);
      while (pivot < a[--j]) if (j == first) break;
      if (i >= j) break;
      swap(a[i], a[j]);
   }
   swap(a[i], a[last]);
   twoway(a, first, i-1);
   twoway(a, i+1, last);
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void partition(int a[], int first, int last, int& i, int& j)
{
    if (last - first <= 1) {
        if (a[last] < a[first])
            swap(&a[last], &a[first]);
        i = first;
        j = last;
        return;
    }
 
    int mid = first;
    int pivot = a[last];
    while (mid <= last) {
        if (a[mid] < pivot)
            swap(&a[first++], &a[mid++]);
        else if (a[mid] == pivot)
            mid++;
        else if (a[mid] > pivot)
            swap(&a[mid], &a[last--]);
    }
 
    i = first - 1;
    j = mid;
}

void threeway(int a[],int first,int last){
	if(last<=first) return;
	int i,j;
	partition(a,first,last,i,j);
	threeway(a,first,i);
	threeway(a,j,last);
}

int *a= new int[10000000];
int main(){	
//	int *a= new int[10000000];	
	int n,m; 
	cin>>n;
	clock_t start,end;
	double time_use;
	cout<<"Bam phim 2 de su dung 2-way partitioning quicksort"<<endl;
	cout<<"Bam phim 3 de su dung 3-way partitioning quicksort"<<endl;
	cin>>m;
	freopen("10^4 e1.inp","r",stdin);
//	freopen("10^5 e1.inp","r",stdin);
//	freopen("10^6 e1.inp","r",stdin);
//	freopen("10^7 e1.inp","r",stdin);
	nhap(a,n);
	if(m==2){
	start=clock();
	twoway(a,0,n-1);
//	xuat(a,n);
	end=clock();
	time_use = (double)(end-start)/CLOCKS_PER_SEC;
	cout<<endl<<time_use;
	}
	if(m==3){
	start=clock();
	threeway(a,0,n-1);
//	xuat(a,n);
	end=clock();
	time_use = (double)(end-start)/CLOCKS_PER_SEC;
	cout<<endl<<time_use;
	}
	delete (a);
	return 0;
}
