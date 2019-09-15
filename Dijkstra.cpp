#include <bits/stdc++.h>

using namespace std;

# define INF 0x3f3f3f3f


class graph{
    public:
        int V;
        list <pair <int,int> > *adj;
        
        graph(int v)
        {
            this->V=v;
            adj = new list <pair <int,int> >[v];
        }
        void make_path(int a,int b,int d)
        {
            adj[a].push_back(make_pair(b,d));
            adj[b].push_back(make_pair(a,d));
        }
};  

class compare{
    public:
        int operator()(const pair <int,int> &a,const pair <int,int> &b){
            return a.second > b.second;
        }
};

int main()
{
    priority_queue <pair <int,int>, vector <pair <int,int>>,compare> pq;					
    pair <int,int> p;
    int n,i,r,j,k,s,d;
    cin >> n >> r;
    map <int,int> m;                       // MAP V=0/1 0 IF NOT FINALISED & 1 IF DID
    vector <int> dist(n,INF);					// FINAL ANSWER VECTOR
    graph g(n);
    for(i=0;i<r;i++){
        cin >> j >> k >> d;				// THE NUMBERS BE 0 BASED INDEX
        j-=1;
        k-=1;
        g.make_path(j,k,d);
    }
    cin >> s;
    s-=1;
    k=0;
	dist[s]=0;
	pq.push(make_pair(s,0));
    while(!pq.empty() && k<=n){
        p=pq.top();
        j=p.first;
        while(m[j]!=0){
            pq.pop();
            p=pq.top();
            j=p.first;
        }
        j=p.first;
        dist[j]=p.second;
        m[j]=1;
        pq.pop();
        k++;
        s=p.first;
        for(auto h=g.adj[s].begin();h!=g.adj[s].end();h++){
            p=*h;
            d=p.first;
            if(m[d]==0 && dist[d]>p.second+dist[s]){
                dist[d]=p.second+dist[s];
                pq.push(make_pair(d,dist[d]));
            }
        }
    }
    for(i=0;i<n;i++){
        if(dist[i]==INF){
            cout << -1 << " ";
        }
        else if(dist[i]==0){
            continue;
        }
        else{
            cout << dist[i] << " ";
        }
    }
    return 0;
}
