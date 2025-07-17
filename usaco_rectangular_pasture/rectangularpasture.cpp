#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

int main() {
	int cow_num;
	cin >> cow_num;


	vector<pair<int, int>> cows(cow_num);
	for (pair<int, int> &c : cows) {
		cin >> c.first >> c.second;
	}
	
	// we do a little coordinate compression
	sort(cows.begin(), cows.end());  // sort by x
	
	// compress the coordinates
	vector<int> xs, ys;
	for (auto &c : cows) {
		xs.push_back(c.first);
		ys.push_back(c.second);
	}
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());

	for (auto &c : cows) {
		c.first = lower_bound(xs.begin(), xs.end(), c.first) - xs.begin();
		c.second = lower_bound(ys.begin(), ys.end(), c.second) - ys.begin();
	}


	// Create a vector of cow points sorted by y
	vector<pair<int, int>> cows_by_y = cows;
	sort(cows_by_y.begin(), cows_by_y.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		return a.second < b.second;
	});

	// Print the compressed coordinate grid as a 2D grid
	// vector<vector<char>> grid(xs.size(), vector<char>(ys.size(), '.'));
	// for (int i = 0; i < cow_num; ++i) {
	// 	grid[cows[i].first][cows[i].second] = 'C';
	// }
	// cout << "Compressed coordinate grid (2D representation):" << endl;
	// for (int y = ys.size() - 1; y >= 0; --y) {
	// 	for (int x = 0; x < xs.size(); ++x) {
	// 		cout << grid[x][y] << " ";
	// 	}
	// 	cout << endl;
	// }


	// Build prefix sums for 'above' (above) and 'below' (below) for each cow
	int N = cow_num;
	vector<vector<int>> above(N, vector<int>(N+1, 0)); // above[v][i+1]: # cows in [0,i] with y > y_v
	vector<vector<int>> below(N, vector<int>(N+1, 0)); // below[v][i+1]: # cows in [0,i] with y < y_v

	for (int v = 0; v < N; v++) {
		for (int i = 0; i < N; i++) {
			above[v][i+1] = above[v][i] + (cows[i].second > cows[v].second ? 1 : 0);
			below[v][i+1] = below[v][i] + (cows[i].second < cows[v].second ? 1 : 0);
		}
	}


	long long total_rectangles = 0;

	for (int i = 0; i < cow_num; i++) {
		for(int j = i+1; j < cow_num; j++) {
			int a, b;
			if (cows[i].second < cows[j].second) {
				a = above[j][j+1] - above[j][i+1];
				b = below[i][j+1] - below[i][i+1];
			} else {
				a = above[i][j+1] - above[i][i+1];
				b = below[j][j+1] - below[j][i+1];
			}
			total_rectangles += (a+1)*(b+1);
		}
	}





	cout << total_rectangles + 1 + cow_num << endl;



}	