#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

bool canAssign(const vector<int>& arrival, int M, int C, int maxWait) {
    int buses = 1;
    int firstCow = 0;
    int n = arrival.size();
    for (int i = 1; i < n; ++i) {
        // If this cow can't fit in the current bus
        if (i - firstCow >= C || arrival[i] - arrival[firstCow] > maxWait) {
            buses++;
            firstCow = i;
        }
    }
    return buses <= M;
}

int main() {
    ifstream fin("convention.in");
    ofstream fout("convention.out");
    int N, M, C;
    fin >> N >> M >> C;
    vector<int> arrival(N);
    for (int i = 0; i < N; ++i) fin >> arrival[i];
    sort(arrival.begin(), arrival.end());
    int left = 0, right = arrival[N-1] - arrival[0];
    int ans = right;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canAssign(arrival, M, C, mid)) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    fout << ans << endl;
    fin.close();
    fout.close();
    return 0;
}
