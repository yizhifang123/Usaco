#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
	int test_num;
	cin >> test_num;
	for (int t = 0; t < test_num; t++) {
		int n, m;
		cin >> n >> m;

		vector<vector<int>> adj(n);
		for (int i = 0; i < m; i++) {
			int u, v;
			cin >> u >> v;
			adj[--u].push_back(--v);
			adj[v].push_back(u);
		}

		// vis[i] stores the component label for node i
		vector<int> vis(n, -1);
		int num_components = 0;

		// Identify connected components using DFS
		for (int i = 0; i < n; i++) {
			if (vis[i] != -1) { continue; }
			// DFS using a stack
			stack<int> s;
			s.push(i);
			while (!s.empty()) {
				int u = s.top();
				s.pop();
				if (vis[u] != -1) { continue; }
				vis[u] = num_components;
				for (ll v : adj[u]) {
					if (vis[v] == -1) { s.push(v); }
				}
			}
			num_components++;
		}

		// components[i] stores all nodes with component label i
		vector<vector<int>> components(num_components);
		for (int i = 0; i < n; i++) { components[vis[i]].push_back(i); }

		// Components containing the start (0) and end (n-1) barns
		vector<int> start_component = components[vis[0]];
		vector<int> end_component = components[vis[n - 1]];

		// Initialize distance vectors with infinity
		vector<int> dist1(num_components, INT_MAX);
		vector<int> dist2(num_components, INT_MAX);

		// Calculate minimum distances to start_component
		int a = 0;
		for (int i = 0; i < n; i++) {
			int dist = abs(start_component[a] - i);
			while (a < start_component.size() - 1 &&
			       abs(start_component[a + 1] - i) < dist) {
				a++;
			}
			dist1[vis[i]] = min(dist1[vis[i]], dist);
		}

		// Calculate minimum distances to end_component
		int b = 0;
		for (int i = 0; i < n; i++) {
			int dist = abs(end_component[b] - i);
			while (b < end_component.size() - 1 &&
			       abs(end_component[b + 1] - i) < dist) {
				b++;
			}
			dist2[vis[i]] = min(dist2[vis[i]], dist);
		}

		// Compute the result by finding the minimum sum of squared distances
		ll res = LLONG_MAX;
		for (int i = 0; i < num_components; i++) {
			res = min(res, 1LL * dist1[i] * dist1[i] + 1LL * dist2[i] * dist2[i]);
		}
		cout << res << '\n';
	}
}