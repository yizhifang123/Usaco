#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("pairup.in");
    ofstream fout("pairup.out");
    
    int n;
    fin >> n;
    
    vector<pair<int, int>> cows; // (milk_output, count)
    
    // Read all milk values with their counts
    for (int i = 0; i < n; i++) {
        int x, y;
        fin >> x >> y;
        cows.push_back({y, x});
    }
    
    // Sort by milk output
    sort(cows.begin(), cows.end());
    
    int maxTime = 0;
    int left = 0, right = cows.size() - 1;
    
    // Pair highest with lowest until all cows are paired
    while (left <= right) {
        if (left == right) {
            // If we have an odd number of cows, this shouldn't happen with M even
            // But handle it just in case
            break;
        }
        
        int pairTime = cows[left].first + cows[right].first;
        maxTime = max(maxTime, pairTime);
        
        // Use up the smaller count
        int minCount = min(cows[left].second, cows[right].second);
        cows[left].second -= minCount;
        cows[right].second -= minCount;
        
        // Remove empty groups
        if (cows[left].second == 0) left++;
        if (cows[right].second == 0) right--;
    }
    
    fout << maxTime << endl;
    
    fin.close();
    fout.close();
    return 0;
}
