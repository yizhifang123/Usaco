#include <cstdint>
#include <iostream>

using namespace std;

int main() {
	int test_num;
	std::cin >> test_num;
	for (int t = 0; t < test_num; t++) {
		int hot;
		int cold;
		int target;
		std::cin >> hot >> cold >> target;

		if (target * 2 <= hot + cold) {
			cout << 2 << '\n';
			continue;
		}

		long long lo = 0;
		long long hi = INT32_MAX;
		long long valid = -1;
		while (lo <= hi) {
			long long n = (lo + hi) / 2;
			long long num = (n + 1) * hot + n * cold;
			long long denom = 2 * n + 1;
			if (num >= denom * target) {
				valid = n;
				lo = n + 1;
			} else {
				hi = n - 1;
			}
		}

		long long err1_num =
		    hot * (valid + 1) + cold * valid - target * (2 * valid + 1);
		long long err1_denom = 2 * valid + 1;

		long long err2_num =
		    target * (2 * valid + 3) - hot * (valid + 2) - cold * (valid + 1);
		long long err2_denom = 2 * valid + 3;

		if (err1_num * err2_denom <= err2_num * err1_denom) {
			cout << 2 * valid + 1 << '\n';
		} else {
			cout << 2 * valid + 3 << '\n';
		}
	}
}