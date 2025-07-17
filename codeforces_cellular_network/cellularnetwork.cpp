#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool can_cover(const vector<int>& cities, const vector<int>& towers, int r) {
    int n = cities.size(), m = towers.size();
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j + 1 < m && abs(towers[j+1] - cities[i]) <= abs(towers[j] - cities[i])) ++j;
        if (abs(towers[j] - cities[i]) > r) return false;
    }
    return true;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> cities(n), towers(m);
    for (int i = 0; i < n; ++i) cin >> cities[i];
    for (int i = 0; i < m; ++i) cin >> towers[i];
    sort(cities.begin(), cities.end());
    sort(towers.begin(), towers.end());
    int lo = 0, hi = 2e9, ans = 0;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (can_cover(cities, towers, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    cout << ans << endl;
    return 0;
}
