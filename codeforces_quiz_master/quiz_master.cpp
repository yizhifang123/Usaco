#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>
using namespace std;

// Helper to get all divisors of x up to m
vector<int> get_divisors(int x, int m) {
    vector<int> divs;
    for (int d = 1; d * d <= x && d <= m; ++d) {
        if (x % d == 0) {
            divs.push_back(d);
            if (x / d != d && x / d <= m) divs.push_back(x / d);
        }
    }
    return divs;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        
        // For each topic, check if there is at least one student proficient
        vector<bool> topic_possible(m + 1, false);
        for (int i = 0; i < n; ++i) {
            vector<int> divs = get_divisors(a[i], m);
            for (int d : divs) topic_possible[d] = true;
        }
        bool all_possible = true;
        for (int T = 1; T <= m; ++T) {
            if (!topic_possible[T]) {
                all_possible = false;
                break;
            }
        }
        if (!all_possible) {
            cout << -1 << '\n';
            continue;
        }
        
        // Sort smartness values
        sort(a.begin(), a.end());
        int ans = 1e9 + 5;
        unordered_map<int, int> topic_count;
        int covered = 0;
        int l = 0;
        for (int r = 0; r < n; ++r) {
            vector<int> divs = get_divisors(a[r], m);
            for (int d : divs) {
                if (++topic_count[d] == 1) ++covered;
            }
            while (covered == m) {
                ans = min(ans, a[r] - a[l]);
                vector<int> divs_l = get_divisors(a[l], m);
                for (int d : divs_l) {
                    if (--topic_count[d] == 0) --covered;
                }
                ++l;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

/*
Sample Input:
3
2 4
3 7
4 2
3 7 2 9
5 7
6 4 3 5 7

Expected Output:
-1
0
3
*/
