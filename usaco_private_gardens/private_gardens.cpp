#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Point {
    long long x, y, t;
    Point(long long x = 0, long long y = 0, long long t = 0) : x(x), y(y), t(t) {}
};

// Calculate Euclidean distance between two points
double distance(const Point& a, const Point& b) {
    long long dx = a.x - b.x;
    long long dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

// Check if travel from point a to point b is possible
bool canTravel(const Point& a, const Point& b) {
    if (b.t < a.t) return false; // Cannot travel back in time
    double dist = distance(a, b);
    long long timeAvailable = b.t - a.t;
    return dist <= timeAvailable;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int G, N;
    cin >> G >> N;
    
    vector<Point> grazings(G);
    for (int i = 0; i < G; i++) {
        cin >> grazings[i].x >> grazings[i].y >> grazings[i].t;
    }
    
    // Sort grazing incidents by time
    sort(grazings.begin(), grazings.end(), [](const Point& a, const Point& b) {
        return a.t < b.t;
    });
    
    // Check if the grazing sequence itself is possible
    bool sequencePossible = true;
    for (int i = 1; i < G; i++) {
        if (!canTravel(grazings[i-1], grazings[i])) {
            sequencePossible = false;
            break;
        }
    }
    
    // If the sequence is impossible, all cows are innocent
    if (!sequencePossible) {
        cout << N << endl;
        return 0;
    }
    
    // Count innocent cows
    int innocentCount = 0;
    for (int i = 0; i < N; i++) {
        Point alibi;
        cin >> alibi.x >> alibi.y >> alibi.t;
        
        // A cow is innocent if they cannot reach the first grazing incident
        // from their alibi location and time
        if (!canTravel(alibi, grazings[0])) {
            innocentCount++;
        }
    }
    
    cout << innocentCount << endl;
    return 0;
}   