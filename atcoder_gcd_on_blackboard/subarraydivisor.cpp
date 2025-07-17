#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to calculate GCD of two numbers
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to get all divisors of a number
vector<long long> getDivisors(long long n) {
    vector<long long> divisors;
    for (long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisors.push_back(i);
            if (i != n / i) {
                divisors.push_back(n / i);
            }
        }
    }
    return divisors;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N;
    cin >> N;
    
    vector<long long> A(N);
    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    
    // Precompute prefix GCD
    vector<long long> prefix(N);
    prefix[0] = A[0];
    for (int i = 1; i < N; i++) {
        prefix[i] = gcd(prefix[i-1], A[i]);
    }
    
    // Precompute suffix GCD
    vector<long long> suffix(N);
    suffix[N-1] = A[N-1];
    for (int i = N-2; i >= 0; i--) {
        suffix[i] = gcd(suffix[i+1], A[i]);
    }
    
    // Find the maximum possible GCD
    long long maxGCD = 1;
    
    // For each position, calculate GCD without that element
    for (int i = 0; i < N; i++) {
        long long gcdWithout;
        if (i == 0) {
            gcdWithout = suffix[1];
        } else if (i == N-1) {
            gcdWithout = prefix[N-2];
        } else {
            gcdWithout = gcd(prefix[i-1], suffix[i+1]);
        }
        
        // The best replacement is to make the new value = gcdWithout
        // This will make the final GCD = gcdWithout
        maxGCD = max(maxGCD, gcdWithout);
        
        // Also try some divisors of gcdWithout as potential replacements
        vector<long long> divisors = getDivisors(gcdWithout);
        for (long long div : divisors) {
            if (div <= 1e9) {
                long long newGCD = gcd(gcdWithout, div);
                maxGCD = max(maxGCD, newGCD);
            }
        }
    }
    
    cout << maxGCD << endl;
    
    return 0;
} 