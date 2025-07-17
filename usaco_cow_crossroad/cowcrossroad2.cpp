#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // File I/O
    ifstream fin("maxcross.in");
    ofstream fout("maxcross.out");
    
    int N, K, B;
    fin >> N >> K >> B;
    
    // Create a boolean array to mark broken signals
    vector<bool> broken(N + 1, false);
    
    // Read broken signal IDs
    for (int i = 0; i < B; i++) {
        int signal;
        fin >> signal;
        broken[signal] = true;
    }
    
    // Use sliding window to find minimum repairs needed
    // We need a window of size K with minimum broken signals
    
    int minRepairs = K;  // Worst case: repair all K signals
    int brokenInWindow = 0;
    
    // Count broken signals in first window [1, K]
    for (int i = 1; i <= K; i++) {
        if (broken[i]) {
            brokenInWindow++;
        }
    }
    minRepairs = min(minRepairs, brokenInWindow);
    
    // Slide the window and update minimum
    for (int i = K + 1; i <= N; i++) {
        // Remove leftmost element from window
        if (broken[i - K]) {
            brokenInWindow--;
        }
        // Add rightmost element to window
        if (broken[i]) {
            brokenInWindow++;
        }   
        minRepairs = min(minRepairs, brokenInWindow);
    }
    
    fout << minRepairs << endl;
    
    fin.close();
    fout.close();
    return 0;
}
