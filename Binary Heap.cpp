/*	l-> Left child
	r-> Right child
	p-> Parent
	Index starts from 1
	Worked Perfectly for a small test case as
	n=5 and ratings as [1 4 0 2 3]
*/
#include <iostream>
#include <cstdlib>

using namespace std;

void swapnum(int *A,int *B,int c,int s)	// Swap function compares the rating and accordingly sort both the arrays
{
	int t;
	t=A[c];
	A[c]=A[s];
	A[s]=t;
	
	t=B[c];
	B[c]=B[s];
	B[s]=t;
}

void moveup(int *A,int *B,int n)	
{
	int p,t;					// p suggests the parent
	if(n>1){					// Takes care for the root element
		p=n/2;					// Parent element
		if(A[p]<A[n]){			
			swapnum(A,B,n,p);		
			moveup(A,B,p);		// Recursion for parent element
		}	
		else {
			return ;
		}
	}
	else {
		return ;
	}
}

void movedown(int *A,int *B,int p,int n)
{
	int l,r;
	l=2*p;						// Left child
	r=2*p+1;					// Right child
	if(l<=n && A[l]>A[p]){
		if(A[l]>A[r]){
			swapnum(A,B,l,p);
			movedown(A,B,l,n);
		}
		else {
			swapnum(A,B,r,p);
			movedown(A,B,r,n);
		}
	}
	else if(r<=n && A[r]>A[p]){
		swapnum(A,B,r,p);
		movedown(A,B,r,n);
	}
	else {
		return ;
	}
}

int Insert(int a,int *A,int *B,int n)
{
	int j;
	n++;					// Increment in ID
	A[n]=a;
	B[n]=n;
	moveup(A,B,n);			// Checking for the changes in heap after insertion
	for(j=1;j<=n;j++){						// Displaying the max heap
		cout << "(" << B[j] << "," << A[j] << ") ";
	}
	cout << "The photo of the week is :- " << B[1] << " with rating equal to :- " << A[1] << endl;			// Root element must be maximum
	return n;
}

void Upvote(int *A,int *B,int n,int id)
{
	int j,i;
	for(i=1;i<=n;i++){
		if(B[i]==id){
			A[i]++;
			break;
		}
	}
	moveup(A,B,i);
	for(j=1;j<=n;j++){										// Displaying the max heap
		cout << "(" << B[j] << "," << A[j] << ") ";
	}
	cout << "The photo of the week is :- " << B[1] << " with rating equal to :- " << A[1] << endl;
}

void Downvote(int *A,int *B,int n,int id)
{
	int i,j;
	for(i=1;i<=n;i++){
		if(B[i]==id){
			A[i]--;
			break;
		}
	}
	movedown(A,B,i,n);
	for(j=1;j<=n;j++){										// Displaying the max heap
		cout << "(" << B[j] << "," << A[j] << ")";
	}
	cout << "The photo of the week is :- " << B[1] << " with rating equal to :- " << A[1] << endl;
}

int Delete(int *A,int *B,int n,int id)
{
	int t,j,i;
	for(i=1;i<=n;i++){
		if(B[i]==id){
			swapnum(A,B,i,n);			
			n--;
			break;
		}
	}
	movedown(A,B,i,n);
	for(j=1;j<=n;j++){									// Displaying the max heap
		cout << "(" << B[j] << "," << A[j] << ") ";
	}
	cout << "The photo of the week is :- " << B[1] << " with rating equal to :- " << A[1] << endl;
	return n;
}

void maxheap(int *A,int *B,int i,int n)
{
	int l,r;
	l=2*i;
	r=2*i+1;
	if(r<=n && A[r]>A[i]){
		if(A[r]<A[l]){
			swapnum(A,B,i,l);
			maxheap(A,B,l,n);
		}
		else {
			swapnum(A,B,i,r);
			maxheap(A,B,r,n);
		}
	}
	else if(l<=n && A[l]>A[i]){
		swapnum(A,B,i,l);
		maxheap(A,B,l,n);			
	}
	else {
		return ;
	}
}

int main() 
{
	int A[100];
	int B[100];
	int n,i,j,ip;
	int ir,id;
	cout << "Enter the numbers of photos less than or equal to 100\n";
	cin >> n;
	cout << "Enter the Ratings of the photos\n";
	for(i=1;i<=n;i++){
		cin >> A[i];
	}
	for(j=1;j<=n;j++){						// ID's will be stored in array B equls to the index
		B[j]=j;
	}
	for(i=n/2;i>0;i--){						// Building the array in a maximum heap beginning with index (n/2) to 1
		maxheap(A,B,i,n);
	}
	for(j=1;j<=n;j++){						// Displaying the max heap
		cout << A[j] << " ";
	}
	
	cout << endl;
	
	for(j=1;j<=n;j++){						// Displaying the ID's sorted according to their ratings
		cout << B[j] << " ";
	}
	while(ip!=5){
		cout << "\n\nWhat do you want to do with the heap\n";
		cout << "1.Insert\n2.Upvote\n3.Downvote\n4.Delete\n5.Quit\n";
		cin >> ip;
		switch(ip){
			case 1:
				cout << "Enter the initial rating of the ID\n";
				cin >> ir;
				n=Insert(ir,A,B,n);
				break;
			case 2:
				cout << "Enter the ID of the photo to increment rating by 1\n";
				cin >> id;
				Upvote(A,B,n,id);
				break;
			case 3:
				cout << "Enter the ID of the photo to decrement rating by 1\n";
				cin >> id;
				Downvote(A,B,n,id);
				break;
			case 4:
				cout << "Enter the ID of the photo to delete from heap\n";
				cin >> id;
				n=Delete(A,B,n,id);
				break;
		}
	}
	return 0;
}
