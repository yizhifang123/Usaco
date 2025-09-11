#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


bool testDistance(long long dist, vector<pair<long long, long long>> intervals, int cowsToPlace) {
    long long numCowsPlaced = (intervals[0].second - intervals[0].first) / dist + 1;
    // line 11: nextLoc maintains earliest placement of next cow
    long long nextLoc = intervals[0].first + numCowsPlaced * dist;

    for (int i=1; i<intervals.size(); i++) {
        if (nextLoc <= intervals[i].second) {
            long long firstInInterval = max(nextLoc, intervals[i].first);
            long long additionalCows = (intervals[i].second - firstInInterval) / dist + 1;
            numCowsPlaced += additionalCows;
            nextLoc = firstInInterval + additionalCows * dist;
        }
    }

    return numCowsPlaced >= cowsToPlace;
}

int main() {
    // using file input/output
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);

    int numCows, numIntervals;
    cin >> numCows >> numIntervals;

    // reading and storing intervals
    vector<pair<long long, long long>> intervals;
    for (int i=0; i<numIntervals; i++) {
        long long start, end;
        cin >> start >> end;
        pair<long long, long long> thisInterval = make_pair(start, end);
        intervals.push_back(thisInterval);
    }
    // sorting needed for binary search
    sort(intervals.begin(), intervals.end());

    // binary search for max possible distance
    // line 46: the distance logically cannot be greater than the maximum distance between grass
    long long high = intervals[numIntervals - 1].second - intervals[0].first;  
    long long low = 1;
    while (low < high) {
        // line 50: + 1 needed to round up because finding max (not min)
        long long mid = low + (high - low + 1) / 2;
        if (testDistance(mid, intervals, numCows)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    cout << low;
    return 0;
}