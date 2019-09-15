#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{
    int n,m,t,u;
    int v,j,i,s,k;
    cin >> t;
    for(i=0;i<t;i++){
        cin >> n >> m;
        int A[n][n];
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                A[j][k]=0;
            }
        }
        A[0][n-1]=0;
        for(j=0;j<m;j++){
            cin >> u >> v;
            A[u-1][v-1]=6;
            A[v-1][u-1]=6;
        }
        
        cin >> s;
        s--;
        
        for(j=0;j<n;j++){
            if(j!=s && A[s][j]!=0){
                cout << A[s][j] << " ";
            }
            else if(A[s][j]==0 && j!=s){
                for(k=0;k<n;k++){
                        A[s][j]+=A[k][j];
                }
                if(A[s][j]==0){
                    cout << "-1" << " ";
                }
                else{
                    cout << A[s][j] << " ";
                }
            }
        }
        cout << endl;
    }
    return 0;
}
