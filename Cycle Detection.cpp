#include <bits/stdc++.h>

using namespace std;

int find(int a,int *A)
{
	int t;
	if(A[a]==a){
		return a;
	}
	return find(A[a],A);
}

int main()
{
	int n,m,j,i,c=0;
	int k,pj,pk;
	cin >> n >> m;
	int A[n];
	for(i=0;i<n;i++){
		A[i]=i;
	}
	for(i=0;i<m;i++){
		cin >> j >> k;
		pj=find(j,A);
		pk=find(k,A);
		if(pj!=pk){
			A[pj]=pk;
		}
		else{
			c=1;
		}
	}
	if(c==1){
		cout << "The cycle exist in the graph\n";
	}
	else{
		cout << "This is an acyclic graph\n";
	}
	return 0;
}
