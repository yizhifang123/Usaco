#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    
    vector<int> haybales(N);
    for (int i = 0; i < N; i++) {
        cin >> haybales[i];
    }
    
    // Sort haybale positions for binary search
    sort(haybales.begin(), haybales.end());
    
    // Process each query
    for (int i = 0; i < Q; i++) {
        int A, B;
        cin >> A >> B;
        
        // Find the first haybale >= A
        auto lower = lower_bound(haybales.begin(), haybales.end(), A);
        
        // Find the first haybale > B
        auto upper = upper_bound(haybales.begin(), haybales.end(), B);
        
        // Count haybales in [A, B]
        
        int count = upper - lower;
        
        cout << count << endl;
    }
    
    return 0;
}



