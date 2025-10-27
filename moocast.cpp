#include <bits/stdc++.h>
using namespace std;

vector<vector<bool>> connected;
vector<bool> visited;

/** @return how many cows can be reached from a cow c */
int reachable_cows(int c) {
	visited[c] = true;
	// we can always reach the initial cow c
	int reached = 1;
	for (int nc = 0; nc < connected.size(); nc++) {
		// make sure we can connect to this cow & it hasn't been reached yet
		if (!visited[nc] && connected[c][nc]) {
			visited[nc] = true;
			reached += reachable_cows(nc);
		}
	}
	return reached;
}

int main() {
	freopen("moocast.in", "r", stdin);
	int cow_num;
	cin >> cow_num;
	vector<int> x(cow_num), y(cow_num);
	vector<int> power(cow_num);
	for (int c = 0; c < cow_num; c++) { cin >> x[c] >> y[c] >> power[c]; }

	connected = vector<vector<bool>>(cow_num, vector<bool>(cow_num));
	for (int i = 0; i < cow_num; i++) {
		for (int j = 0; j < cow_num; j++) {
			int dist_squared =
			    ((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
			connected[i][j] = dist_squared <= power[i] * power[i];
		}
	}

	int max_cows = 0;
	for (int c = 0; c < cow_num; c++) {
		visited.assign(cow_num, false);
		max_cows = max(max_cows, reachable_cows(c));
	}

	freopen("moocast.out", "w", stdout);
	cout << max_cows << endl;
}