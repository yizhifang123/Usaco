#include <iostream>
#include <vector>

using namespace std;
#define trav(a, x) for(auto& a : x)
#define fo(i, k, n) for(int i = k; i < n; ++i)
typedef long long ll;


ll component = 0;
bool impossible = false; 
vector<pair<int, char>> adj[100001];
bool visited[100001];
bool color[100001];

void dfs(int u, bool g){
    
    visited[u] = true;
    color[u] = g;
    
    trav(v, adj[u]){
        
        if(visited[v.first]){
            if(v.second == 'S' && color[v.first] != g) impossible = true;
            if(v.second == 'D' && color[v.first] == g) impossible = true; 
        }

        if(!visited[v.first]){
            if(v.second == 'S') dfs(v.first, g);
            else dfs(v.first, !g);
        }
    
    }
}

int main()
{	
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; ++i){
        char a;
        int b, c;
        cin >> a >> b >> c;
        adj[b].push_back({c, a});
        adj[c].push_back({b, a});
    }

    for(int i = 1; i <= n; ++i){
        if(!visited[i]){
            component++;
            dfs(i, 0);
        }
        if(impossible) break;
    }

    if(impossible) cout << 0 << endl;
    else{
        cout << 1;
        while(component--){
            cout << 0;
        }
    }

    return 0;
}