#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function to determine if Bessie wins given her gesture and FJ's gesture
bool bessieWins(char bessie, char fj) {
    if (bessie == fj) return false; // Tie
    if (bessie == 'H' && fj == 'S') return true;  // Hoof beats Scissors
    if (bessie == 'S' && fj == 'P') return true;  // Scissors beats Paper
    if (bessie == 'P' && fj == 'H') return true;  // Paper beats Hoof
    return false;
}

int main() {
    // File I/O
    ifstream fin("hps.in");
    ofstream fout("hps.out");
    
    int N;
    fin >> N;
    
    vector<char> fjMoves(N);
    for (int i = 0; i < N; i++) {
        fin >> fjMoves[i];
    }
    
    // Create prefix sums for each gesture (H, P, S)
    // prefix[gesture][i] = number of wins if Bessie uses 'gesture' from 0 to i
    vector<vector<int>> prefix(3, vector<int>(N + 1, 0));
    char gestures[] = {'H', 'P', 'S'};
    
    // Build prefix sums for each gesture
    for (int g = 0; g < 3; g++) {
        for (int i = 0; i < N; i++) {
            prefix[g][i + 1] = prefix[g][i] + (bessieWins(gestures[g], fjMoves[i]) ? 1 : 0);
        }
    }
    
    int maxWins = 0;
    
    // Try all possible split points (including no split)
    for (int split = 0; split <= N; split++) {
        // Try all combinations of two gestures
        for (int g1 = 0; g1 < 3; g1++) {
            for (int g2 = 0; g2 < 3; g2++) {
                int wins = 0;
                
                // Calculate wins for first gesture (0 to split) using prefix sums
                if (split > 0) {
                    wins += prefix[g1][split] - prefix[g1][0];
                }
                
                // Calculate wins for second gesture (split to N) using prefix sums
                if (split < N) {
                    wins += prefix[g2][N] - prefix[g2][split];
                }
                
                maxWins = max(maxWins, wins);
            }
        }
    }
    
    fout << maxWins << endl;
    
    fin.close();
    fout.close();
    return 0;
}
