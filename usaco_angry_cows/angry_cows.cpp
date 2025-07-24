#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

bool canDetonateAll(const vector<int>& pos, double R) {
    for(int i = 0; i < pos.size(); i++) {
        

}
int main() {
    int N;
    cin >> N;
    vector<int> pos(N);
    for (int i = 0; i < N; ++i) cin >> pos[i];
    sort(pos.begin(), pos.end());

    // TODO: Implement binary search on R and simulation
    
    // Example output (replace with actual answer)

    while (right - left > 0.05) { // 0.05 ensures correct rounding to 1 decimal
        double mid = left + (right-left)/ 2.0;
        if (canDetonateAll(pos, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }

    cout << fixed << setprecision(1) << 3.0 << endl;
    return 0;
}
