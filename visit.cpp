#include <bits/stdc++.h>
using namespace std;

// cow i wants to visit cow a[i] and gets v[i] points
vector<int> a, v;
// reversed_graph[i] stores the cows that want to go to farm i
vector<vector<int>> reversed_graph;
// marks cows as visited once we have processed them
vector<bool> visited;

/**
 * Marks y and the other cows in its other cycle as visited by performing a dfs.
 */
void mark(int y) {
	if (visited[y]) { return; }
	visited[y] = true;
	for (int c : reversed_graph[y]) { mark(c); }
}

/**
 * Applies Floyd's algorithm to detect the cycle and return the minimum v value
 * in this cycle.
 */
int min_in_cycle(int curr) {
	int y = a[curr];
	int z = a[y];
	while (y != z) {
		y = a[y];
		z = a[a[z]];
	}
	// y is now an element that is in the cycle
	int min_v = v[y];
	y = a[y];

	// traverse the cycle to find the cow with the minimum v_i value
	while (y != z) {
		min_v = min(min_v, v[y]);
		y = a[y];
	}
	// mark every node in this connected component as visited
	mark(y);
	return min_v;
}

int main() {
	int n;
	cin >> n;
	v.resize(n);
	a.resize(n);
	visited.resize(n);
	reversed_graph.resize(n);

	long long max_moos = 0;
	for (int i = 0; i < n; i++) {
		cin >> a[i] >> v[i];
		a[i]--;
		// cow i wants to visit farm a[i]
		reversed_graph[a[i]].push_back(i);
		max_moos += v[i];
	}

	for (int i = 0; i < n; i++) {
		/*
		 * For each unvisited connected component with exactly one cycle, you
		 * can visit all except one cow. We make this cow the one with the
		 * lowest v_i and subtract it.
		 */
		if (!visited[i]) { max_moos -= min_in_cycle(i); }
	}

	cout << max_moos << endl;
}