/*	THE CODE IS ABOUT GRAPH AND PERFORMS THE FOLLOWING TASKS
	1:- BFS TRAVERSAL  2:- DFS TRAVERSAL  3:- DETECTION AND NUMBER OF CYCLES 
	4:- CHECK IF TWO NODES ARE IN SAME PATH  5:- CALCULATE DIJKSTRA DISTANCES
	THE CODE DOES NOT RUN HERE BUT RUNS PERFECTLY ON ideone.com
*/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <queue>

using namespace std;

const int N=100;
int f=0;
int D[N]={1000};
int c=0;

typedef struct graph{
	int I=0;
	int num;
	int dist[N];
	bool v=false;
	graph *ptr[N];
}graph;

graph* createnode(int a)
{
	graph *t;
	t=(graph *)malloc(sizeof(graph));
	t->num=a;
	return t;
}

void createpaths(graph *h1,graph *h2,int d)
{
	int k;
	k=h1->I;
	h1->ptr[k]=h2;
	h1->dist[k]=d;
	h1->I=(h1->I)+1;
}

void dijkstra(graph *head,int m)
{
	graph *t;
	int i,n;
	for(i=0;i<head->I;i++){
		t=head->ptr[i];
		n=t->num;
		D[n]=min(D[n],m+head->dist[i]);
		dijkstra(t,m+D[n]);
	}
	return ;
}

int Twonodes(graph *head,int a,int b)
{
	static graph *h=head;
	graph *t;
	static int s=0;
	int i;
	if(head->num==a){
		f=1;
	}
	if(f==1 && head->num==b){
		return 1;
	}
	if(head->I==0 && a!=h->num){
		f=0;
		return 0;
	}
	for(i=0;i<head->I;i++){
		t=head->ptr[i];
		s += Twonodes(t,a,b);
	}
	return s;
}

void BFST(graph *head)
{
	graph *t;
	graph *p;
	int i,k;
	cout << head->num << " ";
	head->v=true;
	queue <graph *> q;
	for(i=0;i<head->I;i++){
		q.push(head->ptr[i]);
	}
	i=head->I;
	while(!q.empty()){
		t=q.front();
		if(t->v==false){
			cout << t->num << " ";
		}
		t->v=true;
		for(k=0;k<t->I;k++){
			p=t->ptr[k];
			if(p->v==false){
				q.push(p);
			}
			else{
				c++;
			}
		}
		q.pop();
	}
}

void DFST(graph *head)
{
	graph *t;
	int i;
	if(head==NULL || head->v==true){
		if(head->v==true){
			c++;
		}
		return ;
	}
	cout << head->num << " ";
	head->v=true;
	for(i=0;i<head->I;i++){
		t=head->ptr[i];
		DFST(t);
	}
	return ;
}

int main()
{
	int n,i,u,v,m;
	int a,b,s,d;
	cin >> n >> m;
	graph *h;
	graph *P[n];												// Creating array of pointers of graph structure
	
	for(i=0;i<n;i++){
		P[i]=createnode(i);										// Creating Nodes of every number assuming them to be 0 to n-1 
	}
	
	for(i=0;i<m;i++){
		cin >> u >> v >> d;
		createpaths(P[u],P[v],d);
	}

	cin >> s;
	graph *head=P[s];
	// DEPTH FIRST TRAVERSAL
	cout << "The DFS Travrsal is given by\n";
	DFST(head);
	cout << endl;
	
	for(i=0;i<n;i++){											// Initializes the visiting booleans to false for BFS
		h=P[i];
		h->v=false;
	}
	
	// BREADTH FIRST TRAVERSAL 
	cout << "The BFS Traversal is given by\n";
	BFST(head);
	cout << endl;
	
	// DETECTION AND NUMBER OF CYCLES IN GRAPH ACCORDING TO DFS
	if(c>=1){
		cout << "\nThe cycle exists\n";
		cout << "Number of cycles is " << c << endl;
	}
	else{
		cout << "No cycle exists in the graph\n";
	}
	
	
	// CHECK IF TWO NODES ARE IN SAME PATH
	cout << "Enter the two numbers to check path\n";
	cin >> a >> b;
	if(Twonodes(head,a,b)>0){
		cout << "The two numbers lie in same path\n";
	}
	else{
		cout << "The two nodes lie in different paths\n";
	}
	
	// CALCULATION OF DISTANCE OF EACH NODE FROM HEAD (DIJKSTRA)
	for(i=0;i<n;i++){
		D[i]=1000;
	}
	dijkstra(head,0);
	d=head->num;
	cout << "\n\nDijkstra Distances \n";
	for(i=0;i<n;i++){
		if(i==d){
			continue;
		}
		else if(D[i]==1000){
			cout << -1 << " ";
		}
		else{
			cout << D[i] << " ";
		}
	}
	return 0;
}
