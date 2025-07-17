#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vector<long long> beauty(n);
        for (int i = 0; i < n; i++) {
            cin >> beauty[i];
        }
        
        long long maxValue = -1e18;
        
        // For each possible left endpoint
        for (int l = 0; l < n - 2; l++) {
            // Use multiset to maintain top 3 elements efficiently
            multiset<long long> window;
            
            // Start with first 3 elements
            for (int i = l; i < l + 3; i++) {
                window.insert(beauty[i]);
            }
            
            // Calculate initial value
            auto it = window.rbegin();
            long long top3Sum = *it + *(++it) + *(++it);
            long long distance = 2;  // r - l = 2 for first window
            maxValue = max(maxValue, top3Sum - distance);
            
            // Slide window to the right
            for (int r = l + 3; r < n; r++) {
                // Add new element
                window.insert(beauty[r]);
                
                // Remove oldest element if window has more than 3 elements
                if (window.size() > 3) {
                    window.erase(window.begin());
                }
                
                // Calculate top 3 sum
                it = window.rbegin();
                top3Sum = *it + *(++it) + *(++it);
                distance = r - l;
                
                maxValue = max(maxValue, top3Sum - distance);
            }
        }
        
        cout << maxValue << endl;
    }
    
    return 0;
}
