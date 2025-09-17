#include <iostream>
#include <vector>
using namespace std;

int main() {
	freopen("berries.in", "r", stdin);

	int N, K;
	cin >> N >> K;
	vector<int> B(N);
	for (int i = 0; i < N; i++) { cin >> B[i]; }
	int m = 0;
	for (int s = 1;; s++) {
		int full = 0;
		for (int n : B) { full += n / s; }
		full = min(full, K);
		if (full < K / 2) { break; }
		if (full < K) {
			nth_element(B.begin(), B.begin() + min(N, K - full) - 1, B.end(),
			            [&](int a, int b) { return a % s > b % s; });
		}
		int bessie = (full - K / 2) * s;
		for (int i = 0; i < min(N, K - full); i++) { bessie += B[i] % s; }
		m = max(m, bessie);
	}

	freopen("berries.out", "w", stdout);
	cout << m << endl;
}