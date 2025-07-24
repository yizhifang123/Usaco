#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;

bool canFinish(const vector<int>& durations, int K, int Tmax) {
    if (K >= durations.size()) return true; // All cows dance simultaneously
    
    priority_queue<int, vector<int>, greater<int>> stage; 
    
    for (int i = 0; i < K; i++) {
        stage.push(durations[i]);
    }
    
    // Process remaining cows
    for (int i = K; i < durations.size(); i++) {
        int earliestFinish = stage.top();
        stage.pop();
        
        int newFinishTime = earliestFinish + durations[i];
        stage.push(newFinishTime);
    }
    
    // Find the latest finish time
    int totalTime = 0;
    while (!stage.empty()) {
        totalTime = max(totalTime, stage.top());
        stage.pop();
    }
    
    return totalTime <= Tmax;
}

int main() {
    ifstream fin("cowdance.in");
    ofstream fout("cowdance.out");
    
    int N, Tmax;
    fin >> N >> Tmax;
    
    vector<int> durations(N);
    for (int i = 0; i < N; i++) {
        fin >> durations[i];
    }
    
    // Binary search on K
    int left = 1, right = N;
    int ans = N;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (canFinish(durations, mid, Tmax)) {
            ans = mid;
            right = mid - 1; 
        } else {
            left = mid + 1; 
        }
    }
    
    fout << ans << endl;
    
    fin.close();
    fout.close();
    return 0;
}
