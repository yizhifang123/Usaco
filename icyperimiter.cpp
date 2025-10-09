#include <vector>
#include <iostream>

using namespace std;

// Movement directions (up, down, left, right)
vector<pair<int, int>> DIRECTIONS = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

pair<int, int> bfs(int row, int col, const vector<vector<char>> &grid,
                   vector<vector<bool>> &visited) {
	int n = grid.size();  // shorthand

	queue<pair<int, int>> q;
	q.push({row, col});  // Start BFS from the given cell (row, col)

	int area = 0;
	int perimeter = 0;
	while (!q.empty()) {
		auto [row, col] = q.front();  // Current cell (row, col)
		q.pop();

		// Skip if the cell has already been visited
		if (visited[row][col]) { continue; }

		visited[row][col] = true;  // Mark the cell (row, col) as visited
		area++;  // Increment area (each '#' contributes 1 to the area)

		// Each cell starts with 4 sides contributing to the perimeter
		int sides = 4;
		for (auto [dx, dy] : DIRECTIONS) {
			int next_row = row + dx;
			int next_col = col + dy;

			// Check if the neighboring cell is within the grid
			if (next_row >= 0 && next_row < n && next_col >= 0 && next_col < n) {
				// If the neighbor (next_row, next_col) is part of the same blob
				if (grid[next_row][next_col] == '#') {
					// Add the neighbor (next_row, next_col) to the queue
					q.push({next_row, next_col});
					sides--;  // Shared edges reduce the perimeter contribution
				}
			}
		}

		perimeter += sides;  // Add remaining sides to the perimeter
	}

	return {area, perimeter};
}

int main() {
	freopen("perimeter.in", "r", stdin);
	freopen("perimeter.out", "w", stdout);

	int n;
	cin >> n;

	vector<vector<char>> grid(n, vector<char>(n));
	vector<vector<bool>> visited(n, vector<bool>(n, false));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) { cin >> grid[i][j]; }
	}

	int max_area = 0;
	int min_perimeter = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] != '#' || visited[i][j]) { continue; }

			const auto [area, perimeter] = bfs(i, j, grid, visited);

			// Update max_area and min_perimeter based on the BFS results
			if (area > max_area || (area == max_area && perimeter < min_perimeter)) {
				max_area = area;
				min_perimeter = perimeter;
			}
		}
	}

	cout << max_area << " " << min_perimeter << endl;
}