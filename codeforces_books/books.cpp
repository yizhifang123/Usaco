#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, t;
    cin >> n >> t;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    int maxBooks = 0;
    int currentSum = 0;
    int left = 0;
    
    // Sliding window approach
    for (int right = 0; right < n; right++) {
        currentSum += a[right];
        
        // Shrink window from left if current sum exceeds time limit
        while (currentSum > t && left <= right) {
            currentSum -= a[left];
            left++;
        }
        
        // Update maximum books if current window is valid
        if (currentSum <= t) {
            maxBooks = max(maxBooks, right - left + 1);
        }
    }
    
    cout << maxBooks << endl;
    
    return 0;
}
