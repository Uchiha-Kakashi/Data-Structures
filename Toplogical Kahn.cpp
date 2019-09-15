//     THIS ALGORITHM WORKS ONLY FOR DIRECTED acyclic GRAPH

#include <bits/stdc++.h>

using namespace std;

class graph{
	public:
		int V;
		list <int> *adj;
		graph(int v)
		{
			this->V=v;
			adj = new list <int>[V];
		}
		void make_path(int a,int b)
		{
			adj[a].push_back(b);
		}
};

int main()
{
	map <int,int> m;
	queue <int> q;			    // THIS TAKES COUNTS OF THE IN DEGREE OF EACH VERTEX
	int n,p,i,j,k;
	cin >> n >> p;
	graph g(n);
	for(i=0;i<p;i++){
		cin >> j >> k;
		g.make_path(j,k);
		m[k]++;
	}
	for(i=0;i<n;i++){
		if(m[i]==0){
			q.push(i);
		}
	}
	k=0;
	while(k<n){
		j=q.front();
		for(auto h=g.adj[j].begin();h!=g.adj[j].end();h++){
			p=*h;
			m[p]--;
			if(m[p]==0){
				q.push(p);
			}
		}
		cout << j << " ";
		q.pop();
		k++;
	}
	return 0;
}
