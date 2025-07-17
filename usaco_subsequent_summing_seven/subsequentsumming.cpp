#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream fin("div7.in");
    ofstream fout("div7.out");
    
    int N;
    fin >> N;
    
    vector<long long> cows(N);
    for (int i = 0; i < N; i++) {
        fin >> cows[i];
    }
    
    // Compute prefix sums
    vector<long long> prefix(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        prefix[i] = prefix[i - 1] + cows[i - 1];
    }
    
    // Store the first occurrence of each remainder mod 7
    vector<int> first(7, -1);
    int maxSize = 0;
    for (int i = 0; i <= N; i++) {
        int rem = prefix[i] % 7;
        if (rem < 0) rem += 7; // handle negative mods
        if (first[rem] == -1) {
            first[rem] = i;
        } else {
            maxSize = max(maxSize, i - first[rem]);
        }
    }
    
    fout << maxSize << endl;
    
    fin.close();
    fout.close();
    return 0;
}
