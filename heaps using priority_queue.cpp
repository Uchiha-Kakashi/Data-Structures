#include <bits/stdc++.h>

using namespace std;

class compare{
    public:
        int operator()(const pair <int,int> &a,const pair <int,int> &b){
            return a.second < b.second;		// *** Less menans MAX-HEAP && Greater means MIN-HEAP
        }
};

int main()
{
    priority_queue <pair <int,int>, vector <pair <int,int> >,compare> q;
    pair <int,int> p;
    q.push(make_pair(5,3));
    q.push(make_pair(6,3));
    q.push(make_pair(2,4));
    while(!q.empty()){
        p=q.top();
        cout << p.first << " " << p.second << endl;
        q.pop();
    }
    return 0;
}
