#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll solve(ll a, ll b) {
	if (a == b) {
		return 0;
	} else if (a > b) {
		/*
		 * Divide a greedily until a <= b, add 1 in case a is odd to enable
		 * division.
		 */
		ll is_odd = a % 2;
		return 1 + is_odd + solve((a + is_odd) / 2, b);
	} else {
		/*
		 * Otherwise, work on b to reach a by division. Alternatively,
		 * if it's better, perform subtraction until a is reached.
		 */
		ll is_odd = b % 2;
		return min(b - a, 1 + is_odd + solve(a, b / 2));
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		ll a, b;
		cin >> a >> b;
		cout << solve(a, b) << endl;
	}
}