#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> diamonds(N);
    for (int i = 0; i < N; ++i) cin >> diamonds[i];
    sort(diamonds.begin(), diamonds.end());

    // max_in_window[i]: max number of diamonds in a window ending at i
    vector<int> max_in_window(N, 1);
    int l = 0;
    for (int r = 0; r < N; ++r) {
        while (diamonds[r] - diamonds[l] > K) ++l;
        max_in_window[r] = r - l + 1;
    }

    // prefix_max[i]: max window size in [0, i]
    vector<int> prefix_max(N);
    prefix_max[0] = max_in_window[0];
    for (int i = 1; i < N; ++i)
        prefix_max[i] = max(prefix_max[i-1], max_in_window[i]);

    // suffix_max[i]: max window size in [i, N-1]
    vector<int> suffix_max(N);
    suffix_max[N-1] = max_in_window[N-1];
    for (int i = N-2; i >= 0; --i)
        suffix_max[i] = max(suffix_max[i+1], max_in_window[i]);

    int ans = 0;
    for (int i = 0; i < N-1; ++i) {
        ans = max(ans, prefix_max[i] + suffix_max[i+1]);
    }
    ans = max(ans, prefix_max[N-1]); // In case we only use one case
    cout << ans << endl;
    return 0;
}
