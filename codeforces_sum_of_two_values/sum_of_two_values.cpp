#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
        a[i].second = i + 1; // Store original position (1-indexed)
    }
    
    // Sort the array by values
    sort(a.begin(), a.end());
    
    // Two pointer technique
    int left = 0, right = n - 1;
    
    while (left < right) {
        int sum = a[left].first + a[right].first;
        
        if (sum == x) {
            // Found a solution
            cout << a[left].second << " " << a[right].second << endl;
            return 0;
        } else if (sum < x) {
            left++;
        } else {
            right--;
        }
    }
    
    // No solution found
    cout << "IMPOSSIBLE" << endl;
    
    return 0;
}
