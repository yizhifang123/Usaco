#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n >> x;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Use prefix sums to find subarrays with sum x
    // If sum[i..j] = x, then prefix[j] - prefix[i-1] = x
    // So prefix[j] = prefix[i-1] + x
    // We need to count how many times prefix[j] - x appears before position j
    
    unordered_map<long long, int> count;
    count[0] = 1;  // Empty prefix sum (for subarrays starting at index 0)
    
    long long prefixSum = 0;
    long long result = 0;
    
    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];
        
        // Look for prefix[j] - x in our map
        // This represents prefix[i-1] where sum[i..j] = x
        result += count[prefixSum - x];
        
        // Add current prefix sum to our map
        count[prefixSum]++;
    }
    
    cout << result << endl;
    
    return 0;
}
