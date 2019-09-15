#include <bits/stdc++.h>

using namespace std;

class graph{
    public:
        int V;
        list <int> *adj;
        graph(int v)
        {
            this->V=v;
            adj = new list<int>[v];
        }
        void make_path(int a,int b)
        {
            adj[a].push_back(b);
        }
};

map <int,int> rem;				// TAKES COUNT OF VISITED NODES
stack <int> topsort;				// STORES ELEMENTS IN TOPOLOGICALLY SORTED ORDER

void topological(int n,graph g,int l)
{
    int vis=0,i,j; 
    if(rem[l]==1){
    	return ;
	}
	rem[l]=1;
	for(auto h=g.adj[l].begin();h!=g.adj[l].end();h++){
		topological(n,g,*h);
	}
	topsort.push(l);
    return ;
}

int main()
{
    int n,m,i,j,k,l;
    cin >> n >> m;
    graph g(n);
    for(i=0;i<m;i++){
        cin >> j >> k;
        g.make_path(j,k);
    } 
    i=0;
    while(i<n){
    	if(rem[i]==0){
    		topological(n,g,i);
		}
		i++;
	}
	while(!topsort.empty()){
		cout << topsort.top() << " ";
		topsort.pop();
	}
    return 0;
}
