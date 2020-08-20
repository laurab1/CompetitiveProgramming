// { Driver Code Starts
// C++ program to find out whether a given graph is Bipartite or not.
// It works for disconnected graph also.
#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;
bool isBipartite(int G[][MAX],int V);

int main() {
    int t;
	cin>>t;
	int g[MAX][MAX];
	while(t--) {
		memset(g,0,sizeof (g));
		int n;
		cin>>n;
	
		for(int i=0;i<n;i++) {
			for(int j=0;j<n;j++) {
				cin>>g[i][j];
			}
		}
		
		cout<<isBipartite(g,n)<<endl;
	}
	return 0;
}
// } Driver Code Ends

bool dfs(int G[][MAX], int V, std::vector<int8_t> &colors, int i, int col) {
    colors.at(i) = col;

    for(int j = 0; j < V; j++)
        if(G[i][j] and (colors.at(j) == -1)) {
            if(!dfs(G, V, colors, j, !colors.at(i)))
                return false;
        }   
        else {
            if(G[i][j] and (colors.at(i) == colors.at(j)))
                return false;
        }

    return true;
}

bool isBipartite(int G[][MAX],int V) {
    std::vector<int8_t> colors(V, -1);

    for(int i = 0; i < V; i++)
        if(colors.at(i) == -1) {
            if(!dfs(G, V, colors, i, 0))
                return false;
        }

    return true;
}