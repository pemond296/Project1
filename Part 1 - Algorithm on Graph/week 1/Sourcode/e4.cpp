#include<bits/stdc++.h>

using namespace std;

int minstep(string word1, string word2){
	int m=word1.size();
	int n=word2.size();
	int a[10][10];
	a[0][0]=0;
	for(int i=1;i<=m;i++)
	a[i][0]=i;
	for(int j=1;j<=n;j++)
	a[0][j]=j;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(word1[i-1] == word2[j-1])
			a[i][j]=a[i-1][j-1];
			else 
			a[i][j]=min(a[i-1][j],min(a[i][j-1],a[i-1][j-1]))+1;
		}
	}
	return a[m][n];
}

int main(){
	string word1,word2;
	cin>>word1>>word2;
	cout<<minstep(word1,word2);
}
