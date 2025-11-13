#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int &a : v) { cin >> a; }

	long long ans = -accumulate(v.begin(), v.end(), 0LL);

	// For every bit position,
	// check if it's set on in the xor-sum of every subsequence
	for (int i = 0; i < 30; i++) {
		int s = 0;
		// Count the prefix sums
		// The # of 0 xor-sum prefxises starts from 1 to count the prefixes with
		// xor-sum 1
		vector<int> pref = {1, 0};
		for (int a : v) {
			s ^= (a >> i) & 1;
			/*
			 * Count the # of sequences ending at this position with xor-sum
			 * non-zero by counting the prefixes of the inversed bit, i.e.
			 * pref[i] ^ pref[j] = 1. Update the answer by adding the # of such
			 * sequences multiplied by the respective power of two.
			 */
			ans += pref[s ^ 1] * 1LL << i;
			// Update the prexies
			pref[s]++;
		}
	}

	cout << ans << endl;
}