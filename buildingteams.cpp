#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    if (!(cin >> n >> m)) return 0;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    vector<int> color(n + 1, 0); // 0 = unvisited, 1 or 2 = team
    queue<int> q;
    
    for (int start = 1; start <= n; ++start) {
        if (color[start] != 0) continue;
        // start BFS from this node
        color[start] = 1;
        q.push(start);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int u : adj[v]) {
                if (color[u] == 0) {
                    color[u] = 3 - color[v]; // flip 1 <-> 2
                    q.push(u);
                } else if (color[u] == color[v]) {
                    cout << "IMPOSSIBLE\n";
                    return 0;
                }
            }
        }
    }
    
    // Output colors for nodes 1..n
    for (int i = 1; i <= n; ++i) {
        if (i > 1) cout << ' ';
        cout << color[i];
    }
    cout << '\n';
    return 0;
}
