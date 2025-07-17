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
    
    // Try each element as the first value
    for (int i = 0; i < n - 2; i++) {
        int target = x - a[i].first;
        int left = i + 1, right = n - 1;
        
        // Two pointer technique to find two values that sum to target
        while (left < right) {
            int sum = a[left].first + a[right].first;
            
            if (sum == target) {
                // Found a solution
                cout << a[i].second << " " << a[left].second << " " << a[right].second << endl;
                return 0;
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    // No solution found
    cout << "IMPOSSIBLE" << endl;
    
    return 0;
}
